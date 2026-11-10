# 0x0020A150 SlowDeathBehavior::onDie: still 842/842 B, 4 bytes (wf session 3, claude-opus-5-5)

> `build/wf/0020a150/` paths below are untracked scratch and are not kept. The banked source is `targets/game/reverse/attempts/0x0020a150.cpp`.

Earlier handoffs (read them first; this note does not repeat them):
targets/game/reverse/attempt_support/20261030-0020a150-slowdeath-ondie.md and
targets/game/reverse/attempt_support/20261106-0020a150-slowdeath-ondie-exit-join.md.

Best candidate: build/wf/0020a150/s3/base.cpp. It is byte-identical to the bank
targets/game/reverse/attempts/0x0020a150.cpp and defines
`?onDie@SlowDeathBehavior@@UAEXPBVDamageInfo@@@Z`. The bank still reproduces as logged:
842 B, 4 non-reloc bytes at +0x1AF, shape 1.000.
cl: `/DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB` plus `// stlport` (STLport 4.5.3 and the BFME overlay).

## Remaining mismatch (unchanged)
```
  01ad 75 42        jne 0x1f1         | same
!!01af 8b 54 24 30  mov edx,[esp+30]  | mov ecx,[esp+24]   (probabilities eos / behaviors eos)
!!01b3 8b 4c 24 24  mov ecx,[esp+24]  | mov edx,[esp+30]
  01b7 8b 74 24 1c  mov esi,[esp+1c]  | same
```

## New evidence this session
- Compiler build: the retail lotrbfme.exe Rich header lists 1266 objects from
  Utc1310_CPP (prod 96) build 3077, and no other C++ 13.10 build. Retail was built with VC7.1 RTM,
  the same compiler as ours. The "different 13.10 build" idea from the last handoff is ruled out,
  and so are BFME 2's vc71-sp1 (6030) and ddk-4035 profiles.
- STLport: `_vector.h` is byte-identical between the vendored 4.5.3 and BFME 2's 4.6, so a
  4.6 header swap cannot be the lever.
- The J order does not depend on the inert spellings, even in combination. Random combinations of
  3, 5, 6 and 10 inert features from all sessions (56 to 70 features, 236 compiles in
  s3/combo.log) gave 4 B in every buildable case.
- Non-equivalent diagnostics (s3/jdiag.py prints the J pair and the loop-2 solution):
  a capacity test on `behaviors` in loop 1 gives J (edx=[24], ecx=[30]), and in loop 2 gives J
  (ecx=[30], edx=[24]). Neither the register pairing nor the load order is fixed per vector, but
  every flip found so far also changes other code. E_nobehswap keeps our order with a
  different loop 2, so order and allocation are correlated, not locked together.
  `behaviors.clear()` before the in-loop return compiles away (4 B).

## Families tested this session (4 B = inert)
- (a) control flow: loop 1 as while/++update (4), loop 1 indexed `modules[m]` (362),
  nested ifs and continue in loop 1 (4), `if (!empty()) do {} while (!empty())` (360),
  `return sdu->beginSlowDeath(dI);` (4), early `if (behaviors.empty()) return;` (diag 301).
- (b) lifetime and scope: behaviors in an inner block, both vectors or everything in an inner
  block, behaviors plus loop 1 in nested blocks (all 4); split declaration and assignment for
  probability and sdu (4); a named `module` local (4); dummy and pointer locals between the
  vectors (diagnostic, 4); a reference alias for probabilities (4).
- (c) types and ABI: Bool/Int returns on beginSlowDeath, markAsDead, setSelectable and
  deselectObject; Int playerMask; Int slot0C (5) and isDieApplicable (7).
- (d) visibility: `/D_STLP_LINK_TIME_INSTANTIATION` (sibling BfmeConv1110.cpp,
  U1SinkInserters.cpp), alone and with NO_EXCEPTIONS (4).
- (e) flags: /Ow /G5 /GB /arch:SSE /Og (4); /Oa (680); the
  `/DWIN32 /D_WINDOWS ... /D_STLP_NO_EXCEPTIONS` sibling set (4).
- (f) order: copy-initialised vectors `= std::vector<T>()` (4); `*it > roll` (6).
- (g) EH: no lever (two unwind states, same as retail; see the previous handoff).

## Conclusion
About 400 source, flag and combination variants across three sessions leave the 4-byte
exit-join reload order in place. Every other byte of the 842 matches. The cause sits in VC7.1's
allocator or PRE ordering, and no tested source feature reaches it. Retail's compiler build is
now confirmed equal to ours. Recommendation: keep the bank at 0.9952, or land it under a
documented compiler-quirk exception if the project allows one. Further blind spelling search is
unlikely to pay off.

Artifacts: s3/trials.log (per-variant results), s3/combo.log, s3/run.py, s3/combo.py, s3/jdiag.py, s3/q/ (diagnostics).
