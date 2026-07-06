# STLport 4.5.3 (vendored)

The game (BFME / SAGE engine, ex-Generals) linked **STLport 4.5.3** as its C++
standard-library implementation. Byte-matching any function that uses std::
containers (list/vector/map/hash_map/string) REQUIRES compiling against these
exact headers — MSVC 7.1's own STL emits different code (confirmed: STLport's
`list<void*>::push_back` / `_M_create_node` / `_Construct` byte-sequences occur
48–146× in lotrbfme.exe; MSVC's never appear).

Source: http://www.stlport.org/archive/STLport-4.5.3.tar.gz (2002 release), the
same version whose (gitignored, empty) tree sits at
Libraries/Source/STLport-4.5.3 in the reference source dump.

License: STLport license (permissive, BSD-style) — see STLPORT-README.

Usage: a source file opts in with a `// stlport` line near the top; tools/build.py
then prepends vendor/stlport to INCLUDE for that file only (STLport shadows
<cmath>/<cstring>/etc, so it must NOT be global — STL-free matched files use MSVC's).
