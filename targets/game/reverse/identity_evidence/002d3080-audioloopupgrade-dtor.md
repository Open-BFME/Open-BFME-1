# AudioLoopUpgrade complete destructor at 0x002D3080

The 141-byte body at 0x002D3080 was filed as `??1Rva002D3080@@UAE@XZ`. It is
`AudioLoopUpgrade::~AudioLoopUpgrade`.

BFME 1 target evidence:

- Its only caller is the matched scalar-deleting destructor
  `??_GAudioLoopUpgrade@@UAEPAXI@Z` (0x002D33B0), which calls through ILT
  0x000120F8; that ILT jumps to 0x002D3080.
- `symbols.csv` already pins `??1AudioLoopUpgrade@@UAE@XZ` at ILT 0x000120F8
  (T1-access, efp 4.24e-03); `pin_consistency.py --symbol` reports it
  consistent, routing to this body.
- `ilt_oracle.py check '??1AudioLoopUpgrade@@UAE@XZ' 0x002D3080`:
  CONFIRMED, p_false 8.48e-04 (exact).
- The body installs vtable VA 0x010CBE24 (RVA 0x00CCBE24). Its slots are the
  ledger's matched AudioLoopUpgrade rows (`??_GAudioLoopUpgrade` at slot 0,
  `getModuleNameKey`, `removeUpgrade`, `upgradeImplementation`), and the
  matched constructor `??0AudioLoopUpgrade` (0x002D32B0) allocates the same
  0x30-byte object whose +0x2C field this destructor hands to TheAudio.

Donor lead (not proof): BFME 2 (`inputs/reference/open-bfme-2`, revision
59e3f8f825) names its twin `??1AudioLoopUpgrade@@MAE@XZ` in
`Code/GameEngine/Source/GameLogic/Object/Upgrade/AudioLoopUpgradeDtor.cpp`,
with the same TheAudio removeAudioEvent call on the +0x2C handle. BFME 1 keeps
the public `UAE` spelling its own pin and caller already use.

The base and field placeholders (`Rva002D3080WithField`,
`Rva002D3080ExtraInterface`, `m_field2c`) stay opaque: only the class
identity is established here.

## Rename blocked (2026-11-02)

Renaming the row and class to `??1AudioLoopUpgrade@@UAE@XZ` byte-matches
(141/141) but fails the DIR32 gate. The body stores five AudioLoopUpgrade
vftables and then two inlined BehaviorModule vftables (0x0109CB5C, 0x0109CA98).

- Class rename alone emits `??_7AudioLoopUpgrade@@6BObjectModule@@@` etc.; those
  VAs are already recorded as `??_7AudioLoopUpgrade@@6BALU_DeepBase@@@`,
  `6BALU_Iface1`, `6BALU_Iface2`, `6BALU_UpgradeMux` and `6BALU_Iface4` (from
  AudioLoopUpgradeCtorModuleFactory.cpp), and the gate refuses a second name.
- Renaming this TU's bases to those `ALU_*` names fixes three of them, but then
  the inlined BehaviorModule stores become `??_7BehaviorModule@@6BALU_DeepBase@@@`
  and `6BALU_Iface1`, which are not recorded. MSVC names both classes' vftables
  after the same split-point bases, so no private view gives both recorded names.
  `6BUpdateModule` and `6B@` also persisted for the +0x28 and UpdateModule
  subobjects.

To unblock: give the AudioLoopUpgrade ctor and dtor TUs one shared class view
whose base names produce one name per vftable. That means re-recording names
through the full gate's `dir32_record.py record` path and retiring the
`Rva002D3080`/`ALU_*` aliases. That is a cross-TU class reconciliation, not a
row rename.
