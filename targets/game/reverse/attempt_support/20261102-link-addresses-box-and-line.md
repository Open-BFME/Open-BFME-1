# Linking queue #12: BOX tag and Add_Line constant

Target revision: 72862a8ac8. Queue census: d08539a550.
BFME 2 reviewed revision: 92f12c3fc4e42305d6c26c1da9290c17cc5d20cd
(official master fetched 2026-11-02). The existing reference checkout has
staged deletions and was preserved; donor files were read with git show/grep.
The local census index is older (e9a5ae5b4c, 2026-10-19): current linking
selection remains UNKNOWN; no newly linked bytes are claimed.

## BOX tag: repaired false positive

BFME 1 getter 0x00972310 is exactly MOV EAX,00424F58; RET, followed by INT3.
The matched constructor stores vtable VA 0x0113E830 at 0x009723EA; slot 13
contains the getter. Independently, target 0x00972350 calls vslot +0x34 and
0x00972353 compares EAX to 0x00424F58, selecting reference assignment or
release. This proves the value is a type discriminator, not a dereferenced
image address. Express it as the three character bytes B, O, X, preserving
the existing opaque identity, ABI and complete six-byte extent.

Donor Code/Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.cpp has the
corresponding GetClassId comparison in rva00180815 and the character expression
in Rva00180778Get. These corroborate the BOX interpretation; their addresses,
class identity and layout are not imported. Donor history is shallow (the
reviewed revision is the only available path commit). No include mapping or
compiler flags are changed.

## Add_Line: attempted, restored

Both overloads in Render2DClassAddLine.cpp use hard-coded VA 0x0107533C.
The BFME 1 data ledger already proves canonical const float g_rva0107533C,
owned by game/Libraries/Source/EA/Apt/aptMathRound.cpp. Its provider passes
the normal scoped function and data checks. Both consumers initially pass
(435 and 446 bytes). Replacing the address with this symbol keeps those
sizes and relocations but swaps PUSH 6 and FMUL ST(1) at offsets +0x6F/+0x71:
four differing bytes in each function. The globals helper restores its edit
after this failed verification. All further trials used private build paths.

| Variant | Differences per overload |
| --- | --- |
| named, volatile or mutable-cast canonical float | 4 |
| literal 0.5f | 10 |
| read/write barrier after width or half multiply | 31 |
| barrier after X or Y multiply | 42 / 43 |
| volatile X store | 4 |
| reverse X/Y multiplies | 289 / 296, four bytes shorter |
| named float with /G5, /G6, /G7 or /GB | 4 |

MSVC 7.1, normal /O2 /DNDEBUG /MD /EHsc; all direct compiler calls supplied
private object paths. Probe identifies an adjacent instruction swap with
0.992 normalized instruction similarity. No incorrect body or flag change
remains in game/. The minimal best-candidate patch is preserved alongside
this note. Existing geometry-helper unresolved status in the old census is
independent of the floating-point scheduling mismatch.

Donor Render2DClassAddQuadColor.cpp uses a different BFME 2 body and /G7
context; reviewed as a source/shape lead only. It does not justify changing
BFME 1 vertex layouts, helper identities or table addresses.
