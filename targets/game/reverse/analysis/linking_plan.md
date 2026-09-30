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
   Status 2026-09-30 (tools/reloc_ledger.py, data_scaffold.py, code_scaffold.py; db6fc68ade census objects):
   259,301 rows (compiler 127,621; dump 22,157; EH/FieldParse structure 39,563; vftable slot 32,620; use 124;
   scan-candidate 37,216, never linked). Data scaffold 1,797,981 B in 59,089 items (482,131 B structure-proven,
   576 B structure split by another boundary, 105,437 B strings, 337,219 B zero-fill, 872,618 B inferred);
   retail placement exact, links alone at 0x10000000 with no /FORCE, 71,061 fields move. Trial link, no /FORCE:
   round 1 (census + 359 relocatable dumps + data scaffold; 1 dump object missing) 110,286 unresolved. Round 2
   (+ the already-symbolic dump's own object, 4,703 funclet labels on object copies, 15,328 funclet bodies from
   retail bytes, 75,085 code aliases): 19,106 unresolved (13,874 unpinned, 1,945 pinned-elsewhere, 959 import,
   968 data names, 861 g_ code + 221 g_ data/idata refs, 277 alias, 1 CRT absolute), 5,601 duplicates, none
   involving the scaffold. Round 3 (+ msvcrt.lib, 18 import libraries (mss32, DINPUT8 generated from retail's
   import table), retail .res, /SAFESEH:NO; the four CRT initializer tables, 6,008 B, left to the linker):
   18,586 unresolved (13,810 unpinned, 1,947 pinned-elsewhere, 491 `__imp_` names retail does not import under
   that spelling), duplicates unchanged at 5,601. Round 4 (census 007ae4e6b1; ambiguous VA/RVA pins decided
   only by where byte-verified calls land or dir32 evidence): 18,513 unresolved (13,828 unpinned, 1,879
   pinned-elsewhere, 491 import, 964 data names, 857 g_ code refs, 274 alias, 39 pins left ambiguous), 4,619
   duplicates; queue: build/data_scaffold/queue.csv. Unrelocated in-image data words at every byte offset:
   119,586 proven scalars (119,389 library member, 177 vendored declaration read from the hashed source, 20
   element access covering every byte), 13,086 unproven in game object sections; scaffold: 72,390 proven
   pointers, 21,118 aligned + 15,476 unaligned unproven.
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
   Status 2026-09-29 (all PARTIAL; a gpt-6.1-sol review found holes, fixed in be983869f8/0b1312f505):
   - Claims fail closed with per-worker owners (89cbfe7263). Fencing is PARTIAL: tokens exist and a
     lost/expired claim stops the fleet worker and fences its add_match and pre-push, but nothing on
     origin checks a token; a non-fleet agent, a --no-verify push or the harvest API fast-forward is
     not fenced. Heartbeat: fleet_run only, hourly; a host that sleeps past the TTL loses claims
     without knowing until its next beat.
   - Release on landing is PARTIAL (07e7fb1df0). Guarantee: while this checkout holds a queued
     landing for a body whose row, source blob and changed game/ + inputs/reference/ blobs are not
     ALL on origin/master, no path in claims.py releases that body's claim -- not settlement, not
     `release --landed SHA` for an older commit adding the same RVA, not an earlier settled entry
     (fixed after review: the SHA path bypassed the blob check). Not covered: symbols.csv pins, what
     the byte gate actually read, queues in OTHER checkouts, `release 0xRVA` and `--force` (manual,
     unconditional), and queue entries older than a day (dropped; the claim has expired). It runs
     only when fleet_run settles or someone runs release --landed.
   - Test isolation: claims git calls no longer discover an enclosing repository; a fixture must
     still point at its own bare origin (tests assert it). One review run created real claims first.
   - Receipts record host/launched/model with reserved keys (5e7b12a8a0), unauthenticated.
   - Verifier-Change trailer + per-commit shrink-only baselines (b9eaa9c709) are client-side hooks:
     advisory against edited hooks, --no-verify, and the harvest scratch-branch path.
   - Landing service: design + fixture-tested prototype (b0926cee30); not in use, so publication
     is still one push per seat and none of the server-side checks above exist yet.
H. **Test hosts**: Linux workers that fleet_cgroup accepts; a separate boot host (windowed, timeout, logs, crash
   capture). Nothing launches the game on the owner's desktop.

## Order
Now: A (prototype on one dump file), G-claims fixes, plan committed. When slots free: B+C together, then D, E.
Swarm lanes (F) open only after C exists, because C is their acceptance check.
