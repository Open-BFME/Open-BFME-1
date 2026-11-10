# 0x001F6250 BridgeTowerBehavior::onDamage: EXACT

Best candidate: build/wf/001f6250/best.cpp
(`?onDamage@BridgeTowerBehavior@@UAEXPAVDamageInfo@@@Z`, 514/514 bytes, probe
`result EXACT (modulo relocation slots)`). Flags are unchanged from the bank and
from the matched sibling BridgeTowerBehaviorOnHealing.cpp:
`// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-` + `// stlport` (build.py adds -O2 -GR- -EHsc-).

## What fixed it
The residue that went from 62 bytes to 4 bytes came from how the source template was written.
The bank spelled Object::isKindOf as an open-coded `if (t && t->m_nextOverride) t = t->m_nextOverride->getFinalOverride();`
with an opaque out-of-line getFinalOverride declaration. Zero Hour's actual shape
fixes the EBX/EBP partition, and the direct-argument source lookup then emits
retail's `mov ecx,[ebx+8]; push ecx; mov ecx,TheGameLogic`. That shape is:
- `Overridable::getFinalOverride() const` is inline and recursive
  (`if (m_nextOverride) return m_nextOverride->getFinalOverride(); return this;`).
- `Thing::m_template` is `OVERRIDE<ThingTemplate>`, whose `operator->` / `operator const T*`
  does `if (!m_obj) return 0; return (T*)m_obj->getFinalOverride();`.
- Object::isKindOf is `getTemplate()->isKindOf(type)`.

This is the same view as the matched DrawableGetHealthBoxPosition.cpp. The 
`sourceID` local copy was removed. ZH's direct `findObjectByID(damageInfo->in.m_sourceID)` is now exact.

Measured: best_ovr_a (operator-> directly) EXACT; best_ovr_b/best.cpp (getTemplate()) EXACT;
same OVERRIDE change on the 4-diff local-copy bank: still 4 (the local copy was the wrong lever).
v/ovr_allinline.cpp: plain inline findObjectByID at all three sites is also EXACT. The VC7.1 inliner
inlines only the loop call site. That copy emits a COMDAT `?findObjectByID@GameLogic@@QAEPAVObject@@W4ObjectID@@@Z`
that is identical to retail 0x0009A510 (82 B EXACT). best.cpp keeps the bank's opaque declaration and the forceinline
loop helper, so it does not emit that extra symbol.

## Ruled out this session
- Plain inline findObjectByID at all sites with the old isKindOf view: 62 (v/v1, v/v2).
- Prior sessions (see re_attempts.log) exhausted declaration order, loop forms, register
  params, aliases, flags, typed fastcall views, visible noinline lookup/override, and factored helpers.
  The earlier "override_default_inline 534/321" trial lacked OVERRIDE's null-test wrapper.

## Landing notes (read-only checks done)
(a) `ilt_oracle.py check '?onDamage@BridgeTowerBehavior@@UAEXPAVDamageInfo@@@Z' 0x001F6250` -> CONFIRMED (exact).
(b) Emitted helper COMDATs:
`?getFinalOverride@Overridable@@QBEPBV1@XZ` probed against its row 0x00087A80 (INIWater.cpp) gives 26/26 EXACT, so it is
retail-identical. No findObjectByID COMDAT is emitted, because it is declared opaque and the loop helper is __forceinline.
(c) Relocations bind to recorded names. `?TheGameLogic@@3PAVGameLogic@@A` is in data_rows.csv at 0x012F0898.
`?findObjectByID@GameLogic@@QAEPAVObject@@W4ObjectID@@@Z` is pinned at ILT 0x0001F253 in symbols.csv.
`?getFinalOverride@Overridable@@QBEPBV1@XZ` is pinned at ILT 0x000022BB (route=0x00087A80).
`??0DamageInfo@@QAE@XZ` is pinned at 0x0002C9D5, with its row at 0x000ED430.
(d) TU: new game/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehaviorOnDamage.cpp,
mirroring the sibling BridgeTowerBehaviorOnHealing.cpp with the same flags. Replace the gen row with
`--replace-rva 0x001F6250` (current row `?d_001f6250@@YAXXZ` in game/gen_asm/d_001db160.asm).
The TU keeps local views (GameLogic, Object, Overridable, ThingTemplate, OVERRIDE). The shared
GameLogicObjectLookup.h cannot be used: its private m_objHash plus int ObjectID gives no way to
inline only the loop site. The unused DamageInfoInput::m_sourceTemplate is still declared as a pointer;
retail's field is 16-bit plus padding (see identity_evidence/001f6250-helper-visibility.md). It is unused here.
