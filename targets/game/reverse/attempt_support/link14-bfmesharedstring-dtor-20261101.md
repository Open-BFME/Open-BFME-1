# Link queue #14: `??1BfmeSharedString@@QAE@XZ` (s526, a1)

Census bb53b24f2b: wrong_selected, 636 B in Rva00363360/Rva003634F0
LivingWorldEntryFind.cpp.

Facts (retail): findByField10 0x00363360 / 0x003634F0 call
`releaseBuffer` 0x00887940 directly on the normal path; their unwind
funclets (gen rows uw_00c19e10 etc.) are `lea ecx,[ebp-0x10]; jmp 0x0040D828`,
the ILT of `??1AsciiString@@QAE@XZ` (0x0005EE90, itself `jmp 0x00887940`).
The ledger defines 0xD828 as `??1BFMERetailAsciiString@@QAE@XZ`
(CarvedBFMERetailAsciiStringDestructor.cpp). The pin
`??1BfmeSharedString@@QAE@XZ` sits on the 0x00887940 body.

Emitters of a 5-byte `jmp releaseBuffer` COMDAT under that name: both
queue files plus Rva00367810EntriesStartNewGame.cpp and
NetworkStringGetterIdentities.cpp.

Tried: `__declspec(dllimport) __forceinline ~BfmeSharedString() {}` (the
0a4cb4954e fix for Rva00363050). Bytes stay 1/1 and the two non-EH files stop
emitting, but in both queue files the unwind funclet becomes
`jmp [__imp_??1BfmeSharedString@@QAE@XZ]`: an unresolvable import. Reverted.

Next: the funclet must name a defined symbol for 0xD828 while the normal
path keeps the inlined releaseBuffer call, e.g. the local's class carrying an
inline dtor whose emitted COMDAT is named and byte-equal to a defined row.
