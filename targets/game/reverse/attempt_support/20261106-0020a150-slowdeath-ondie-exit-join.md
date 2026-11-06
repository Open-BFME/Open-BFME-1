# 0x0020A150 SlowDeathBehavior::onDie: still 842/842 B, 4 bytes (wf session, claude-opus-5-5)

Best candidate: build/wf/0020a150/base.cpp, identical to the bank
targets/game/reverse/attempts/0x0020a150.cpp. It defines
`?onDie@SlowDeathBehavior@@UAEXPBVDamageInfo@@@Z`, and the probe reproduces the
logged result (842 B, 4 non-reloc bytes at +0x1AF, shape 1.000).
cl: `/DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB` + `// stlport` (build.py adds -O2 -GR- -EHsc-).

## Remaining mismatch
```
  01ad 75 42        jne 0x1f1        | same
!!01af 8b 54 24 30  mov edx,[esp+30] | mov ecx,[esp+24]   (probabilities eos / behaviors eos)
!!01b3 8b 4c 24 24  mov ecx,[esp+24] | mov edx,[esp+30]
  01b7 8b 74 24 1c  mov esi,[esp+1c] | same
```
This is the loop-2 exit block J. Both exits (+0x1AD and the jmp at +0x27C) go through it.
It reloads the two eos values that K (the scope-end dtors, reached from the no-modules
`je +0x1B7` with the zero registers ecx/edx) expects to find in registers.

## New diagnostic evidence (not equivalent source; used only to locate the cause)
- J order follows the loop-2 register solution. Removing any loop-2 call flips J to
  retail's order: `slot0C` (J_noslot0c), `isDieApplicable` (R5), `beginSlowDeath` on the
  return path (R6). Removing `probabilities[index]=back();pop_back()` also flips it. Every
  one of these flips also changes the loop-2 allocation: index moves ebp->edi, sdu moves
  edi->ebp, and `sub ebp,[ecx]` becomes `mov eax,[ecx]`. Retail has the ebp/edi solution
  together with the (edx,ecx) J order, a combination no compile has produced.
- In the R6 (no beginSlowDeath) space, 28 spelling variants all keep the (edx,ecx) order.
  In the full-body space, about 110 variants all keep (ecx,edx). The order therefore
  depends on the set of calls and webs, not on spelling.
- Inert, so not a hash or context effect: renaming locals and vectors, extra headers
  (<map>/<list>/<string>/CRT), 300 dummy classes, 1000 dummy declarations, and adding
  calls before the vectors, between the loops or inside either loop.
- Swapped declaration order (prior work: 698 B) puts J in destruction order. So does the base.

## Families tested this session (all 4 B, i.e. inert, unless noted)
(a) control flow: while(true)/for(;;)+break or return (848/370), goto loop, begin!=end and
end!=begin (7), if/else in either order, split nested ifs, `!x||!y||!z` continue
(817), chosen-pointer break + call after loop (748: merges the dtor copies, so retail
really returns inside the loop), found flag (754), roll loop as while / `&&` cond / raw pointer.
(b) lifetime: index/probability/all locals hoisted, sdu shared by both loops, `obj` in a
block, `ai` in the if-init, index declared before total update (847), no index var (892),
`*it = back()` (886), `sdu` as reference into the vector (845), condition into a Bool (837),
named `hi` for total-1 (63).
(c) types: index unsigned, const_iterator, total unsigned or long, roll long, vector<long>,
vector<unsigned> + cast, vector<void*> (849), slot0C const/char, const prob, MI
BehaviorModule (ObjectModule + BehaviorModuleInterface base, same bytes, more authentic),
real AI/Object/ThingTemplate members in place of at<> views.
(d) visibility: `extern template` of both vectors (insert_overflow is in-class inline,
so it stays visible), throw() or extern "C" on the random call and the virtuals,
swapRemove inline helper, std::distance, receivers through behaviors[index] (849/888/686).
(e) flags: parseSound sibling `/O2 /Ob1 /DWIN32 /D_WINDOWS` (SlowDeathBehavior_parseSound.cpp),
/DWIN32, /Ob2, /Ox, /GX, /GF /Gy, /GR, /Zi, /Z7, /Gs, /Oi, /Op; /G7 (484), /EHa (112).
(f) order: `total` add after or between the push_backs (675/688), `total = total - *it`.
(g) EH: retail FuncInfo has 2 unwind states (vector<Int> then vector<T*>), the same as ours. There is no EH lever.

Donor: Open-BFME-2 master SlowDeathBehaviorUpdate.cpp onDie (0x0045E6B8, VC8 build) has the same
two-vector loop as the bank (rva0050B5C6 = our slot0C). It offers no new structure.

## Suggested next steps
The residue is a pure allocation-order artifact that ~140 source and flag variants cannot move.
The options left are compiler-internal: a different 13.10 build, or an unknown second
web in retail's IL. Leave this body at 0.9952, or land it under a documented
compiler-quirk exception if project policy allows. trials.log in this directory lists every probe.
