# ??1RefHandle008958D0 (retail 0x00784A70, 35 B; ILT 0x000463AD) — select-any dtor COMDAT losers, no source lever remains

Session 2026-11-04, link queue #9, census aafdf413e9 (2026-11-03 13:29). Prior
blocks: re_attempts.log entries 54799, 55845, 56260, 56351, 56363, 56629,
57142, 57263, 57421, 57808, 57819, 57824, 58979, 59047, 59214, 59238, 60079 and
handoff `refhandle008958d0-inline-depth-20261028.md`.

## Target

Three consumer TUs emit non-retail select-any copies of the
`RefHandle008958D0` destructor; the census charges them (kind `losers`,
`link_check.py`: `comdat ??1RefHandle008958D0@@QAE@XZ (retail: not retail's
body)` on all three):

- `game/GameEngine/Source/Common/Rva00893030ManagerFind.cpp` (in-class dtor,
  line 105; parent 0x00895950, 163 B)
- `game/Libraries/Source/Apt/Rva00895A00CreateHandle.cpp` (`__forceinline`
  out-of-class dtor, lines 87-92, `absent-from-retail`; parent 0x00895A00,
  274 B)
- `game/Libraries/Source/Apt/Rva00895B20Dependencies.cpp` (in-class dtor,
  line 42; method 0x00895B20, 294 B)

Retail keeps one 35 B copy (ledger row 172305,
`game/GameEngine/Source/Common/Rva00784A70Cleanup.cpp`) reached through ILT
0x000463AD (`targets/game/reverse/identity_evidence/00784a70-refhandle008958d0-dtor.md`).
Selection was already fixed in 4e5f307: the kept copy is now retail's, so the
linked image is right; the charge is purely the census counting the three
loser copies (entry 59047).

## The essential single-TU contradiction

The retail image is self-consistent only because the TU(s) that own the matched
parents and the TU that provides the kept COMDAT are DIFFERENT, with DIFFERENT
dtor bodies:

- The matched parents require the dtor INLINED at the scope-exit drop site in
  the inlined call-helper shape. Find parent 0x00895950 at 0x008959C7:
  `dec [esi]; jne; mov ecx,esi; call 0x895260 (~BfmeDropObjectA);
  push 0x18; push esi; call [0x1337830] (TheBfmeFree); add esp,8` — the inline
  expansion of `if (p && --p->m_refCount == 0) { p->~BfmeDropObjectA();
  TheBfmeFree(p,24); }`. Create parent 0x00895A00 drops both of its class
  locals (bare `dec` for `found` at 0x00895A53-5A, proven nonzero after the
  copy-ctor `inc`; full drop for `made` at 0x00895ADD-8). Deps parent
  0x00895B20 drops its `RefHandle008958D0` temp at 0x00895BAA-8 (the second
  drop at 0x00895C0E belongs to `Rva00895B20Ref`, a different symbol,
  uncharged and untouched).
- The kept retail COMDAT (0x00784A70, 35 B) is the OUT-OF-LINE helper-call
  shape: `push esi; mov esi,ecx; mov eax,[esi]; test eax,eax; je; push eax;
  call 0x894D90 (decrement); add esp,4; test eax,eax; jne; mov eax,[esi];
  push eax; call 0x895320 (bfmeDropA); add esp,4; pop esi; ret`.

One source dtor body compiles to one out-of-line shape (the COMDAT) and
inlines into the parent scope-exit as the inline expansion of that SAME body.
It cannot be the helper-call shape (for the COMDAT) and the call-helper shape
(for the parents' inline tails) at once. No single TU can emit both. The
funclet `$L` rows are not the wall: their jmp target is relocation-masked in
the byte gate, so the target symbol is free — but a dtor defined in the TU plus
any out-of-line use of it forces the select-any copy regardless.

## Current HEAD, byte-verified this session

With the call-helper dtor source, the Find object's COMDAT copy is 35 B but
differs from retail's 35 B (inlined `dec [esi]` + object dtor + free instead
of retail's out-of-line helper calls):

```
56 8b31 85f6 7417 ff0e 7513 8bce e8???????? 6a18 56 ff15???????? 83c408 5e c3
push esi; mov esi,[ecx]; test esi,esi; je end; dec [esi]; jne end;
mov ecx,esi; call ??1BfmeDropObjectA; push 0x18; push esi; call [TheBfmeFree];
add esp,8; end: pop esi; ret
relocs: (14,20,??1BfmeDropObjectA@@QAE@XZ) (23,6,?TheBfmeFree@@3P6AXPAXI@ZA)
```

verdict `wrong` (keep_rule, tools/link_census.py:962-997: `loses[obj] =
verdict == "wrong"` absolute, since the symbol has a retail address). Parents
match exactly (the drop is the inlined expansion of the same body), so this
form is parent-good / COMDAT-bad — the current census charge.

## Levers tested and ruled out

| Lever | COMDAT | Parents | Verdict |
|---|---|---|---|
| Call-helper dtor (current HEAD) | 35 B, `wrong` | exact | losers charged |
| Helper-call dtor (decrement + noinline bfmeDropA; digest 3e30e419f464) | EXACT retail 35 B | inline `push; call decrement; add esp,4; ... call bfmeDropA` instead of retail's inline tail -> Find parent 162 B, FAIL (entries 56351, 57142) | parents break |
| dllimport + `__forceinline` dtor (suppress the copy) | suppressed | every EH funclet reference becomes a 6-byte FF25 through `__imp_??1RefHandle008958D0` (retail funclet: 5-byte e9 to ILT 0x463AD); Find .text$x 43 B vs 45 B, parent FAIL (entry 57142) | reverted |
| Declared-only dtor (no body in TU) | none (external `??1X`) | normal-path scope exit emits `call ??1X` (DIR32, reloc off 48) + `lea ecx,[esp]; mov [esp+0xc],-1` state store instead of the inline tail -> parents FAIL | parents break |
| `#pragma intrinsic(X::~X)` on declared-only (NEW, this session) | none (external) | INERT: probe 2 body byte-identical to probe 1; the normal-path `call ??1X` remains | ruled out |
| inline_depth / auto_inline placement, `__forceinline` (2026-10-28 handoff) | EXACT under depth(0)/auto_inline(off) | parents then `call ??1` (273 B) or keep the 38 B copy; MSVC 7.1 inlines a chain-level-k call only when k <= the recorded depth of every caller: retail needs the dtor at depth 0 (copy) and >= 2 (parents) | one TU cannot satisfy both |

## Decisive intrinsic probe (build/probe-intrinsic/, VC7.1, /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc)

- probe1_declonly (declared-only dtor, no intrinsic): NO COMDAT (`??1X`
  external, sec=0 storage=2); `$L299` funclet = `lea ecx,[ebp-0x10]; jmp` with
  DIR32 (type 20) reloc at offset 4 to external `??1X` — the retail funclet
  shape, target masked; f1 normal path keeps the out-of-line `call ??1X`
  (DIR32 reloc offset 48).
- probe2_intrinsic (declared-only + `#pragma intrinsic(X::~X)`): VC7.1 accepts
  the member syntax (compiles rc=0) and the object is byte-identical to probe
  1: no COMDAT, `??1X` still external, f2 body identical — the normal-path
  `call ??1X` (reloc offset 48) and the state store are STILL emitted. The
  intrinsic is inert on a declared-only dtor.
- probe3_inclass (in-class dtor, provably dead `p==0`): f3 normal path emits
  NOTHING (no call, no drop — the drop is provably dead) yet a 10 B select-any
  COMDAT of `??1X` is still emitted (`8b01 85c0 7403 48 8901 c3`, no relocs).
  MSVC emits the select-any copy of every in-class dtor a unit uses even when
  it inlined the call or the drop is dead (keep_rule docstring).

Consequences: the normal-path call cannot be elided while keeping the EH
funclet, the COMDAT cannot be suppressed while the dtor is defined in the TU,
and a defined-in-TU dtor (in any body form) that the parent inlines still
emits a charged copy. The `unreferenced` census exemption does not apply: it
requires retail truth unable to judge the symbol AND no references; this symbol
has a retail address (row 172305) and its verdicts are not all-None.

## Donor evidence (read-only, open-bfme-2 @ f6d845ec)

- `reverse/attempt_support/folded-handle-guard-link-20261022/readme.md`: the
  same family — "main paths need the out-of-line Release call, while retail's
  kept cleanup copy inlines it" — was resolved in BFME 2 by the census
  ADMISSION rule (retail-truth-3: "wrong discarded copies are admitted when the
  kept provider is retail"), NOT by a source fix; BFME 2's kept copies there
  are 5 B jmp thunks (0x000A9DF3), whereas BFME 1's kept copy is a real 35 B
  body. BFME 1 has no such admission rule (keep_rule 962-997) — a rule change
  is a Verifier-Change + census_rebaseline, out of scope for this lane.
- BFME 2's current donor revision provides no same-name provider for this dtor
  (entry 57808); the prior suppression donor is inapplicable to the required
  25 B sret unwind actions (entry 57263).

## Verdict

BLOCKED at the source level. The three Apt TUs' select-any dtor COMDATs are
inherent losers: retail's own Apt TUs shipped these divergent copies and lost
them to the 0x00784A70 copy at link time (entry 59047, 60079; the UnicodeString
case 59653 is the same pattern). No clean C++ shape, pragma, intrinsic, or
suppression keeps the matched parents' inlined tails while emitting a
retail-shaped (or no) reachable COMDAT. The AGENTS.md "remove a wrong
definition nothing verified needs" remedy does not apply: the in-TU dtor
definition IS needed by the verified parents (their inlined drop sites).
Resume condition: a census admission for wrong discarded copies when the kept
provider is retail (BFME 2 retail-truth-3), or a new codegen lever that
elides the select-any copy without changing the parent normal path or the EH
funclets.

Boundary: matched 35 B retail cleanup via ILT 0x000463AD; parents 0x00895950
(163 B), 0x00895A00 (274 B), 0x00895B20 (294 B) exact at HEAD
(766fa97385); Find scoped gate 3/3; link_check before/after census aafdf413e9
identical on the three files. model=qwen38-27b-ninfer
blocker=comdat-losers-no-source-lever

## Upstream reconciliation (2026-11-13, origin/master 9b03111301)

This session resumed after a 9-day pause; origin/master advanced 1828 commits
(766fa97385 -> 9b03111301). No AGENTS.md or docs/matching.md edits in the
range; no commit touched tools/link_census.py or tools/census_rebaseline.py,
so the census admission rule still has not landed and the current queue entry
(link_queue.csv rank 19, 552 B) lists only two emitters now:

- Suppressed upstream: `e3fda96dc8` (2026-11-11, "[BFME 2 donor] Suppress
  unused Apt dependency handle destructor") landed the Deps suppression —
  `Rva00895B20Dependencies.cpp` got `__declspec(dllimport) __forceinline` on
  its in-class dtor. It works because that TU never ODR-uses the dtor (its
  method inlines the drop; no funclet or call reloc references the symbol; the
  34 B COMDAT there is an orphan).
- Sharper suppression rule proven upstream (attempt_support
  `20261112-used-dtor-suppression-block.md`, muse-spark-1.3, 2026-11-12):
  `__declspec(dllimport) __forceinline` suppresses the COMDAT only when the
  TU never ODR-uses the dtor. When used — even with every use inlined and zero
  call relocs — MSVC 7.1 emits a dangling `__imp_<dtor>` undefined symbol;
  link_check `excused()` covers an `__imp_` name only when retail imports that
  function (tools/link_census.py:2167), and a game dtor is never a retail
  import, so suppression trades the loser for an unresolved blocker. That
  upstream seat confirmed the same failure modes I measured: ManagerFind
  dllimport drops the pinned $L458 funclet (row loses its anchor); CreateHandle
  dllimport on the out-of-line body is C2264 (deleting the body reroutes
  rva00895A00's cleanup to a local 0xC57CD6).
- My session's intrinsic probe (this note above) remains the only new lever
  not covered by the upstream analysis, and it is inert: for the remaining
  Find + CreateHandle emitters the conclusion is unchanged — the in-TU dtor
  definition is load-bearing for the matched parents' inlined drop sites, and
  a used, defined-in-TU dtor cannot avoid the charged select-any copy.

Resume condition (updated): the census admission for wrong discarded copies
when the kept provider is retail (BFME 2 retail-truth-3; still absent in BFME
1), or a codegen path that keeps the parent's inlined drop while the TU stops
ODR-using the dtor — the matched parents forbid it.
