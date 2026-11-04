# Guard lookup: remove the wrong source without losing native helper rows

Queue #33, census aafdf413e9; previous blocker and exact deletion experiment:
20261101-guard-lookup-emission.md. The existing large lookup banks and their
frame/filter mismatches were reviewed, preserved and not retried.

This new source repair addresses all three provider dependencies from that
handoff. The original Zero Hour headers define setNemesisID and
getFrameObjectsChangedTriggerAreas inline. Hide those definitions locally,
leaving their declarations in the existing classes, then provide the same
native operations explicitly in their existing AIGuard.cpp owning TU:

* AIGuardMachine::setNemesisID writes m_nemesisToAttack. It continues to emit
  the existing10B body for the native0x0016A390 row and its independently
  byte-equal10B twin0x00801180 gen-alias row.
* GameLogic::getFrameObjectsChangedTriggerAreas returns the existing member,
  preserving its existing7B native0x007FAD40 row.

No call or anchor is added just to force emission; these are real definitions
of the existing provider methods. Their full native callees inventories are
empty. Existing target field access and ABI remain verified by their own rows.
The exact scoped gate passes18/18 (including all three previously missing
helper rows) and all13 DIR32 references. find_declared_unmatched passes.

Delete the unmatched Zero Hour lookForInnerTarget body. Its filter-pointer
array was already independently refuted against BFME1's linked chain.
Final normal AIGuard COFF now defines the setter/getter, has no zhInline
symbols, and leaves the real lookForInnerTarget symbol undefined.

This last point is a material limit: retail0x0015D530/2514B is still a
`?d_0015d530@@YAXXZ` gen-dump row in game/gen_asm/d_00153d10.asm. Removing a
wrong provider does not create the missing named native lookup. Its real C++
recovery/identity remains required to finish the queue item. No generated
source, alias, pin, fallback or gate was changed to route around that missing
provider. No new native or linked bytes are claimed.

Donor review: latest officialBFME2a9286edec5374324e40c1f5dd29c3a8ab5582283,
Code/GameEngine/Source/GameLogic/AI/AIGuard.cpp (929B lookup and its helper
relationship), plus prior recorded donor2e97f871794a7b0cc6463976dd3b6fc3c1d780f8.
The latest body still has different target/filter/layout behavior and is not
imported. Code maps to BFME1game source only as a semantic reference. The
helper rewrite uses BFME1's already-verified declarations and bytes, not donor
addresses or layouts. No compiler context or shared header is changed.

The oldindexe9a5ae5b4c census-only preview still reports the historic selected
body; a complete current census is unavailable. Source and actual COFF prove
the emitter change, while the native lookup remains unresolved in current
source. This commit is partial cleanup, not a completed linking task.
