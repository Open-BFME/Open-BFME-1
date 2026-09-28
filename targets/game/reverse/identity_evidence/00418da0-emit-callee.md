# 0x00418DA0 Drawable::Drawable: the ILT 0x0002CB79 callee

The retired bank (`targets/game/reverse/attempts/0x00418da0.cpp`) spelled the
call at +0x97C as `DrawableEmitterCall::emit(void *, bool)` and bound it with a
`/alternatename` directive to `?j_0002cb79@@YAXXZ`. build.py does not read
`/alternatename`, so that spelling never resolved, and no evidence ties the
callee to an "emitter": the body it reaches, 0x00417710, is still the
unidentified gen dump `?d_00417710@@YAXXZ` (functions.csv), and callees.py
infers only `__thiscall`, two stack slots, result unused.

The only resolvable spelling for ILT 0x0002CB79 is the existing
`symbols.csv` pin `?bfmeEmit@Gen_00417cb0@@AAEXPAX0@Z` (address-derived family
name). The landed constructor
(`game/GameEngine/Source/GameClient/DrawableConstructor.cpp`) uses that pinned
spelling unchanged and asserts nothing further about the callee.

Retail call shape (+0x961..+0x97C): `m_object ? m_object->[+0x200]->vslot(0x20)
: 0` is pushed with a literal 0, `ecx = this`, then `call 0x0002CB79`.
