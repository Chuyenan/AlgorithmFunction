////
//// Created by 14911 on 2023/4/6.
////
////
// Yet another caching allocator for CUDA device allocations.
//
// - Allocations are associated with a stream. Once freed, blocks can be
//   re-allocated on the same stream, but not on any other stream.
// - The allocator attempts to find the smallest cached block that will fit the
//   requested size. If the block is larger than the requested size, it may be
//   split. If no block is found, the allocator will delegate to cudaMalloc.
// - If the cudaMalloc fails, the allocator will attempt to free one cached
//   block of sufficient size that is not split and retry the allocation.
//   If this also fails, the allocator will attempt to free all cached blocks
//   that are not split and retry the allocation.
// - Large (>1MB) and small allocations are stored in separate pools.
//   Small requests are packed into 2MB buffers. Large requests will use the
//   smallest available free block or allocate a new block using cudaMalloc.
// - To reduce fragmentation, requests between 1MB and 10MB will allocate and
//   split a 20MB block, if no free block of sufficient size is available.
// - To further reduce fragmentation, blocks >= 200MB are not allowed to be
//   split. These oversize cached blocks will still satisfy requests within
//   20MB of the oversize cached block size.
//
// With this allocator, allocations and frees should logically be considered
// "usages" of the memory segment associated with streams, just like kernel
// launches. The programmer must insert the proper synchronization if memory
// segments are used from multiple streams.
//
// The library provides a recordStream() function to help insert the correct
// synchronization when allocations are used on multiple streams. This will
// ensure that the block is not reused before each recorded stream completes
// work.
//
//
//Note [Interaction with CUDA graph capture]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Graph capture performs a dry run of a region of execution, freezing all CUDA
//work (and virtual addresses used during that work) into a "graph." The graph
//may be "replayed" like a single giant kernel, with greatly reduced CPU
//overhead as well as modestly improved GPU performance.
//
//Because capture bakes in memory addresses, the memory used during capture
//must be available for the graph to use during replay. DeviceCachingAllocator
//assigns and frees memory eagerly and dynamically, so if we're not careful
//about managing graphs' memory, at replay time those memory addresses could be
//use by other tensors.
//
//To guarantee a graph's baked in addresses are safe to reuse in replay,
//DeviceAllocator satisfies allocations from a graph-private memory pool during
//capture, and doesn't begin cudaFreeing those addresses until the graph is
//destroyed.
//
//Within the private pool, allocations are freed and reassigned as usual during
//capture. Memory regions will be used in a consistent order during replay. So
//a private pool doesn't use memory more wastefully than the default pools
//during capture, but it does reserve its high-water mark of used memory away
//from the default pools as long as the capture(s) it served survive
//(regardless whether those captures are idle or replaying).
//
//CUDAGraph's requests for private pools are mediated by
//DeviceAllocator::notifyCaptureBegin, notifyCaptureEnd, and
//notifyCaptureDestroy.
//
