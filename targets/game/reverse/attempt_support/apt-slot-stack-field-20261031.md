# Apt slot release: bind the existing stack array field

Base `6845e687a`; claimed address-owned `dup_008c66a0`, RVA `008C66A0`,
129 bytes, ending with RET at +7A and +80. Its semantic callback name remains
unknown. The census blocker is declaration-only `g_bfmeArr1233`.

Native entry loads the array from VA `01338750` into EAX, then the count
from `01338748` into ECX. This is the already-declared +8 field and count
of `Rva008AE770TheStack`. The existing strong global owner is
`Common/Rva00C6DCC0StaticInit.cpp`: its 88-byte object starts at `01338748`,
and its independently rowed 22-byte initializer passes that address to the
70-byte `Rva008C5FD0Zero` constructor. Existing Apt consumers, including
`Rva008AE770Invoke.cpp` and `Rva008AF0B0CreateNode.cpp`, already read these
same fields. No new global, alias, pin, data row or object layout is needed.

Remove the dangling global declaration and load the existing stack field.
The raw COFF operand at +1 changes only its relocation addend, 0 -> 8, and
DIR32 referent, `g_bfmeArr1233` -> `Rva008AE770TheStack`. Its linked native
address remains `01338750`. All other bytes and nine relocations are identical;
the retained inline predicate is also unchanged. No code definition is added
or removed. Normal verification of caller, initializer and zero constructor
passes 3/3 rows, ten DIR32 checks and body guards. Frozen definitions pass.

VC7.1 `/O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc` initially reverses the
related field loads: direct member access and explicit array/count locals
each leave one wrong SIB byte. Making both loads volatile restores that SIB
but changes the later flag temporary EDX -> EAX and shortens TEST. Only the
array pointer read is volatile in the final implementation; the count stays
ordinary. This preserves the native EAX/ECX and EDX allocation and all 129
linked bytes. These measured variants are preserved in the build controls;
no failed reconstruction remains in the source tree.

Reviewed BFME 2 pin `b5a7b8290a0c4c20b03a3664609d434904e228eb`,
`Code/GameEngine/Source/Common/Rva006EC670Cluster.cpp`, and the existing
BFME 1 `Rva008AE770Invoke.cpp` donor adaptation. The donor argument handlers
read their existing interpreter stack through At(0..2); this supports the
shared ownership pattern, not BFME 1 addresses or a complete class identity.
BFME 1 native entry, its existing partial view and proven global initializer
establish this particular field binding. Donor addresses and layouts are not
imported, and no anonymous callback is renamed.

Frozen index `afbe8bafb6` (2026-10-31 12:37) previews caller 0 -> LINKS/129,
initializer 22 -> 22 and zero constructor 70 -> 70, cohort 92 -> 221.
This is a bounded prediction, not a new census, complete current selection,
full-image link or runtime test. The broader local object set remains
incomplete; its unchanged missing-input obstacle is not rescanned.

Native disassembly, original source/object, exact relocation comparison and
normal build/link controls are retained in ignored
`build/two-each-no-qwen-20261031-1707` and the matching diagnostic package.
Qwen and other local models remain off; verification uses the shared
ten-worker build cap without changing an Unreal process.
