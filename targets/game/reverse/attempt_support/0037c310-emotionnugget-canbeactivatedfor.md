# 0x0037C310 EmotionNugget::CanBeActivatedFor (465 B), session 494 bank

Identity: tools/ilt_oracle.py CONFIRMS
`?CanBeActivatedFor@EmotionNugget@@QAE_NHHPBVObject@@@Z` at ILT 0x000466B4
(the `PAVObject`, `QBE` and lower-case spellings are CONTRADICTED). Donor lead:
open-bfme-2 b5a7b8290 Code/GameEngine/Source/GameLogic/Object/Update/
EmotionNuggetCanBeActivatedFor.cpp (494 B there). BFME 1 lacks its leading
testStatus(0x46), and its attribute query has a fixed kind 4.

Bank (attempts/0x0037c310.cpp): 467/465 B, 34 non-relocation diffs, all after
+0x1A8. Retail loads the target's AI (`mov ecx,[esi+0x204]`) straight into ECX
for getAIStateType. Ours loads it into ESI and adds a `mov ecx,esi`, so the
tail is 2 bytes longer.

Changes from the 0.43 bank that moved bytes (262 -> 41 -> 34 diffs):
- Read `data04->atXX` again at every test, as the donor does, instead of
  caching a `data` local. This fixes the EAX-pointer / CL-byte assignment
  across the whole first half. Keep a local only for the a/b weight block.
- Write `bonus < 0.5f` (fld bonus; fcomp 0.5). `0.5f > bonus` reverses the fcomp.

Inert for the final ECX/ESI choice (all 34 diffs): AI local, const AI local,
single or double inline accessor, direct m_ai, function-scope AI variable
shared with the head, forceinline predicate helper, a separate `unit` variable
for the redirected object, const Object*, `||` with !allowed, nested ifs,
`State45 ==` order, assignment in the condition. An int `allowed` is worse (111).

## Session 519 (claude-opus-5-5): the target map block decides ECX vs ESI

- Retail twin: `Rva002E6170ObjectRandomChance` (LuaScriptBindingsLuaA.cpp,
  0x2E6170+0x97) runs the same bonus + `m_ai && state == 0x2D` tail and gets
  `mov ecx,[esi+0x204]`. The bank's tail alone, compiled as a small member
  function in this TU (with the getF4 redirect), also gets ECX.
- Bisection on the bank: deleting the whole `if(target){...}` map block gives
  ECX; deleting either half (objects14 find/erase, or templates20 find/erase)
  also gives ECX; deleting only either erase keeps ESI; deleting the head
  blocks (at08/at09 AI, at2c/at2d) keeps ESI. So both map lookups together
  push the allocator over to ESI; the rest of the body is not the cause.
- Inert (34 diffs): scoped blocks around each lookup, find(target->m_id) /
  find(template) without key locals (worse: 210/175), frame re-read in the
  first compare, ObjectID enum key + BFME_HAVE_OBJECTID, data local in its own
  scope, flag assignment instead of early return (`allowed=false`; `return
  allowed` gives 33), non-const / int-returning getAIStateType, ternary
  redirect, forceinline helpers for the tail or for the map block.
- Lead: retail's second lookup calls `_Rb_tree::_M_find<unsigned short>`
  (0x37B060, returns the node in EAX), the first an sret `find` (0x2231C0).
  A map spelling with fewer inlined iterator temporaries is the next thing to
  try.
