# RVA 0x002666A0: coordinate-return reconstruction bank

This is an unmatched experimental bank, not a new identity or conversion.
The entry remains `Rva002666A0::method`: neither caller proves the original
method spelling. No ledger function or symbol pin is changed by this attempt.

## Boundary and ABI

The unpacked retail body begins at RVA `0x002666A0` and ends with `ret 0x10`
at `0x00266972`, followed by INT3 padding: 725 bytes. Ghidra creation at VA
`0x006666A0` independently reports this same extent. Direct callers at RVAs
`0x0026713F` and `0x00267442` call ILT `0x00020455`; their four pushes and
subsequent copies through returned EAX establish a hidden twelve-byte result,
an Object pointer, a twelve-byte coordinate output pointer, and a Bool pointer.

The local-static key uses the complete retail string `SiegeDockingBehavior`
at VA `0x01090CA4`. Handler RVA `0x00C0FC5E` leads to FuncInfo `0x00DFED70`:
its one unwind state calls `0x00C0FC50`, which clears bit zero of guard
VA `0x012EFD38`. This is the local-static initialization lifetime, not a
coordinate destructor action.

The module constructor at RVA `0x002062C0` installs secondary table
VA `0x010A626C` at receiver offset `0x20`. Slot 2 goes through ILT
`0x0003D6D6` to `0x00206B40`. That body consumes an ObjectID, returns a
signed index, and its independently decoded failure exit returns -1 with
`ret 4`. The bank calls this witnessed slot through an address-derived view.

## Direct calls and values

`callees.py 0x002666A0 725` and independent decoding identify:

- NameKeyGenerator::nameToKey, RVA `0x0008FFC0` via ILT `0x0003ADD7`.
- Object::findModule, RVA `0x001BEE60` via ILT `0x0002AE23`.
- Object::setStatus, RVA `0x001C7370` via ILT `0x000307E7`.
- Object::setStatusBit, RVA `0x000D3EB0` via ILT `0x00032DEE`.
- Rva002060B0Owner::copyAt, RVA `0x002060B0` via ILT `0x000398B5`.
- Rva00206100Owner::point, RVA `0x00206100` via ILT `0x00024726`.
- VectorAdjust003E3B20::adjust, RVA `0x003E3B20` via ILT `0x0000187A`.
- Pathfinder::bfmeGroundCellThreshold, RVA `0x003D8BC0` via ILT `0x0003CE25`.

The status operation uses `BitFlags<86>(kInit,63)`, first cleared and then
set through the individual-bit helper. The coordinate bank includes the
existing WWMath Coord3D header and its authentic inline arithmetic/copy
bodies. The NameKeyGenerator header's unused reference coordinate declarations
are renamed locally to keep that separate reference view from colliding.
Object layout comes from the canonical object.h. The final bank uses the
protected findModule declaration and the canonical `AI *TheAI` global type.

The floating-point operands were read directly from retail: VA `0x01075334`
is `3F800000` (1.0f), `0x01075C70` is `3DCCCCCD` (0.1f), and `0x01075344`
is `40A00000` (5.0f). Normalization deliberately retains retail's unguarded
FSQRT/FDIVR after the pathfinder adjustment.

## Measurements and remaining blockers

The final scratch probe emits 724 bytes against 725, with 369 differing
non-relocation bytes, first at +23, and 13 relocation-layout drifts.
`finish_measure` quality is 0.4883 (size error is penalized twice).
The normalized instruction shape is 0.986; that is **not** the bank's score
and does not prove relocation bindings.

The frame is `0x30`, versus retail `0x24`, with separate helper return
storage; EBX/EBP and scratch allocation differ. The extra frame is observed,
not explained merely by the two opaque helper types. Before promotion the
Pathfinder facade must adopt a canonical header and resolve its existing
struct-Coord3D versus class-Coord3D symbol contract independently. The AI
layout view reads the witnessed pathfinder at +0x0C but is not a complete AI
layout. No new aliases or pins have been added to conceal these issues.

Failed or improving experiments, to avoid repeating them:

- Trivial reference coordinate: 794 bytes, 562 non-relocation differences.
- Existing nontrivial Coord3D copy/assignment lifetime: 724 bytes, 448 differences.
- Positive index guard and separate expression scopes: 724 bytes, 369 differences.
- Visible authentic noninlined copyAt/point bodies: unchanged.
- Experimental common Coord3D return type for both helpers: unchanged; discarded.
- Named block-scoped return objects: 740 bytes, 476 differences; discarded.
- Correct protected findModule and AI-global declarations: unchanged best bytes.

The current body is intentionally banked outside game/. Only independent
strict byte verification and ABI/header reconciliation can promote it.
