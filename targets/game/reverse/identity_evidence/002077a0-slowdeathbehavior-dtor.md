# SlowDeathBehavior destructor at RVA 0x002077A0 (39 bytes)
Old: `??1Rva002077A0DeepDtor@@UAE@XZ`
New: `??1SlowDeathBehavior@@MAE@XZ`

The matched scalar deleting destructor ??_GSlowDeathBehavior@@MAEPAXI@Z
(SlowDeathBehaviorDeletingDestructor.cpp, RVA 0x00207DA0) calls this body
through ILT 0x00032691. tools/ilt_oracle.py check ??1SlowDeathBehavior@@MAE@XZ
0x002077A0: CONFIRMED exact.
The body stores vftables 0x010A65B8 (+0x20) and 0x010A65A4 (+0x24), which
dir32_addresses.csv records as ??_7SlowDeathBehavior@@6BSlowDeathBehaviorInterface@@@
and ??_7SlowDeathBehavior@@6BDieModuleInterface@@@, then the inlined
UpdateModule teardown (0x0109CBAC at +0x10, 0x0109CB5C at +0, 0x0109CA98 at
+0xC, as in ~RampageBehavior and ~WallUpgradeUpdate) and tail-jumps to ILT
0x00047C53, the ObjectModule destructor.
The Zero Hour SlowDeathBehavior.cpp definition (unmatched, selected by the
link over retail's) is removed; that TU now only declares it.
