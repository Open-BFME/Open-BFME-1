# WallUpgradeUpdate destructor at RVA 0x002B2100 (39 bytes)
Old: `??1Rva002B2100DeepDtor@@UAE@XZ`
New: `??1WallUpgradeUpdate@@MAE@XZ`

The matched scalar deleting destructor ??_GWallUpgradeUpdate@@MAEPAXI@Z
(WallUpgradeUpdateDeletingDestructor.cpp, RVA 0x002B2410) calls this body
through ILT 0x0002575C, which symbols.csv pins as ??1WallUpgradeUpdate@@MAE@XZ.
tools/ilt_oracle.py check ??1WallUpgradeUpdate@@MAE@XZ 0x002B2100: CONFIRMED exact.
The body stores vftables 0x010C51BC (+0x20) and 0x010C51B8 (+0x24), which
dir32_addresses.csv records as ??_7WallUpgradeUpdate@@6BWUU_Iface3@@@ and
??_7WallUpgradeUpdate@@6BWUU_Iface4@@@, then the inlined UpdateModule teardown
(0x0109CBAC at +0x10, 0x0109CB5C at +0, 0x0109CA98 at +0xC, the same stores as
the UpdateModule-derived ~RampageBehavior) and tail-jumps to ILT 0x00047C53,
the ObjectModule destructor.
