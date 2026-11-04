# Living World update: begin relocation is the current linking blocker

Queue #28, inspected at BFME 1 77a8439ee4. The normal scoped build of
`game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManagerUpdate.cpp`
passes 1/1, including literals, DIR32 addresses and body guards. The census-only
link preview remains 0 -> 0 linked bytes; a current preview with compile-limit
zero is UNKNOWN because this worktree lacks 22,776 current ledger objects.

A fresh `link_census.RetailTruth` comparison of the verified object establishes
that all 369 masked bytes agree, but the REL32 at body +0x73 does not. Retail
calls ILT RVA 0x00047DC5, targeting 0x00611610. The C++ calls the
`hashtable<pair<const int, void*>, ...>::begin` instantiation, whose authoritative
ledger home is 0x000D09C0. Its additional symbols.csv candidate at 0x00611610
explains why the normal byte resolver passes. No extra pin or alias can repair
this conflict.

The source comment claiming ICF makes all int-keyed pointer maps share this
body is unsupported: retail had no ICF. The row at 0x00611610 is currently
`tg_00611610`, emitted by Player.cpp under a Relationship-valued instantiation.
Neither that row nor the caller establishes the true mapped type of manager
+0x210. A correct repair needs independent identity evidence for that map and
its begin provider, followed by reconciled caller/provider verification. Changing
only the cast of the mapped value cannot change the template relocation.

BFME 2 c8b988aae8f06e96b73717239e0bb8f1e7ec23d4 (also official upstream HEAD
at inspection) has no corresponding LivingWorldManagerUpdate implementation;
reviewed git grep of Code and reverse/attempt_support and docs/recipes.md.
Its reference audit mentions this BFME 1 file but supplies no identity proof.
The existing donor worktree has pre-existing staged deletions; it was preserved,
and git object reads were used. No donor source adaptation applies.

No body, ledger, pin, shared header or bank was changed. This isolates a
relocation/identity prerequisite rather than reopening the solved EAX/ECX
compiler-shape problem. blocked-on=0x00611610; model=gpt-6.1-sol; t=10min.
