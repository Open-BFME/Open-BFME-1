> Scratch paths under `build/wf/003c4490/` below are untracked session files and are not kept.

# 0x003C4490 LivingWorldLogic::DoXfer (542 B): still 16 diffs (session 2026-11-06)

Best candidate: unchanged bank `targets/game/reverse/attempts/0x003c4490.cpp`
(copy: `build/wf/003c4490/base.cpp`), symbol `?DoXfer@LivingWorldLogic@@UAEXAAVXfer@@@Z`,
`// cl: /DNDEBUG /MD /EHsc /Igame` (probe adds `/O2 /GR- /EHsc-`). The bank still
reproduces as logged: 542/542 B, 18 relocations, 16 non-reloc diffs, all in the
save tail +0x1F4..+0x214. About 170 new trials ended at exactly 16; the logs are
in `build/wf/003c4490/trials.log` and the scripts in `t*.py`.

## Remaining mismatch
```
retail                                   ours
01f4 mov edx,[TheGameLogic]              mov ecx,[TheGameLogic]
01fa cmp dword [edx+0x10c],8             cmp dword [ecx+0x10c],8
0201 setne al                            setne al
0204 mov edx,[esi]                       movzx edx,al
0206 movzx ecx,al                        mov eax,[esi]
0209 lea eax,[esp+0x14]                  lea ecx,[esp+0x14]
020d mov [esp+0x14],ecx                  push ecx / mov ecx,esi
0211 push eax / mov ecx,esi              mov [esp+0x18],edx
0214 call [edx+0x78]                     call [eax+0x78]
```
The instruction shape is identical. Only register choice differs, in the
version<2 arm (block2) and at the join.

## New diagnostic findings (measured; the cause is still an inference)
1. The join permutation follows directly from block2's pointer register. When
   block2 holds no pointer temp, or that temp lands in EAX, the join comes out
   exactly as retail does (vtable EDX, value ECX, address EAX). Seen with diagnostic
   bodies `x_else_member`, `d_true_member` and `d_true_one`. When block2's pointer
   is in ECX, all three join temps rotate. **To match, block2's TheGameLogic load
   has to land in EDX.**
2. Block2's register depends on code laid out before it, not on how the tail is
   spelled. Changing the load arm's reset block (`diag_stopaqa`: a non-virtual
   call in place of `reset(0)`; `diag_noreset`) moves block2's pointer to EDX.
   Changing the true arm's temps also moves it (EAX when block1 has no EAX temp).
   This looks like MSVC 7.1 steering away from registers that nearby code just
   used. Retail behaves as though ECX was also busy just before block2, with no
   visible instruction that uses it.
3. MSVC canonicalises every byte-neutral spelling tried below to the same IR, so
   none of them changes block2.

## Ruled out this session (all inert at 16 unless noted)
- (a) Control flow: ternary forms (`tern_uc`/`tern_ge`); switch on the version
  (49 and 71 diffs); goto layouts (48 or 16: MSVC re-lays out blocks); duplicated
  per-arm xfer calls (52 to 57); load arm as if/else in either order (16, or 40
  when the layout changes); `!state`.
- (b) Lifetime and scope: `int state; state=active`; copies through a value local;
  arg-assign `xfer == (state = active)` and its comma and pointer forms; `int*`
  alias; mode, pointer and logic locals per arm or shared at tail scope (sh_*);
  struct or array wrapper for `active`.
- (c) Types: helper return long, unsigned, unsigned long or short (16; char 47);
  unsigned mode; unsigned state; bool join (44); version via uchar, int or bool
  local or a reference; `reset` returning int, bool, uchar or void*, or taking
  bool.
- (d) Callee visibility: `__forceinline` state helpers taking the version (int,
  uchar or `const Version&`; plain `inline` is not inlined and costs 28 to 35
  diffs); nested uchar/bool-returning helpers (16 or 44); Xfer-derived view member
  helpers (inline and forceinline, uchar or int); GameLogic view members
  (`isActive`, `isNot8`, `getMode`, static); pointer, reference and no-argument
  helpers; else helpers returning int or unsigned. A direct member call in place
  of the PMF union for 0x003C0610 does not change the tail either.
- (e) Flags: /Ox /Ot /G6 /GA /Gy /GF /Gr /Op /Ob2 /Oi- /GS are inert; /Oa and /Ow
  give 32 diffs; /Os gives 406. Sibling LivingWorld TUs
  (`LivingWorldLogicConstructor.cpp`, `Transfer003C3D90.cpp`) use the same
  `/O2 /MD /EHsc` set and differ only in defines, so no sibling flag justifies a
  change.
- (f) Evaluation order: `8 != mode`, `!(mode==8)`, `mode==8 ? 0 : 1`, if/else
  setting 1/0, bool temp, `(int)(mode != 8)`; `||`, `&&`, if-chain, switch,
  result-local and ternary forms of the true-arm helper (16 or 47 to 58).
- (g) EH: none (no unwind map).
- Upstream byte-neutral variants: union-wrapped version storage, reset through
  a local or reference, `reset(false)`, `m_flag2D = 0`, `active == false`,
  inlined mode reads in the first version block. A 72-way cross product of
  true-arm, else-arm, join, reset and load-test spellings (`t34.py`) was all 16.
- BFME 2 donor (Open-BFME-2 6d03b6cd `LivingWorldLogic_xfer.cpp`): its tail is
  different (an `isSelectionLocked` branch, then `counterF0`) and offers no guide
  for this save arm.

## Next hypotheses (untested)
- Look for byte-neutral IR differences in the load arm's reset block that "use"
  ECX later than EDX, for example a `reset` reached through a class whose `this`
  adjustment is folded, or the fade/reset blocks emitted in a different IR order
  but the same layout. Finding 2 shows this region drives block2.
- A hidden ECX temp in block1, for example a helper whose IR keeps a separate
  return-value temp that is later coalesced into EAX.
