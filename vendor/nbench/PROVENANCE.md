# nbench-byte 2.2.3 (vendored)

The game (BFME, 2005) statically linked **BYTE Magazine's BYTEmark** — Uwe F.
Mayer's Linux/Unix port `nbench-byte` **2.2.3**. Identity is not in doubt:
`calc_confidence`'s error string, the `wordcat.h` catalogue, the
`CPU:Stringsort` tag, and the 0.09 BETA constant in nbench1.c's back-prop loop
are all in `.rdata`, EA's own `Benchmark.dsp` names the files, and
`reverse/functions.csv` already claims the bodies against
`Code/Libraries/Source/Benchmark/{nbench0,nbench1,emfloat}.cpp`. Those wrappers
`#include` the upstream `.c` files, which were never committed (the original
`-Ibuild/nbench-source` only existed in one agent's scratch tree), so every
full gate died with

  fatal error C1083: Cannot open include file: 'nbench1.c'

Source: https://www.math.utah.edu/~mayer/linux/nbench-byte-2.2.3.tar.gz
(Uwe F. Mayer's 2.2.3 release; LSM entered-date 12MAY2008, sources dated
1997–2004). Size 111791 bytes, SHA-256
`723dd073f80e9969639eb577d2af4b540fc29716b6eafdac488d8f5aed9101ac`
(matches the OpenEmbedded `nbench-byte_2.2.3` recipe). LSM copying-policy:
"freely distributable".

The `.c` / `.h` files here (except the two local notes below) are unmodified
extracts of that tarball.

Usage: `Code/Libraries/Source/Benchmark/*.cpp` include the upstream `.c` by
their original names (`#include "nbench1.c"`). `tools/build.py` puts
`vendor/nbench` on INCLUDE for those Benchmark TUs only. `nbench1.cpp` also
passes `-Ivendor/nbench` on its `// cl:` line (replacing the untracked
`-Ibuild/nbench-source`).

## Local files that are not in the tarball

- `pointer.h` — the Makefile generates this by compiling `pointer.c` and
  writing `#define LONG64` only when `sizeof(long) != 4`. Win32/MSVC 7.1 has
  32-bit longs, so the generated file is empty (`touch pointer.h`).
- `strings.h` — MSVC 7.1 has no POSIX `<strings.h>`. nbench1.c includes it
  only for `bzero`; this header maps `bzero` to `memset`. Not used as a
  compile-shape lever.

`sysinfo.c` / `sysinfoc.c` are not vendored: nbench0.c includes them only
under `#ifdef LINUX`, which these TUs do not set.

## Local delta in nbench1.c

`create_text_line` is the one function that does not byte-match unmodified
2.2.3. Retail uses unsigned `jbe`/`jb` for the two length compares; upstream
declares `charssofar` and `tomove` as signed `long`, which emits `jle`/`jl`.
Those two locals are `unsigned long` here — the rest of nbench1.c is
verbatim. `Code/Libraries/Source/Benchmark/nbench1.cpp` also compiles with
`/MD` so `strncmp` (inlined into `strsift`) goes through the MSVCR71 IAT
slot at 0x013594BC, matching retail.
