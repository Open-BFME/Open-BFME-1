# Blocker-family lane review, 2026-09-24

Current-master `pick_blocker.py` groups open dump bodies by the canonical
`blocker=` **family** from their latest recorded attempt. It preserves the
leaf detail, excludes busy/recent and suspect-boundary RVAs, and asks a worker
to prove one lever on at least three bodies. The default picks the family with
the greatest total bytes and its largest twelve members. This is exploratory
assignment; neither the family tag nor a masked probe is shared-prerequisite
or byte-match proof.

Independent current-data replay found 113 `regalloc` bodies/43,021 B with 103
distinct leaf details. Its default twelve include eleven different details.
The `stack-slot` 34, `eh` 30, `float` 12, `toolchain` 6, `identity` 9, and
`callee` 5 groups each have as many distinct details as bodies. One 72-byte
`member-call-receiver-order` record canonicalizes to `layout` because the
generic word `member` precedes `codegen-order`; it is not in the default
brief. These facts disprove an assertion that members already share one
concrete blocker, but do not establish that a useful common compiler lever
cannot exist. No live blocker-seat outcomes, cost, or throughput were found.

## Decision before changing the worker note

Proceed with a wording correction only: call this a broad tagged family, ask
the worker to compare leaf details and attempt histories before probing, and
require evidence that each RVA put in `unlocked.txt` actually gained the
prerequisite. Keep the existing family selection, eligibility, attempt-cap
override, probes, and publication gates. Expected benefit is avoiding a false
premise in the brief; no throughput benefit is claimed. A dry-run of the real
picker must show the corrected note and unchanged selected RVAs. No new test
that merely repeats a prose string is useful for this low-impact edit.

Adversarial review considered grouping by exact leaf tag, family rotation, and
automatic cooldown after a no-common-lever session. Exact details are nearly
unique and historically use varied spellings, so that would erase the lane's
exploratory pool. Rotation/cooldown might prevent repeated default `regalloc`
selection, but could also starve the only tractable shared lever and lacks
measured failure frequency. Defer those policy changes until several real
batch outcomes record the selected RVAs, shared-lever result, and exact landed
or reopened targets. The taxonomy false-positive is too small to justify a
new classification policy in this patch.
