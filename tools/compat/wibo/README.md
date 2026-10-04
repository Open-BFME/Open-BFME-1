# Linux Wibo: MSVC7.1 native-link compatibility

Opt-in source patch and focused reproduction, validated 2026-10-04. The repository's
Wine setup remains the default. Nothing here installs/replaces a runner, changes
Wine or sandbox security settings, or changes game code, gate tools or baselines.

## Why `LNK1104: cannot open file 'TEMPFILE'` occurred

The linker created its temporary file successfully. It reserved a guest address,
released it with `VirtualFree(..., 0, MEM_RELEASE)`, then requested a file view at
that address. Wibo deliberately retained an inaccessible **host** reservation to
keep host allocations out of guest address space. Its old explicit-base
`MapViewOfFileEx` path used `MAP_FIXED_NOREPLACE`, collided with that reservation,
and returned error 487. This was an allocator-ownership mismatch, not a missing
file or a security restriction to bypass.

The patch reserves exact-base views through Wibo's synchronized guest mapping
table before replacing only its owned host reservation. Live guest allocations,
views, partial overlaps, native mappings, low-DOS/out-of-arena addresses and bad
alignment are rejected. Unmapping restores `PROT_NONE` before releasing guest
ownership. Initial native-range metadata exhaustion fails startup closed; exact
addresses on non-Linux hosts return unsupported. A failed restoration retains
bookkeeping conservatively, potentially leaking address space rather than
allowing reuse that could overwrite an unrelated mapping.

## Provenance and license

Apply these **unchanged patches in order** to
[decompals/Wibo 420a75b7f80435824c3a633571277f90ae056119](https://github.com/decompals/wibo/tree/420a75b7f80435824c3a633571277f90ae056119):

1. `stringfromguid2.patch`, SHA-256
   `6a53db04b78e0d1104d1a6e95483898e62f0592f03e3e45635848b58166791fe`.
   This is the independently reviewed new formatter reconstruction, including
   its complete source, registration and sentinel/capacity test. It is not a
   recovered historical patch or an upstream commit.
2. `mapping-compatibility.patch`, SHA-256
   `3dc3dbf159c3ec1fb9ee98697c1032d9ff30c7585598a0409467e196c27abd41`.
   Includes the complete mapping regression fixture and CMake registration.

Upstream Wibo portions and source context in these patches retain the MIT
copyright notice for 2022–2024 Ash Wolf & Decompals, preserved verbatim in
[LICENSE.wibo](LICENSE.wibo). Preserve that notice when redistributing the bundle.
This addition does not change the repository's [GPL-3.0 license](../../../LICENSE);
local patch and fixture additions follow that existing repository license.
Standalone fixture sources live under
[tools/tests/fixtures/wibo](../../tests/fixtures/wibo), the repository's test-source
location. No binaries are bundled.

The tested baseline was upstream plus patch 1, SHA-256
`3fd1768efb14a0e45555e3cb1a8646fc1dffb25a8991990f5959ade9db90686b`.
The reviewed Linux candidate was baseline plus patch 2, SHA-256
`c6addd458da551ef40860c737e637e973fb2c3b77c3a2ebb76632373b962a7e5`.
These identify the tested artifacts, not a promise of reproducible ELF bytes with
other compiler/dependency versions. [validation.json](validation.json) records
patched-source hashes and the four real-source compiler parity results.

## Reproduce in an isolated directory

From this repository root, with Git, GNU patch, CMake, Ninja, GCC/G++ (C++20), LLD,
Python 3.10+ with venv/pip and libclang 17+ available:

```bash
repo=$PWD
bundle="$repo/tools/compat/wibo"
(cd "$bundle" && sha256sum -c SHA256SUMS)
mkdir -p build/wibo-compat
work="$repo/build/wibo-compat"
git clone https://github.com/decompals/wibo.git "$work/source"
git -C "$work/source" checkout --detach 420a75b7f80435824c3a633571277f90ae056119
patch --batch --fuzz=0 -d "$work/source" -p1 < "$bundle/stringfromguid2.patch"
patch --batch --fuzz=0 -d "$work/source" -p1 < "$bundle/mapping-compatibility.patch"
cmake -S "$work/source" -B "$work/runner" -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="$work/source/cmake/toolchains/x86_64-linux-gcc.cmake" \
  -DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=lld \
  -DWIBO_VERSION=1.2.0+420a75b7f804-guid-map20261004 \
  -DWIBO_ENABLE_LIBURING=OFF -DWIBO_ENABLE_FIXTURE_TESTS=OFF -DWIBO_ENABLE_LTO=OFF
cmake --build "$work/runner" --target wibo --parallel 2
bash "$bundle/verify.sh" "$work/runner/wibo" "$work/source" "$work/fixtures"
```

Use a new `work` directory if it already exists. Upstream CMake pins mimalloc to
`69c5c5c402bf0414ff4a366697ecbd5c7578dc02`, downloads hash-checked Wine CRT DLLs
from `encounter/winedll` release `2026-09-29`, and bootstraps `clang==17.0.6` for
trampoline generation. It does not launch Wine. Existing dependency caches can
be supplied with upstream `FETCHCONTENT_SOURCE_DIR_MIMALLOC`, individual
`*_DLL` CMake variables, `Python3_EXECUTABLE` and `LIBCLANG_LIBRARY`; the original
validation used those overrides. Dependencies retain their own licenses.

`verify.sh` uses only the supplied runner and this checkout's MSVC7.1 compiler,
linker and import libraries. Outputs and temporary files stay in `OUTPUT_DIR`.
The Linux host-layout fixture is deliberately enabled; do not use this script as
a Windows/macOS conformance suite. The added strict fixture links a DLL against
`msvcrt.lib` with `/NODEFAULTLIB`, checks `MSVCR71.dll!memmove`, and has no local
import stub or `/FORCE`. The minimal native link is exactly:

```bash
# In verify.sh's output directory, with its process-local VC environment:
"$runner" "$vc/bin/link.exe" /nologo /nodefaultlib /incremental:no \
  /machine:x86 /subsystem:console /entry:map_test_entry \
  /out:minimal-map.exe minimal-map.obj kernel32.lib
```

## Verified scope

- Baseline minimal native `link.exe`: exit 80, `LNK1104 TEMPFILE`; candidate:
  exit 0, valid PE32. Minimal reserve/release/fixed-map executable: baseline
  exit 5, candidate exit 0.
- Mapping fixture: baseline exit 12 at released-address mapping; candidate
  passes 32 map/unmap/reuse cycles, live allocation/view and partial-overlap
  rejection, preserved native ELF, alignment error 1132, address error 487,
  file-range error 87, nonzero offsets, null-base mapping and `VirtualQuery`.
- Separate capacity-zero diagnostic build: startup exit 1 with the native-range
  capacity diagnostic before guest execution. This deliberately altered test
  binary is not the reviewed candidate and is not installed or bundled.
- Genuine MSVC7.1 native links and executions of mapping, GUID and CRT smoke
  fixtures passed; smoke prints answer 51. No LLD substitution in guest links.
- Original Quickmatch strict inputs: baseline exit 80; candidate exit 0 with
  `MSVCR71.dll!memmove`. This was an import-only link using the repository
  verifier's labelled non-import stubs, `/NODEFAULTLIB`, `/DLL`, `/NOENTRY`,
  `/OPT:NOREF`, `/SAFESEH:NO`, and retail import libraries, without `/FORCE`.
  It is **not a full game link**. The small bundled strict fixture is a separate
  reproducible check of that import-library mechanism, not the original inputs.
- Four real BFME TUs compiled under both runners to identical **complete raw
  COFF files** using the same input/output paths. A separate comparison covered
  nondebug section bytes, symbols/auxiliary records and all **269 relocations**
  (types, offsets and referents), including EH handlers, `.xdata` and `.rdata`:
  `Rva00452300MapPointerVector` (32), `OnlineQuickMatchConstructor` (95),
  `MapCacheAddMap` (116), `Object_bfmeTransferReplacementState` (26).
- Independent static reviews approved both exact patch hashes above. Mapping
  review covered ownership/ranges, locks, overflow, fail-closed startup and
  platform limits; runtime tests were performed separately. No upstream review
  or general cross-platform approval is implied.
- Packaging verification applied both patches without fuzz to a clean upstream
  source copy and compared every changed source with the reviewed candidate.
  CMake configure with existing dependency caches and the documented fixture
  command passed with that source and the existing candidate; packaging did not
  rebuild the candidate a second time.

No Windows/Wine parity, full MinGW/CTest suite, full game link or general
cross-platform compatibility claim is made. Wine was unavailable in the test
environment; MinGW was not installed. The fixture assertions follow the API
contract, not a measured Windows execution.

For repository use, select this candidate **only for the intended `link.exe`
process** after focused validation. Continue ordinary compilation/byte gates
with the existing runner. If a temporary adapter is needed, keep it local to the
calling process, identify the intended binary by hash, and delegate all other
commands to the existing runner. For a rebuild, first run the focused checks and
record that locally tested binary's SHA-256; do not assume it has the ELF hash
above. Do not install it over `wine`, rewrite global PATH/configuration, or weaken
a gate to make a link pass.

## Primary contracts

- [MapViewOfFileEx](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-mapviewoffileex):
  explicit-base availability, allocation granularity, file bounds and null-base selection.
- [VirtualFree](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualfree)
  and [UnmapViewOfFile](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-unmapviewoffile):
  guest release and view lifetime.
- [ERROR_MAPPED_ALIGNMENT](https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes--1000-1299-)
  and [Linux mmap(2)](https://man7.org/linux/man-pages/man2/mmap.2.html): alignment
  reporting, collision rejection versus replacing an allocator-owned reservation.
- [StringFromGUID2](https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-stringfromguid2):
  braces, character capacity, NUL-inclusive return count and insufficient capacity.
  Uppercase output and unchanged buffers on failure are local reconstruction tests.
