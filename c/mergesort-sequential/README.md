# Performance
## Sequential Code
All tests were done in ubuntu linux on a Ryzen 5 3600.

Immediately after writing the code, without any further optimizations, the
performance was about 6.5e6 items per second for all n >= 1e8

After this the code was modified so that instead of each iteration of merge 
creating its own buffer, a single buffer is required to be provided by the
calling code. This nearly *tripled* the speed: performance was about 1.6e7
items per second for all cases with n >= 1e8

## Parallel Code
The parallel implementation is about 40% slower than the sequential code. I
believe this is because mergesort doesn't parallelize well, being heavily
memory-bound. I suspect that I would see speedup if I ran this on a cluster,
especially one with NUMA.
