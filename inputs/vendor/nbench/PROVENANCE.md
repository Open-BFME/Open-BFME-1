# nbench-byte: retail compiled 2.1 (pre-Dierks); the 2.2.3 tarball vendored here supplies headers only

The game (BFME, 2005) statically linked **BYTE Magazine's BYTEmark** in Uwe F.
Mayer's Linux/Unix port `nbench-byte`. Identity is not in doubt:
`calc_confidence`'s error string, the `wordcat.h` catalogue, the
`CPU:Stringsort` tag, and the 0.09 BETA constant in nbench1.c's back-prop loop
are all in `.rdata`, EA's own `Benchmark.dsp` names the files, and
`reverse/functions.csv` claims the bodies against
`game/Libraries/Source/Benchmark/{nbench0,nbench1,emfloat}.cpp`.

## Which release: 2.1, not 2.2.3

This file said 2.2.3 until the 2026-10-08 library audit
(`_impl/reports/libaudit-misc.md`). Across Mayer's releases 2.1 (1997-12-11),
2.2/2.2.1 (2003-02-19) and 2.2.2/2.2.3 (2004-12-29), `emfloat.c` and
`sysspec.c` are identical, `nbench0.c` differs only by the `hardware()` hook
(which EA's `RunBenchmark` replacement never had; EA's `Benchmark.dsp` lists no
`hardware.c`), and the ONLY compiled-code change in `nbench1.c` is the Eike
Dierks stride fix added in 2.2: `p += i*ROWS*COLS` became `p += ROWS*COLS` in
`DoAssignIteration` and `LoadAssignArrayWithRand`. Retail has the pre-fix form:
`DoAssignIteration` 0x00878010 loops `add esi,edi; call Assignment;
add edi,0x9F64` and `LoadAssignArrayWithRand` 0x00877210 loops
`add edi,ebx; ...; add ebx,0x9F64` (0x9F64 = 101*101*4), so the code is 2.1 or
earlier; the byte-exact `calc_confidence`, `DoBitfieldIteration` and
`DoHuffIteration` (functions Mayer changed in 1996-97) put it at 2.1 rather
than BYTE's 1995 original. BFME2's `game.dat` shows the same shape.

## What is actually compiled

`game/Libraries/Source/Benchmark/nbench1.cpp` is `#include "nbench1.c"` with
`-Iinputs/vendor/nbench`; a quoted include resolves to the sibling file first,
so the EA-adapted local copies `game/Libraries/Source/Benchmark/{nbench0,
nbench1,emfloat}.c` are what compiles, and this directory supplies only the
headers (`nbench1.h`, `nmglobal.h`, `wordcat.h`, `emfloat.h`, `sysspec.h`, ...).
The local `nbench1.c` carries `i*ASSIGNROWS*ASSIGNCOLS` at both Dierks sites:
that is the 2.1 text, i.e. the version delta, not an EA edit. The 2.1 headers
differ from these only in `nbench1.h`'s `randnum`/`abs_randwc` prototypes
(`long` instead of `int32`, the same on Win32, and the wrappers `#define` both
to EA functions anyway) and an OSX guard in `sysspec.h`, so keeping the 2.2.3
tarball changes no byte.

## The tarball

Source: https://www.math.utah.edu/~mayer/linux/nbench-byte-2.2.3.tar.gz
(Uwe F. Mayer's 2.2.3 release; LSM entered-date 12MAY2008, sources dated
1997-2004). Size 111791 bytes, SHA-256
`723dd073f80e9969639eb577d2af4b540fc29716b6eafdac488d8f5aed9101ac`
(matches the OpenEmbedded `nbench-byte_2.2.3` recipe). LSM copying-policy:
"freely distributable". The 2.1 tarball (`nbench-byte-2.1.tar.gz`, 195315
bytes, SHA-256
`d6cbe372e6096843a4fd7660841fd6dc40f773644f776db5519b83156d29dddd`) survives
only on web.archive.org's copy of tux.org/~mayer/linux/ and is not vendored.

The `.c` / `.h` files here (except the local notes below) are unmodified
extracts of the 2.2.3 tarball. `tools/build.py` puts `vendor/nbench` on
INCLUDE for the Benchmark TUs only; `nbench1.cpp` also passes
`-Ivendor/nbench` on its `// cl:` line.

## Local files that are not in the tarball

- `pointer.h` — the Makefile generates this by compiling `pointer.c` and
  writing `#define LONG64` only when `sizeof(long) != 4`. Win32/MSVC 7.1 has
  32-bit longs, so the generated file is empty (`touch pointer.h`).
- `strings.h` — MSVC 7.1 has no POSIX `<strings.h>`. nbench1.c includes it
  only for `bzero`; this header maps `bzero` to `memset`. Not used as a
  compile-shape lever.

`sysinfo.c` / `sysinfoc.c` are not vendored: nbench0.c includes them only
under `#ifdef LINUX`, which these TUs do not set.

## Local delta in this directory's nbench1.c

`create_text_line` is the one function that does not byte-match any Mayer
release. Retail uses unsigned `jbe`/`jb` for the two length compares; upstream
declares `charssofar` and `tomove` as signed `long`, which emits `jle`/`jl`.
Those two locals are `unsigned long` in this directory's copy (lines
2765-2766); the compiled local copy casts in the comparison instead. Whether
BYTE's original differs here or EA edited it is unresolved.
`game/Libraries/Source/Benchmark/nbench1.cpp` compiles with `/MD` so `strncmp`
(inlined into `strsift`) goes through the MSVCR71 IAT slot at 0x013594BC,
matching retail.
