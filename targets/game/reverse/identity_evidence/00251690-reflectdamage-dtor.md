# ReflectDamage destructor at RVA 0x00251690 (25 bytes)
Old: `?dup_00251690@@YAXXZ` (gen-alias of ??1TensileFormationUpdateBase@@UAE@XZ)
New: `??1ReflectDamage@@MAE@XZ`

The matched scalar deleting destructor ??_GReflectDamage@@MAEPAXI@Z
(ReflectDamageDeletingDestructor.cpp, RVA 0x00251800) calls this body through
ILT 0x00007C57, pinned ??1ReflectDamage@@MAE@XZ. tools/ilt_oracle.py check
??1ReflectDamage@@MAE@XZ 0x00251690: CONFIRMED exact.
The body stores vftable 0x010B1DC4 (recorded in dir32 as ??_7DamageModule@@6B@)
at +0x10, then the BehaviorModule tables 0x0109CB5C (+0) and 0x0109CA98 (+0xC),
and tail-jumps to ILT 0x00047C53, the ObjectModule destructor: the empty
destructor of a DamageModule (Zero Hour ReflectDamage derives from
DamageModule). Retail has no identical-COMDAT folding, so the address has one
identity and the TensileFormationUpdateBase alias claim is retired.
