# BridgeTowerBehavior destructor at RVA 0x001F5F70 (39 bytes)
Old: `??1Rva001F5F70DeepDtor@@UAE@XZ`
New: `??1BridgeTowerBehavior@@MAE@XZ`

The matched scalar deleting destructor ??_GBridgeTowerBehavior@@MAEPAXI@Z
(BridgeTowerBehaviorDeletingDestructor.cpp, RVA 0x001F6180) calls this body
through ILT 0x00012F44. tools/ilt_oracle.py check ??1BridgeTowerBehavior@@MAE@XZ
0x001F5F70: CONFIRMED exact.
The body stores vftables 0x010A2A7C/2A78/2A68 at +0x10/+0x14/+0x18, which
dir32_addresses.csv records as ??_7BridgeTowerBehavior@@6BBridgeTowerBehaviorIface2/3/4@@@
(installed by the matched constructor), then the inlined BehaviorModule
teardown (0x0109CB5C at +0, 0x0109CA98 at +0xC, as in ~WargBehavior) and
tail-jumps to ILT 0x00047C53, the ObjectModule destructor.
The Zero Hour BridgeTowerBehavior.cpp definition (unmatched, selected by the
link over retail's) is removed; that TU now only declares it.
