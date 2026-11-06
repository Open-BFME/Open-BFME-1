# GdElemSlot ctor/dtor: pin path refused by ilt_oracle (2026-11-06)

Repair items (body_guard_baseline.csv): `??1BfmeGdElem36@@QAE@XZ` at
0x004128FA ("already recorded as ??1GdElemSlot@@QAE@XZ") and
`??0BfmeGdElem36@@QAE@XZ` at 0x00436E7B ("nothing owns it"), both referenced
by `??0GlobalData@@QAE@XZ` (0x00084510, GlobalDataConstructor.cpp).

## Established facts

- The DWORDs are thunk VAs, not body addresses: retail `??0GlobalData` passes
  `push 0x436e7b / push 0x4128fa` to `??_L@YGXPAXIHP6EX0@Z1@Z`. VA 0x00436E7B
  = thunk at RVA 0x00036E7B (`?j_00036e7b`, gen-thunk row, target body
  0x00083440 `?get@Rva00083440Self@@QAEPAXXZ`); VA 0x004128FA = thunk at RVA
  0x000128FA (`?j_000128fa`, gen-thunk row, target body 0x00083450
  `?Rva00083450Return@@YAXXZ`). The TU comment naming bodies 0x83440/0x83450
  was right; the "mid-function garbage" reading came from treating VAs as RVAs.
- dir32_addresses.csv records `??1GdElemSlot@@QAE@XZ` at 0x004128FA (the thunk
  VA). GlobalDataDestructor.cpp carries the same declare-only class and its
  `??1GlobalData` is matched with the identical reference shape.
- Reworking the TU to declare-only `GdElemSlot` (fields kept: RGBColor
  ambient/diffuse + BfmeGdCoord3D lightPos = 36 B) keeps all 10 rows matched
  and DIR32 OK in the scoped build.

## Refused: symbols.csv pins to the thunks

`??0GdElemSlot@@QAE@XZ @ 0x00036E7B` and `??1GdElemSlot@@QAE@XZ @ 0x000128FA`
trip the commit hook: `ilt_oracle` CONTRADICTS both (p_false 3.26e-04 /
2.61e-04, outside every window of the target's slots 44158:26486-26490 /
14385:10555-10558). Decoration variants (struct tag, virtual dtor, global
spelling) and the address-derived `Rva00128FA`/`Rva0036E7B` names all
contradict too. The grandfathered `Rva00026AB2Vec12` pin at 0x00026AB2 also
contradicts today, so the rule postdates that precedent. All pin-side changes
were reverted; nothing was pushed.

## Options for the next agent

- The DIR32 messages demand the GdElemSlot spellings while the hook refuses
  to route them; one side's evidence has to give. Do NOT re-add pins without
  new oracle evidence.
- Retiring the `??1GdElemSlot` dir32 record in favour of the `?j_000128fa`
  thunk name would need the same rewrite in GlobalDataDestructor.cpp (whose
  `~GlobalData` is matched) plus `dir32_record.py retire` guard proof; the
  member-dtor pointer cannot spell a free thunk name without manual helper
  calls, so this is disproportionate surgery for the gain. Left undone.
- Repro: `python3 tools/ilt_oracle.py check '??1GdElemSlot@@QAE@XZ' 0x128FA`.
