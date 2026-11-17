# BFME1 FieldParse continuation and full-image census

34 additional source tasks, 548-581, are verified and published. The authorization
allowed up to 500 additional tasks from 547; this report does not claim 500.
The task audit finds contiguous numbers and no repeated operation. The PC stays on.

| Published commit | Consumers | Tasks | Native provider/consumer gate |
|---|---:|---|---|
| `90e0a97930bcf38c3b02367ce6347908a69b0769` | 28 | 548-575 | 124/124 across 31 sources |
| `d4137666e072d6b340a0b7d1a78596ac387cf292` | 2 | 576-577 | 94/94 across 6 sources |
| `d4dbfb67b783084e0344524735c7e66da9affc34` | 4 | 578-581 | 117/117 across 7 sources |

The provider checks overlap. The 34 consumers themselves contain 61 retained
function rows and 8,607 retained bytes. Their complete ordinary runtime inventories
remain identical to immutable controls: code, data, definitions, relocation roles,
raw directives, weak externals and aliases. The closure rechecks all 34 at
`d4dbfb67b783084e0344524735c7e66da9affc34`. Other original complete class layouts are unchanged.

The existing 16-byte FieldParse descriptor now has one canonical game header.
Four local INI shims and the thin INI view include it, preserving subsequent line
numbers. Matched lookup 00850880 and dispatcher 00851910 establish the four slots
and callback ABI. FontSubstitution keeps its original ILT 0001EB4B, whose retail
E9 reaches the already matched 512-byte callback 004776E0. A fresh current-tree
sweep leaves no other complete game-source FieldParse definition.

The normal shared-header gate passed 1,800 dependent sources. Normal publication
gates passed after ordinary integration; two races required rebase and revalidation.
The separate whole-object audit covers all 22,994 original objects at pre-integration
commit `cee69b93002208313a060bd86cc4a8e8a4772651`: 22,722 identical files and 272
identical runtime inventories. That evidence retains its actual scope; independent
later source changes are not relabeled unchanged. Four negative controls reject
swapped slots, wrong callback arity, widened offset and changed code.

## Full-image measurements

| Measurement and actual input | Linked bytes | Linked sources | Unresolved names |
|---|---:|---:|---:|
| Hosted 44094222765 / e27899673e | 3,095,587 | 15,536 | 88,682 |
| Hosted 44135612880 / 30f455d610 | 3,096,325 | 15,538 | 88,681 |
| Native / d4dbfb67b7 | 3,282,910 | 15,627 | 88,649 |

The requested followup completed successfully; both official artifact ZIPs passed
their API SHA256 digests. Its historical input excludes later work. The new native
census measures published input `d4dbfb67b783084e0344524735c7e66da9affc34` through the unmodified
`tools/link_census.py --build --history` and `tools/link_check.py --publish`.
It compiled 272 stale sources, verified all 1,870 data rows and measured all
22,994 objects with none missing. Source inputs remained fixed throughout.

Against the hosted followup: linked bytes +186,585, linked sources
+89, unresolved names -32. These are project-wide
changes, including prior work and independent contributors. The FieldParse cleanup
preserves bindings and receives no exclusive linked-byte credit. Consumer link
statuses are `{'no': 17, 'yes': 17}`; unknown or blocked units remain so.

Read-only BFME2 reference `0630f0ef47d0a818bb2e97583b43cfb1ecd35491` supplied context;
BFME1 evidence establishes addresses, layout and ABI. No donor code or toolchain,
verifier, baseline, selection exception, pin, alias or generated source was changed.
All metric CSVs came from their native writers. No Qwen or local model was used.
All 62 captured reservation keys have no remaining exact session lease.

No crash, leak, RAM, 64-bit, multicore, FPS or game-start improvement is established.
The fresh native queue nominates AICommandInterface::aiMoveToPosition under its
wrong_selected category: the selected ScriptActions copy has verdict `unknown`,
and all seven inventoried COMDAT copies have the same digest and remain unproven.
Six sources totaling 2,067 bytes are blocked at this census. This does not prove
that the selected body is wrong, and it does not justify deleting a provider.
It is a measured verification gap and a potential work scope, not an achieved gain.
The GameLOD findStaticLODLevel duplicate is another documented lead. Neither is
counted as a completed task; provider, caller and complete-object preservation
proof is still required before retiring either emitter.

Source evidence: [foundation](20261117-fieldparse-header.md),
[explicit consumers](20261117-fieldparse-final-consumers.md),
[remaining definitions](20261117-fieldparse-remaining-definitions.md).

Logs, controls, task/lease audits, verified hosted artifacts, archived old index
and native receipts: `W:/OpenBFME/diagnostics/continue-20261117-more500/`.
