# Verifier upgrade and link-first plan (Open-BFME-1 and Open-BFME-2)

Status: plan, October 2026. The checks below are being implemented; none has landed yet.
This file is identical in both repos. Numbers come from an audit of Open-BFME-1 @ e5ce116448 and
Open-BFME-2 @ 22fb48d9ee; "measured" numbers were re-derived independently, "est." are estimates,
and simulated gains are ceilings, not targets.

## Why

The byte compare is strict about the bytes it compares, but much of what decides whether code is
right sits outside those bytes. Measured on the audit commits:

- Deliberately wrong code passed the real pre-commit hook 6 of 6 times in BFME2 and 4 of 7 in
  BFME1: a wrong callee via one new `symbols.csv` pin; a wrong global under an unseen decorated
  name; `gen-alias` in a row's notes masking every call target; local static data never
  compared; truncated string literals; switch jump tables never compared.
- BFME2 has 13 truncated string literals and 6 switch statements whose bytes match retail but
  whose case mapping is wrong (e.g. `piEnterResultToJoinResult` returns 1 where retail returns 10).
- A real `/ORDER` link of BFME2 with retail-byte fillers puts 37.6% of `.text` at its exact retail
  address, but only ~16% is placed *and* wired to the right targets. About half of the failures
  were the test link's own setup (exception-handler thunks, `__except_list`, imports), the rest
  mostly duplicate or wrong data definitions.
- In BFME1, link.exe 7.10's incremental thunk table can be reproduced exactly; it pins each
  thunked function's decorated name. 17.5% of thunks carry the exact retail name today; 6,336
  real-looking names are contradicted; 3,986 repairs can be derived automatically.
- Retail BFME2 GameEngine code was built with `/G7`, which no source declares; it explains ~405
  exception-table mismatches. BFME1 game code is one flag set (/O2, x87).
- Metrics: progress bars include prebuilt libraries, generated code and address-named
  placeholders; "linking %" means a file raised no error in a `/FORCE` link, never compared with
  retail placement.
- Every past metric, lane or gate that shipped without a guard was gamed within hours to days;
  shrink-only baselines, tombstones and `Verifier-Change:` trailers worked.

## Rules for every change below

1. Policy lives in hooks, tools and queues, not in AGENTS.md prose.
2. No metric, lane or queue ships without its anti-gaming check.
3. Every headline number has a counter beside it (aliases and pins per row, `__emit`/asm bytes).
4. Every escape hatch is counted and shrink-only: `gen-alias`, data pins, `object-symbol=` rows,
   `/alternatename`, `selectany`, `g_Va*` globals, `class-gate: allow`, `present-unmatched`,
   `#pragma optimize`. A 2× jump in 24 h freezes it until a `Verifier-Change:` commit lifts it.
5. Baselines only shrink, provably: agents may remove lines (the hook re-verifies each), only
   tools add them, and the checker that judges a commit is pinned outside that commit.
6. Checks are scoped to what a commit touches, never repo-wide totals.
7. Queues serve only items with a machine pass test and say where the code goes.
8. Only verified output counts; attempts and votes are reported separately; repairs are credited.
9. Rule changes are versioned and shown next to the old numbers.

## Plan

Days are wall-clock from adoption, overlapping, sized for fleets of ~45–130 commits/hour. Each
step names the bottleneck that more agents cannot speed up. Exit criteria, not dates, decide
promotion.

| # | Step | Bottleneck | Exit | Days |
|---|---|---|---|---|
| 1 | Admins restrict pushes to master to a publisher bot; fleets submit to a queue. Until then hooks run the checker from `origin/master`. | admin and operator decisions | direct and API pushes refused | 0–2 |
| 2 | Publisher: isolated builders without push rights, a pinned and separately promoted checker, signed receipts, continuous drain (no fixed sleep), per-operator quotas, dependency bundles and aging. | publisher gate-seconds vs arrival rate | bypass and crash fixtures pass; queue depth flat at peak | 0–3 |
| 3 | Close the gate holes in both repos: NUL-terminated string compare; exact `$L` jump tables; bytes past a row's extent equal retail; `.c`/`.asm` in the hook; `gen-alias` only as an exact token with a callee identical in bytes and resolved relocations; `symbols.csv` validation (RVAs, no data pins, no second name on an owned address); `object-symbol=` limits; local static data; keyed identity baselines; shared exploit fixtures in both repos; build provenance. | 48 h shadow per check on live traffic | every reproduced exploit rejected; no correct work rejected | 0–4 |
| 4 | Escape-hatch counters with the 2×/24 h freeze. | — | freeze fixture passes | 1–2 |
| 5 | Real link cycle as the only source of credit: `/ORDER` from the ledger, retail-byte fillers, quarantine loop; setup fixes (EH thunks belong to their function, `__except_list`, retail import libraries); every failing relocation per row; data checked by address and content; a second link at a shifted base; credit = unique retail bytes in verified closure, fillers/stubs/aliases never count; each cycle pinned to a commit, checker digest and build provenance. | link.exe, 45–70 min per host | deterministic receipts; series published next to the current bars | 1–6 |
| 6 | Tool-owned retail inventories: code and data extents, interior targets, thunk routes, an ICF fold list verified on bytes and resolved relocations, `data_items.csv`, `flag_regions.csv`. | — | every reference has a classified target or keyed debt | 2–6 |
| 7 | Data identity sweep: one definition per retail global, references bound by retail address, invented globals for retail constants replaced; extents, alignment, linkage and initializers preserved; residue to a queue. Largest single lever measured. | consumer recompiles, publisher, ledger conflicts | wrong/duplicate-global debt shrink-only | 4–10 |
| 8 | Code identity: allowed-symbol sets from retail address identities; tool-only `/alternatename`; rows for unowned targets only when bytes match; duplicate-definition tool; verification of the COMDAT the linker selected; name tiers (evidence / unverified / address) written only by tools. | aggregate links | wrong bindings shrink-only | 4–12 |
| 9 | BFME1 track: pause bulk renames and raw dump harvests; run the step-3 shadow gate; thunk-table name check in the hook; tool-applied name repairs with caller evidence; relocations recovered in MASM dumps; BFME1 link cycle (bind at the thunk, no ICF, x87). | BFME1 full gate and link | repairs landed; dumps relocatable; BFME1 series live | 0–14+ |
| 10 | Flags from `flag_regions.csv` (BFME2 GameEngine `/O1 /arch:SSE /G7 /EHsc`); `// cl:` overrides only through the tool; exception and funclet data verified. | region recompile + full gate | funclet failures 538 → <130 | 5–14 |
| 11 | Canonical classes: first make header gating fit a publish window; a canonical layout is accepted only with retail evidence (constructor stores, access widths, vtable targets) and all consumers verifying; private copies detected by layout fingerprint. | header gate and windows | registered classes have no private copies | 7–24 |
| 12 | Original source files by tool sweep; new rows land in their assigned file; start-up and runtime lane (CRT entry, initializers, imports/exports, SafeSEH, resources, relocations in fillers and dumps); RotWK as a second verification target over the BFME2 tree after step 8. | publisher, full links, boot and crash triage | links without `/FORCE` or stubs at a non-retail base; automated runs reach the menu, a skirmish and save/load | pilot 2–7; completion weeks |

## What changes for agents now

Until the step-3 checks land: edit `tools/build.py`, `.githooks/`, baselines and whitelists only to
fix verifier bugs; add no new escape hatches (rule 4 list); BFME1 pauses bulk renames. Keep
matching as usual — rows the new checks flag will be served as a queue.

## Decisions needed from maintainers

1. Publisher with a pinned checker and push restriction on master (steps 1–2).
2. Date for showing the new link-based series next to the current progress bars (step 5).
3. BFME1 pause on bulk renames and raw dump harvests (step 9).
4. A word cap for BFME2's AGENTS.md.
