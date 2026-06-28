# Rules

* Keep shit lean. It's very easy to generate verbose code and verbose docs with AI. Always ask yourself if you're being helpful by generating it. Temporary scripts and tests are fine if you clean them up. Really ask yourself a question if your commit is larger than 33% of the median of previous commits in the project.
* Don't add fallback code paths as a convenience. They hide mismatches and create subtle bugs that cost more time than they save. If the original toolchain matters, use the original toolchain.
* Don't commit without the user explicitly asking
