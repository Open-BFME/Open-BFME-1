# 0x003CB640 LivingWorldRegionManager::rva003CB640 (248 B) — session 493 bank

New finding (BFME 1 target evidence): the loop body inlines the obfuscated
hook wrapper `Rva003C92A0` (BigObfHookWrappers.cpp, slot g_Slot012BE394,
state Obf003C87A0, fallback Gen003C78B0) with both arguments = region +0xB4.
Earlier attempts (24 verdicts) modelled it as an opaque callback.

Semantics: clear this+0x34/0x38/0x3C; for i < m_campaign(+4)->regions(+0x30
vector of pointers).size(): if wrapper(key,key) == 1 then
+0x34 += region+0x7C, +0x38 += region+0x78, +0x3C += region+0x80.

Trials (flags /DNDEBUG /MD, probe shape):
- inline wrapper function called from the loop: 231 B, 0.793; totals schedule
  sequential; `this` in EBX, hook ESI, &vector fully spilled.
- manual inline with goto in the loop body (stash): 252 B, 0.830; totals
  interleaving now matches retail; hook compared against a hoisted zero register
  (xor ecx,ecx) and i lives in memory.
- inert: pa/pb read order, key local, static/forceinline wrapper, pointer vs
  reference to the vector, temps for the totals, b-before-a, result local,
  continue-form, /EHsc /DWIN32. Worse: /G7, /O1, re-reading key for b.
Retail allocation: this ESI, region EDI, &vector EBX and i EBP, both spilled
(slots +0x1C/+0x10) around the hot block where EBX = hook and EBP = pa;
frame 0x38 with one unexplained slot at +0x20.
