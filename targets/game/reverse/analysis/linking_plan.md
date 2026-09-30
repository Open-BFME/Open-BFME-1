# Linking plan: a relinkable, verified BFME 1 built by a multi-provider swarm

Revised 2026-09-29 after two adversarial reviews (gpt-6.1-sol on the draft; an owner-run gpt-6.1-sol code review).
Every figure names the commit it was measured on. Scratch evidence: `build/plan/` on the lead host.

## Goal and the honest definition of done
1. **Relinkable image**: link.exe 7.1 links every object (source-built, generated, library, and labelled
   scaffolding) with no `/FORCE`, at a placement that is NOT retail's, and every function, vtable and data item
   compares equal to retail after relocation. This proves every reference is symbolic.
2. **Boots** on an isolated test host (never the owner's remote desktop): menu, skirmish, save/load.
3. **Progress** = source-built code (authored + vendored C/C++) verified inside that image. Scaffolding (dumps,
   delinked data, alias objects) never counts, is tagged with provenance, and may only shrink.
4. Byte-identical retail image (original TU grouping, link order, ILT) is a later, separate goal.

## What the reviews established (measured)
- Code objects: at db6fc68ade, 82.21% byte-matched, 16.58% dumps, 1.21% (117,623 B) unclaimed (progress.py).
- **All 340 gen_asm dump objects have zero relocations**: their `db` bodies hold retail rel32 displacements and
  absolute addresses, so they only work at retail addresses. (Sol; confirmed: `game/gen_asm/*.asm` bodies are
  raw `db`.) Dumps are 1.6 MB of code: relinkability needs their relocations recovered, or their conversion.
- Byte gate (tools/build.py resolve): REL32 targets resolved through symbols.csv candidates; DIR32 copied from
  retail (masked). Data content is unverified except by the new per-file data checker (ab5791d503).
- Name ambiguity is small: 56 names cover distinct bodies (+42 body/ILT-stub chains); dir32 names never map to
  two addresses. But a name table is NOT an ABI repair (private class copies differ in layout/vtables), and weak
  aliases cannot override an existing wrong definition.
- COMDAT selection cannot be fixed by object order: 71 contradictory ordering pairs (e.g. Line3D dtor vs deleting
  dtor). Of 4,003 wrong kept copies (22a5be53d9 census): 2,052 have a proven retail copy elsewhere; of the 1,951
  without one, 1,024 have unproven alternatives and 927 have every alternative disproved.
- Deleting a wrong inline body is NOT byte-neutral (inlining/template emission change): every deletion is a
  dependency repair re-verified across all affected functions, vtables and funclets.
- Missing lanes: 232 `.CRT$XCU` (+XCB/XCY) static-initializer sections, 50,379 `.xdata$x`, 5,409 `.sxdata`
  (SafeSEH) sections, the `STLPORT_` section, `.idata`/IAT and import order, exports, `.rsrc`, `.data`
  zero-fill; `_WinMainCRTStartup` unresolved. Retail TLS and load-config directories are zero (verify, don't build).
- Two-hop gap (owner's Sol): a locally clean file can call a function that calls a wrongly selected copy; only a
  whole-image check catches it.
- Swarm infrastructure bugs: `claims.claim` returns empty (not failure) on network trouble; `fleet_run` ignores
  refused claims; `add_match` releases a claim after local verification, before publication; pre-push can rerun
  the full gate; tool edits get only a syntax check; model identity is caller-supplied.
- The name lane's 80% two-model accuracy came from Opus+Fable (one vendor) plus a gpt audit: cross-vendor
  accuracy is not yet measured.

## Workstreams (each ends in a mechanical acceptance check)
A. **Dump relocation recovery** (tool, scripted): disassemble every dump body (capstone); rel32 branches -> REL32
   to the target's symbol (exact); absolute operands -> typed DIR32 with provenance and confidence; ambiguous
   imm32 flagged for review, never guessed. Emit relocatable scaffold objects under build/ (gen_asm is never
   edited). Acceptance: each regenerated body, resolved at its retail address, equals retail; placed elsewhere,
   every reference moves with its target.
B. **Typed relocation ledger** (code + data): target, addend, kind, provenance (compiler reloc / dump analysis /
   data scan / manual evidence). Source for the data scaffold and the comparator; a pointer scan alone is never
   accepted as proof.
C. **Whole-image comparator** (COFF-level, extends component_link): statics, section-relative labels, unmatched
   extents, aliases, padding, scaffold provenance; verifies at a shifted placement.
D. **Loader/startup lanes**: CRT entry and initializer order, EH and SafeSEH tables, imports/IAT order, exports,
   resources, STLPORT_ section.
E. **Unclaimed extents**: inventory the 117,623 B and give each a boundary (carve) or scaffold before boot.
F. **Definition repairs** (swarm, per dependency, not per file): wrong kept copies, duplicates, the 56 multi-body
   names, ABI conflicts between private class copies. Unit = one dependency repaired declaration -> definition ->
   selected linked implementation (+ data), re-verified everywhere it is used. Disproved copies only; unknowns
   need evidence first.
G. **Swarm infrastructure**: fail-closed claims with unique worker ids, heartbeats and fencing; release on
   authoritative landing; one publisher (landing service) with verification receipts tied to exact snapshots,
   idempotent queue, batch bisection and crash recovery; protected verifier/baseline changes; authenticated
   model/provider receipts; blind cross-vendor review; cost per accepted byte (incl. review and landing).
   Status 2026-09-29: fail-closed claims + per-worker owner + fencing tokens + heartbeat (89cbfe7263);
   release on origin/master landing (07e7fb1df0); host/launched-model receipts, unauthenticated
   (5e7b12a8a0); Verifier-Change trailer + shrink-only baselines (b9eaa9c709); landing service
   designed and prototyped in tools/landing_service.py (b0926cee30), not yet in use.
H. **Test hosts**: Linux workers that fleet_cgroup accepts; a separate boot host (windowed, timeout, logs, crash
   capture). Nothing launches the game on the owner's desktop.

## Order
Now: A (prototype on one dump file), G-claims fixes, plan committed. When slots free: B+C together, then D, E.
Swarm lanes (F) open only after C exists, because C is their acceptance check.
