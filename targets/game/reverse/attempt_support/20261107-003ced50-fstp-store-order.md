# 0x003CED50 LargeGroupAudioMap::LargeGroupAudioMap(AsciiString) - handoff (2026-11-07, claude-opus-5-5)

> The best candidate (`build/wf/003ced50/best.cpp`, untracked scratch) is banked as `targets/game/reverse/attempts/0x003ced50.cpp`. Other `build/wf/003ced50/` paths below are scratch and are not kept.

Symbol: `??0LargeGroupAudioMap@@QAE@VAsciiString@@@Z`, 290 B, ret 4. Ledger row still
`?d_003ced50@@YAXXZ` (gen_asm). Bank `targets/game/reverse/attempts/0x003ced50.cpp`
reproduces exactly as logged: 290/290, 8 non-reloc bytes, score 0.9724.
Best candidate: `build/wf/003ced50/base.cpp` (identical to the bank). Flags: `/DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib`.

## Remaining mismatch (only one)

```
retail                                    ours
+00cb mov [esi+0xa0], eax                 mov [esi+0xa0], eax     (last -1.0f cache store)
+00d1 mov eax, 0x7fffffff                 fstp dword ptr [esi+0x10]
+00d6 fstp dword ptr [esi+0x10]           mov eax, 0x7fffffff
+00d9 lea ecx, [esp+0x1c]                 lea ecx, [esp+0x1c]
```

## What controls fstp placement (measured this session)

* fld/fmul are always hoisted to just after the AsciiString copy-ctor call (needs a
  TU-local `static float`; anon-namespace/extern pins the fld after the stores, 126 diffs).
* fstp is emitted at the first slot after the last store it cannot move above, and is
  always picked ahead of a pending `mov eax, imm`:
  - cache written directly (`m_c.m_value[1] = -1.0f; ...`, chained `a = b = -1.0f`, or an
    inline member function of LargeGroupAudioMap): fstp jumps above `mov eax,0xbf800000`
    (37 diffs).
  - cache written through any derived pointer (struct `reset()`, member-struct ctor,
    `float *c = m_value`, `SpeedCache &c`, two pair-structs, `reset(float v)`): fstp lands
    right after the 4th cache store and still before `mov eax,0x7fffffff` (8 diffs).
  - integer stores through an inner struct pointer (thresholds via `m_th.set()`, or inside
    the cache reset) are barriers for later stores in source order: fstp then follows
    st+0x90 (14-38 diffs). The fstp itself through a struct pointer (`m_ss.setSpeed()`)
    is inert.
* Position of the speed statement after the cache reset is irrelevant (all 8).

## Ruled out this session (all measured with probe.py; scratch under build/wf/003ced50/v*/)

| family | change | result |
|---|---|---|
| control flow / order | all 24 orders of {reset, thresholds, speed, size} + 6 speed-last orders | 8 best (R first, T before Z), others 24-57 |
| lifetime/scope | speed local at top, speed local assigned last, `const int` threshold local, threshold block scope, 1-8 unused int/float locals | 8 |
| types | unsigned/long thresholds, `(unsigned)-1>>1`, readback `stop = start`, `true` for byte, double product (fmul qword, 9) | 8 / worse |
| layout/views | Tail struct (thresholds+H+cache) reset/ctor, threshold pair struct (value/set/ctor), SizeSpeed struct + Thresholds struct with inline setters for every subset of T/S/Z/H (62+56 variants), two SpeedPair halves (direct/ptr mixes), temporary-struct assignment | 8 best; others 12-71 |
| callee visibility | inline `convertVelocity(v)` by value/ref/static/with temp, inline getter of the scale, function-local static, anon namespace | 8 (anon 126) |
| member ctors | ConditionFlags/StatusBits memset(this), clear(), byte counts; loop (154), field stores (112) | 8 / worse |
| flags | /Ox /Ob1 /Gy /GF /Og /Ot /GA /Gr /GB (8); /Oy- (286 B); /G7 /arch:SSE (313 B) | no change |
| ablation (diagnostic) | remove size/H stores, three threshold uses | fstp still first |
| donor | BFME 2 `LargeGroupAudioAudioMap.cpp` (dbde7dbe) ctor order; BFME 2 retail 0x003EE0CF is SSE code, no x87 schedule evidence | no transfer |

Previously logged (not repeated): Overridable base, TU-local static scale, *= compound,
chained thresholds, volatile stores, real STLport vector, G5/G6/G7, Op/Oi/Oa/Ow.

## Assessment / next hypotheses

The scheduler always issues the x87 store ahead of a register-only constant load when both
become ready at the same point. Retail needs the fstp to become ready strictly after
`mov eax,0x7fffffff`, i.e. a dependency that ends between them, or a priority (height)
difference we have not reproduced. Untested ideas: a different alias source for the cache
barrier (e.g. a cache owned by a base/second class reached through a cast), EA's real
member types for the cache (copy helper 0x003D21C0 resets it in the same [1],[0],[3],[2]
order, so a shared inline reset is plausible), or a header-level inline the real TU had.
