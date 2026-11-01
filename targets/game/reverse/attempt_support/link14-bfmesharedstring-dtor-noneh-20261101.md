# Link queue #14: BfmeSharedString dtor, non-EH half landed (s30b)

Queue: `??1BfmeSharedString@@QAE@XZ`, wrong_selected, 636 B in
Rva00363360/Rva003634F0LivingWorldEntryFind.cpp. Prior handoff
`link14-bfmesharedstring-dtor-20261101.md` identified 4 emitters of a 5-byte
`jmp releaseBuffer` COMDAT and the funclet-safe requirement. This note records
what landed and what the remainder needs.

## Landed: the 2 non-EH emitters stop emitting

`Rva00367810EntriesStartNewGame.cpp` (implicit dtor) and
`NetworkStringGetterIdentities.cpp` (explicit `{}`) use the 0a4cb4954e
pattern now: `__declspec(dllimport) __forceinline ~BfmeSharedString() {}`.
Both verify (1/1 and 5/5) and their COFF has no dtor definition or
reference (fully inlined, non-EH, zero footprint). BFME 2 uses the same
suppression pattern (e.g. Rva00079911Clear.cpp @6584c19); the change
follows the local precedent. Emitters 4 -> 2; the kept copy is still a
wrong queue-file jmp, so the queue entry remains until the EH half lands.

## Verified facts (object-level, Rva00363360 TU)

- Normal path: two `E8 -> ?releaseBuffer@?$StringBase@D@@AAEXXZ`
  (dtor inlined through the base). Funclet (.text$x): one
  `E8 -> ??1BfmeSharedString@@QAE@XZ` (the pinned name; the only
  out-of-line user).
- The emitted 5-byte COMDAT (`E9 -> releaseBuffer` name) is byte- and
  reloc-identical to the DEFINED `??1AsciiString@@QAE@XZ` row at 0x5EE90.
  It still loses: the NAME is pinned at 0x887940 (134-byte body), so any
  emission under it is judged wrong. Any fix must leave zero emitters of
  this name while the funclet keeps naming a defined symbol.
- `copyString` (whose sret feeds the EH'd local) is a matched row in
  NetworkStringGetterIdentities.cpp with a `BfmeSharedString` return; the
  findByField10 row names embed `BfmeSharedString` too. Both are fixed.

## Refuted: type-swap of the EH'd local

Swapping the local to `AsciiString`/`BFMERetailAsciiString` (whose names
are defined) fails: copyString's differing return type forces a converting
ctor through a temporary, and the temporary's destruction adds bytes and
EH coverage to the tight 315/321 B parents. Same-shape conflict as the
RefHandle dtor (#8): the normal path needs E8->releaseBuffer while any
defined-name COMDAT needs a different target.

## Next: port the 134-byte body into a noinline TU-local dtor (2 EH TUs)

Donor: `StringBase<T>::releaseBuffer` in
game/Libraries/Source/string/StringBase.cpp (scoped-lock + refcount-dec +
free). Sketch per queue TU: `__declspec(noinline) ~BfmeSharedString()` with
the full 134-byte logic adapted to the TU-local StringData view
(`references` vs `ref_count`, lock type, `free`/EnterCriticalSection
imports). Then the normal path is E8->dtor-name resolving via the pin to
0x887940 (same target as today's E8->releaseBuffer; pin resolution in the
gate is proven by the current passing state), the funclet is unchanged,
and the emission is byte-equal to 0x887940 (verdict retail, never loses).
Caveats: donor TU compiles `/EHs-c-`, queue TUs `/EHsc` (unwind shape);
each TU's StringData view differs; verify emission equality per TU with a
COFF dump, not just the parent gate. Estimated 2-4 h for both. The uw_
gen-funclet rows stay valid (their 8 bytes are unchanged).
