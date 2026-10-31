# Living-world selector: use the existing canonical Coord2D storage

Base `274f3cb00`; claimed selector RVA `003C1EE0`, existing extent 432 bytes.
Replace only its private two-float Coord2D with the registered
`game/Libraries/Include/Lib/Coord2D.h` and use its existing x/y field names.
The eight-byte struct contract and native output stores establish offsets
0 and 4. Retain their original y=0 then x=1 order. No function, method,
parameter, source path or native identity is renamed.

Normal byte verification and owning Coord2D acceptance pass. The complete
432-byte row, all 28 retained external code definitions and their relocation
lists are identical. No external code definition is added or removed.
The two existing absent-from-retail helper markers are preserved.

All 34 non-debug COFF sections have identical bytes and relocation target
positions, including the EH code and data. Compiler-local $T/$L names shift
by one after the include; the raw-name control records that difference.
Resolving only defined storage-class-3 $T/$L targets to their unchanged
non-debug section ordinal and value proves the same cleanup/table edges.
External target names are never normalized. This establishes preservation,
not a newly measured native EH or runtime result.

Reviewed the pinned BFME 2 `Code/Libraries/Include/Lib/Coord2D.h` and its
canonical storage pattern. Its class-key is `class`, whereas BFME 1's
registered byte-evidenced contract requires `struct`; the BFME 1 header is
used unchanged. No donor class-key, method declarations, build flags or
addresses are imported. Existing target contract and native accesses decide
the target layout, not equal names alone.

Frozen `afbe8bafb6` preview remains non-linking, 0 -> 0: the existing
measurePair spelling and AsciiString/STLport clear/destroy copies remain
separate blockers. This task removes one private type definition and passes
header acceptance; it does not repair those link dependencies or claim new
matched bytes. This version of the BFME 1 accept tool validates but does
not retire historical header_queue.tsv rows; that queue is not hand-edited.

The first owning acceptance could not find Git's bash.exe filename. The
installed sh.exe is already GNU Bash 5.2.37, byte-identical to the existing
local Bash copy. A create-only, hash-checked bash.exe copy in that Git
installation supplies the expected executable name. The unchanged owning
acceptance then passes through build.sh. No repository gate is modified.

Original source/object, both acceptance outputs, raw/normalized runtime
section comparisons and normal/link controls are in ignored
`build/two-each-no-qwen-20261031-1756` and the matching diagnostic package.
Build cap remains ten; no Qwen/local inference or Unreal process changes.
