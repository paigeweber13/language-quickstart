# Performance
All tests were done in ubuntu linux on a Ryzen 5 3600.

Immediately after writing the code, without any further optimizations, the
performance was about 6.5e6 items per second for all n >= 1e8

After this the code was modified so that instead of each iteration of merge 
creating its own buffer, a single buffer is required to be provided by the
calling code. This nearly *tripled* the speed: performance was about 1.6e7
items per second for all cases with n >= 1e8
