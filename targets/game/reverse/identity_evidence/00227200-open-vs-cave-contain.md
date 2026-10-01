# 0x00227200 is OpenContainModuleData's constructor, not Cave's

Two real names claim the 398-byte body at 0x00227200:
`??0CaveContainModuleData@@QAE@XZ` and `??0OpenContainModuleData@@QAE@XZ`.
Retail was linked without identical-COMDAT folding, so only one is right.
The body installs vtable VA 0x010AC338; the Cave vtable is VA 0x0108F288.
The constructor that installs 0x0108F288 is a different body, 0x0012AB50,
which calls 0x00227200 as its base. So 0x00227200 is the Open base
constructor and the Cave row is the over-claim to retire.

All addresses below are retail RVAs unless marked VA, read from
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`.

## 0x00227200 installs 0x010AC338 and never 0x0108F288

- At +0x27 the body has `C7 06 38 C3 0A 01`: `mov dword ptr [esi],
  0x010AC338`. That is the only vtable store in the 398 bytes.
- Slots 1-16 of VA 0x010AC338 and VA 0x0108F288 are identical; only slot 0
  differs (0x0041ED5D vs 0x00415B4F). The probe masks the vtable operand as
  a relocation, which is why both names byte-match the same body.

## The 0x0108F288 installer is 0x0012AB50, which calls 0x00227200 as its base

- 0x0012AB50 (28 bytes):
  `56 8B F1` (push esi; mov esi,ecx)
  `E8 D8 94 F1 FF` (call ILT 0x00044030, which jumps to 0x00227200)
  `C7 06 88 F2 08 01` (mov dword ptr [esi], 0x0108F288)
  `C7 86 68 01 00 00 00 00 00 00` (mov dword ptr [esi+0x168], 0)
  `8B C6 5E C3` (mov eax,esi; pop esi; ret).
- That is the derived-constructor shape: call the base constructor, install
  the derived vtable, initialize the derived tail. The tail word at +0x168
  is `m_caveIndexData`: Zero Hour `CaveContain.h` declares
  `class CaveContainModuleData : public OpenContainModuleData` adding only
  `Int m_caveIndexData` (initialized to 0), and `dir32_addresses.csv` pins
  `??_7CaveContainModuleData@@6B@` at 0x0108F288.
- 0x0012AB50 is ledger-claimed as `?dup_0012ab50@@YAXXZ` with
  `object-symbol=??0CaveContainModuleData@@QAE@XZ`, consistent with this.

## The factories agree: 0x168 keeps 0x010AC338, 0x16C reinstalls 0x0108F288

- `?friend_newModuleData@OpenContain@@` (0x001159E0, 110 bytes): pushes
  `0x168` (`68 68 01 00 00`), calls 0x00227200 via ILT 0x00044030, and
  performs no vtable store afterwards. The object keeps the 0x010AC338 the
  body installed, and 0x168 is `sizeof(OpenContainModuleData)` (the bank's
  `VerifyObjectSize` guard).
- `?friend_newModuleData@CaveContain@@` (0x0012ABC0, 126 bytes): pushes
  `0x16C` (`68 6C 01 00 00` = 0x168 + 4), calls 0x00227200 via ILT
  0x00044030, then stores `C7 06 88 F2 08 01` (vtable 0x0108F288) and
  `C7 86 68 01 00 00 00 00 00 00` (+0x168 = 0). A factory that had just run
  the true Cave constructor would not need to reinstall the vtable and the
  tail; it does so because 0x00227200 is the Open base constructor.
- Every other caller of 0x00227200 (via ILT 0x00044030) is a derived-class
  base call or the Open factory: TransportContainModuleData 0x0021FC80,
  HordeContainModuleData 0x00220530, HordeSiegeEngineContainModuleDataBase
  0x0022E820, S4ModuleData0012A070 0x00129F80. `one_identity.py --callers`
  names `??0OpenContainModuleData@@QAE@XZ` at 2 call sites plus the
  `BFMEFactoryModuleData<OpenContainModuleData, 0x168>` facade, and no
  caller names the Cave row.

## The deleting-destructor chains do not distinguish (documented, not evidence)

- Vtable 0x010AC338 slot 0 (VA 0x0041ED5D) reaches scalar 0x00227400, whose
  complete call (ILT 0x000376E1) lands in 0x00129E90.
- Vtable 0x0108F288 slot 0 (VA 0x00415B4F) reaches scalar 0x0012AB80, whose
  complete call (ILT 0x00019704) jumps to stub 0x0012ABB0 and from there to
  the same ILT 0x000376E1, i.e. the same complete body 0x00129E90.
- 0x00129E90 destroys exactly the bank's subobjects in reverse order
  (+0x158 vector, +0x120 / +0x11C lists, +0x118 / +0x114 handles, +0xA4 /
  +0x34 audio events; the +0x08 DieMuxData is trivially destructible) and
  never touches +0x168, then installs base vtable 0x01073744. A Cave
  complete destructor needs no distinct bytes (its +0x168 tail is a trivial
  Int), so both classes share this complete body and the chains cannot
  break the tie. The constructor vtable operand and the separate 0x0012AB50
  Cave constructor above are what decide it.

## Action

Retire `??0CaveContainModuleData@@QAE@XZ` at 0x00227200 (tombstone this
file as the reason) and land the banked `??0OpenContainModuleData@@QAE@XZ`
body (398 bytes, probes EXACT modulo relocations) in
`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainModuleDataCtorThunk.cpp`,
replacing its naked lift; delete the orphaned
`CaveContainModuleDataCtorThunk.cpp` naked copy.
