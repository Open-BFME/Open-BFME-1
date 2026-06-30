# How to Contribute

* Start easy - Find a small function you can generate the C++ code for, or translate __asm to C++
* If confident, go harder - Check docs/ for more ambitious things to do

# Rules

* Keep shit lean. It's very easy to generate verbose code and verbose docs with AI. Always ask yourself if you're being helpful by generating it. Temporary scripts and tests are fine if you clean them up. Really ask yourself a question if your commit is larger than 33% of the median of previous commits in the project.
* Don't add fallback code paths as a convenience. They hide mismatches and create subtle bugs that cost more time than they save. If the original toolchain matters, use the original toolchain.
