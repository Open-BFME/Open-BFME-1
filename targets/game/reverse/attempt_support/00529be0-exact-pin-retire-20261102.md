# 0x00529BE0 (?d_00529be0, 186 B) -- EXACT C++, landing blocked on the ILT pin

Session a1/536, model claude-opus-5-5, 2026-11-02.

The banked source (targets/game/reverse/attempts/0x00529be0.cpp) is EXACT
(186/186, relocations modulo): the only change from the 0.93 bank is a
foldable first loop term,
`bool searching = true; while (searching && Rva00527730(key, ...) != END)`,
which keeps retail's head-tested key loop (init and advance calls share the
`add esp,8; mov esi,eax` head). Lever documented in docs/shape_levers.md
(0x0061A0F0 entry).

Why it is not landed: ilt_oracle contradicts the pinned ILT spelling
?shouldRefresh@SkirmishScreenState@@QAE_NXZ (0x0003029C, p_false 4.57e-4),
so the row needs an address-derived name (?rva00529BE0@SkirmishScreenState@@QAE_NXZ),
and pin delta refuses a new row on a body whose ILT still carries a
real-name pin in the base. Both matched callers resolve their call through
that pin: SkirmishScreenRefresh.cpp (?_bfme_refresh@BfmeAptScreenSkirmish, an
inline union-PMF wrapper named shouldRefresh that is emitted out of line)
and SkirmishScreenStateApply.cpp (apply). Deleting the pin alone makes
_bfme_refresh fail with an unresolved ?shouldRefresh call.

Recipe (memory: retired ILT pin two-push, s68/s70):
1. Push 1: replace the ILT pin with a self-addressed or otherwise admissible
   name for 0x0003029C and respell both callers to it; verify both TUs.
2. Push 2: apply attempt_support/00529be0-landing-20261102.patch (new TU
   game/GameEngine/Source/GameClient/GUI/SkirmishScreenStateRva00529BE0.cpp,
   row replace of ?d_00529be0 via add_match --replace-rva 0x529BE0, a
   name_corrections entry shouldRefresh -> rva00529BE0 whose before hash is
   origin's bank), turn the ILT pin into route=0x00529BE0 under the row name
   and respell the callers to rva00529BE0. Regenerate the name_corrections
   digests against the then-current origin bank.
