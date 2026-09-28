# GameClient is the 0x010F37F0 class; the 0x0110C2D8 class is not

Two classes in the image were both filed under `GameClient`. Retail was linked
without identical-COMDAT folding, so only one of them can own
`??1GameClient@@UAE@XZ`. The proof runs both ways.

## 0x010F37F0 is Zero Hour's GameClient

- Resolving vtable 0x010F37F0 through its incremental-link thunks gives, in
  Zero Hour `GameClient.h` declaration order, the matched bodies
  `GameClient::reset` (slot 4, 0x00431900), `setFrame` (slot 9, 0x004318A0),
  `registerDrawable` (slot 10, 0x0042E530), `findDrawableByID` (slot 11,
  0x00430AF0), `firstDrawable` (slot 12, 0x004318B0),
  `iterateDrawablesInRegion` (slot 20, 0x0042E570), `destroyDrawable`
  (slot 24, 0x00431110) and `getFrame` (slot 26, 0x004318C0).
- The destructor at 0x00431380 installs 0x010F37F0 and its Snapshot-side
  table 0x010F37DC, then Snapshot's 0x01073744 before
  `SubsystemInterface::~SubsystemInterface`. The constructor 0x00433340
  installs the same pair.
- The body is Zero Hour's `GameClient::~GameClient`: the drawable TOC
  `clear()` (pinned `_List_base<GameClient::DrawableTOCEntry>::clear`,
  0x00430A90, called on this+0xF0 exactly as the matched `xferDrawableTOC`
  does), the drawable-list walk through the matched
  `GameClient::destroyDrawable`, the subsystem deletes in Zero Hour's order,
  and `TheMessageStream->removeTranslator` over `m_translators`.
- `W3DGameClient`'s destructor 0x006FBAD0 (between the matched
  `W3DGameClient::createMouse` 0x006FBA50 and `friend_createDrawable`
  0x006FBB20) installs the W3DGameClient tables 0x01120468/0x01120450 and
  tail-jumps into 0x00431380. The concrete game client derives from this class.

## 0x0110C2D8 is a different class, the base of AptPalantir

- Vtable 0x0110C2D8 has 12 slots. Slots 9 and 10, where GameClient keeps
  setFrame and registerDrawable, are `_purecall` (0x0088C500); slot 5 is
  0x00598950 and slot 11 is 0x00592B80. None of GameClient's matched methods
  appear in it.
- Its destructor 0x00596500 destroys members at +0x20, +0x68, +0x154, +0x17C,
  +0x2B8, +0x460 and +0x488 and fields to +0x4DC, far past GameClient's last
  member (+0xF4 array ending at +0x11C). It unregisters the
  `AptPalantir::OnBttn*` and `Palantir/ObserverStuff/*` window callbacks.
- `??1AptPalantir@@UAE@XZ` (0x0079D1D0) calls 0x00596500 as its base
  destructor, and the AptPalantir constructor 0x0079D9F0 calls this class's
  constructor 0x00597FC0 through ILT 0x0000DA58.

No string or caller names the 0x0110C2D8 class, so it takes the address-token
name `Rva00597FC0Client` (its constructor address). The rows and pins that
carried `GameClient` for it (0x00596500, 0x00597680, 0x00592B80, 0x00598950,
the 0x00597FC0 constructor pin) move to that name, and 0x00431380 takes
`??1GameClient@@UAE@XZ`.
