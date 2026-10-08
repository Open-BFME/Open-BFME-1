# STLport 4.6 (vendored)

The game (BFME / SAGE engine, ex-Generals) linked **STLport 4.6** as its C++
standard-library implementation. Byte-matching any function that uses std::
containers (list/vector/map/hash_map/string) REQUIRES compiling against these
exact headers — MSVC 7.1's own STL emits different code (confirmed: STLport's
`list<void*>::push_back` / `_M_create_node` / `_Construct` byte-sequences occur
48–146× in lotrbfme.exe; MSVC's never appear).

Source: http://www.stlport.org/archive/STLport-4.6.tar.gz (2003 release), the
`stlport/` header tree plus the three private `src/` headers below. Until
2026-10 this directory held STLport 4.5.3, the version Generals' reference
source dump names. Retail's own bodies say 4.6:

- `ios_base::_S_initialize` ends with 4.6's `--Init::_S_count` (retail RVA
  0x843990); 4.5.3 has no such decrement.
- `__stl_next_prime` matches only in the shape of 4.6's
  `hashtable::_M_next_size` lookup (no comparator temporary on the stack).
- `basic_string<char>::find(char, size_type)` (0x006542C0) shares one
  `return npos` tail, which only a `static const` npos produces (see below).

License: STLport license (permissive, BSD-style) — see STLPORT-README.

Usage: a source file opts in with a `// stlport` line near the top; tools/build.py
then prepends vendor/stlport to INCLUDE for that file only (STLport shadows
<cmath>/<cstring>/etc, so it must NOT be global — STL-free matched files use MSVC's).

## Changes from the 4.6 tarball

- `config/stl_msvc.h`: `_STLP_STATIC_CONST_INIT_BUG` is defined only up to
  `_STLP_MSVC` 1300 (stock 4.6 goes up to 1310), so VC7.1 gets in-class
  `static const` members such as `npos`. The enum spelling makes the
  `find(char)` body above 8 bytes longer.
- `stl/_list.h` (`BFME_PARTICLE_LIST_NODE_TAIL`) and `stl/_tree.c`
  (`_BFME_RETAIL_TREE_INSERT_LAYOUT`): opt-in macros carried over from the
  4.5.3 tree. They change nothing unless a TU defines them.

## Private `src/` headers

`vendor/stlport/src/` holds the headers STLport's own translation units include
but which live outside the header tree in the tarball: `stlport_prefix.h`,
`c_locale.h` (the `_Locale_*` C API — a different file from
`stlport/stl/c_locale.h`) and `aligned_buffer.h`. `Code/stlport/*.cpp` are those
library sources, so they include them by their upstream spelling
(`#include "stlport_prefix.h"`); tools/build.py puts `vendor/stlport/src` on
INCLUDE right behind `vendor/stlport` for `// stlport` files. Same 4.6
tarball as the headers above, unmodified.
