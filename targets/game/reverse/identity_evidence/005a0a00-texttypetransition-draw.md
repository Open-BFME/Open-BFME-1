# RVA 0x005A0A00 is TextTypeTransition::draw

The 57-byte body at RVA 0x005A0A00 is
`?draw@TextTypeTransition@@UAEXXZ`, a public virtual with no stack arguments.
The identity is established; a byte-exact C++ conversion remains open.
All binary facts below were checked in
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, image base
0x00400000, with pefile and capstone. GhidraMCP creates the same 57-byte
function at VA 0x009A0A00.

## Constructor and named neighbouring slots

The matched TextTypeTransition constructor at RVA 0x005A0620 stores
VA 0x0110CCFC to `[esi]` at VA 0x009A062A. The retail table is:

| Slot | Stub RVA | Body RVA | Identity |
|---|---|---|---|
| 0 | 0x00009543 | 0x005A0A50 | TextTypeTransition scalar deleting destructor |
| 1 | 0x00012F53 | 0x005A07F0 | TextTypeTransition::init |
| 2 | 0x0001BB08 | 0x005A0910 | TextTypeTransition::update |
| 3 | 0x0002AF3B | 0x005A0430 | Copy/flag method, still address qualified |
| **4** | **0x00031976** | **0x005A0A00** | **This body** |
| 5 | 0x0004079B | 0x00489240 | Shared transition method |
| 6 | 0x00045C69 | 0x005A0420 | Short class-specific method |
| 7 | 0x000418CB | 0x00489250 | Shared transition method |

Slot 4's pointer is at VA 0x0110CD0C. Its ILT E9 targets VA 0x009A0A00.
The destructor, init and update neighbours are independently named matched
rows, rather than names inferred from this body. The class declaration in
Zero Hour's `GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h`
orders destructor, init, update, reverse, draw, skip. Slots 1 and 2 agree with
the BFME names, placing draw at slot 4.

## Native behaviour agrees with the specific method

The body reads the current draw frame at this+0x28 and requires it to be
strictly greater than this+0x10 and strictly less than this+4. The matched
update at 0x005A0910 writes this+0x28 after consulting the same frame bounds.
The constructor clears strings at +0x2C/+0x30 and DisplayString at +0x34;
matched init populates those fields. This body's first call copies the
UnicodeString at +0x30 into a by-value temporary through the real
StringBase<unsigned short> copy constructor (RVA 0x00888400). It passes the
copy to the DisplayString's virtual slot +4, then calls the render helper
at RVA 0x005A0450 using the window at +0x0C and the display string at +0x34.
It ends with RET at 0x005A0A38 and INT3 at 0x005A0A39.

The Zero Hour body in `GeneralsMD/.../GUI/GameWindowTransitionsStyles.cpp`
contains the same strict draw-frame guard, setText(m_partialText) and
same-file drawTypeText(m_win,m_dStr) operation. BFME adds the start-frame
member and changes the DisplayString interface, so reference offsets and
helper call conventions cannot be copied unchanged.

## Fresh code generation experiment and remaining blocker

The scratch experiment uses the existing GameWindowTransitionsStyles TU and
its real TextTypeTransition declaration, with the already witnessed BFME
field view used by init/update. It exposes the genuine same-file render
helper instead of declaring a synthetic external adapter or adding a caller.
A narrow address-qualified view describes the helper's observed BFME virtual
slots. No shared header, pin or production source is changed.

The caller probes at 57/57 bytes with two REL32 relocations, but differs in
14 non-relocation bytes and has normalized instruction shape 0.960.
Retail keeps the transition in ESI and supplies the render helper's display
argument in EDI; this compiler allocates the opposite pair and saves EDI
before the guard instead of between comparison and branch. Swapping real
helper-local declaration order leaves this result unchanged. Reversing the
two logical helper parameters produces 55 bytes and still the wrong private
register contract. A direct typed helper parameter also remains non-exact.
The helper itself probes at 369/363 bytes, so its source is evidence for
further work, not a byte-match or an independently landed dependency.

The bank retains the exact-size candidate and address-qualified helper;
identity is no longer the blocker. Register allocation and helper binding
must both be resolved before add_match can land it.
