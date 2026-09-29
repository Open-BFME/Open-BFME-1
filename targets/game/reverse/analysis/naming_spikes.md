# Descriptive naming spikes (2026-09-29)

Can models name the code that no binary names, byte-exact and without misleading readers?
These spikes measured it before any lane was built. The answer is mostly yes: capable models
give about 60% accurate names and 2% misleading ones. The costs are that the same concept gets
different names in different files, and that an audit is needed to catch the misleading 2%.

## What needs naming

In the 21,500 C/C++ files outside `game/gen_*`, 80% hold invented identifiers: about 85,000
distinct names, used 311,000 times.

- 27,096 stand-in types that files declare for the classes they touch; 86% appear in one file only
- 38,313 invented function names
- 4,837 invented members, 3,522 globals, and about 1,200 locals and parameters

Evidence reaches about 5% of it:

- EA renames: 243 rows, `tools/ea_queue.py`
- stand-in types identified by a shared vtable, global or pin: about 1,000
- per-file copies of header types: about 3,000 invented names, and adopting a header removed
  none of them (43 byte-exact adoptions)

## Spike 1: naming quality against an answer key

Seven models named 50 anonymized functions blind, from the code and a brief's evidence:

- 30 whose real names come from EA's WorldBuilder labels;
- 20 with exact Zero Hour names, with the class, method, members, locals and parameters hidden.

Two graders who could see the truth (Opus, and gpt-5.6-sol through `codex`) graded the answers.

- **The Zero Hour half measures memory, not naming.** EA published Zero Hour's source, and Opus
  recalled it: 20/20 classes, 20/20 functions and 128/146 variables exactly. Only the EA half,
  BFME-specific and unpublished, tests naming.
- **EA labels fail about 12% of the time.** 7 of the 60 EA names were rejected in unison by all
  seven models. One was `Report_Unable_To_Fog`, a label inherited from an inlined callee, on
  Zero Hour's `Enable_Fog`; another was a log string's name on `LANAPI::OnHasMap`. Those were
  dropped as answer-key failures. When five or more independent models reject a label in unison,
  suspect the label.

EA set without the answer-key failures. The two graders agree within a few points, and the
table shows the range:

| Model | Accurate (exact or synonym) | Related (right area, vaguer) | Misleading |
|---|---|---|---|
| Opus, Sonnet, gpt-5.6-sol, gpt-6-astra, Grok | 55-62% | 30-38% | 0-8% (mostly 2%) |
| gpt-5.6-luna | 51-55% | 38-45% | 2% |
| Haiku | 36-40% | 49-50% | 8-9% |

Class names come out right more often than method names: about 65% against 40%. The graders
agreed on 77% of non-exact grades, and on 91% for acceptable versus wrong or misleading.

## Spike 2: can a blind auditor catch misleading names?

gpt-5.6-sol rated every EA proposal without the answer key. On the clean set it caught 12 of 15
misleading names and passed 95% of accurate ones. It over-flags, though: only 12 of its 44
"misleading" flags were truly misleading. As a filter (apply only names the auditor passes), the
residual misleading rate is under 1%, at the cost of dropping about 12% of names.

## Spike 3: applier mechanics (byte gate)

- **Locals under `-O2`, the default:** 27 of 27 files that compiled stayed byte-identical after
  every local was renamed.
- **Locals under `/Od`:** 3 of 17 files changed bytes, as frame slots follow identifier text.
  Only 223 files are `/Od`: gate them per file and revert.
- **Parameters:** 19 of 19 stayed byte-identical.
- **A naive applier prototype:** it renamed a file's invented types, members and functions, then
  rippled into other files, the ledger, `symbols.csv` and DIR32. It landed 25 of 30 files
  byte-exact, with 91 names renamed and 50 ripple files. All the failures were mangled names it
  did not rewrite: `object-symbol=` notes, compiler-generated `??_E` rows, and types used in other
  files' signatures. A production applier must rewrite every stored mangled name.
- The ripple is small: of 39,001 rows with invented names, only 85 real-named rows carry an
  invented type in their signature.

## Spike 4: consistency across files

The stand-in types fall into 5,942 distinct layouts, but the big clusters are trivial: 1,397 types
hold a single pointer. Checked against the identified types, 15 layouts mix real classes and only
8 hold a single one. Layout cannot unify concepts, so naming is per file, and one concept will
carry different names in different files.

## Spike 5: cost

The `codex` models named 50 items in 1.5-2.5 minutes with about 70K tokens (1.4K per item). Grok
took about 16 minutes. The Claude agents used 100-200K tokens each, mostly on reading the prompt
in chunks. A full pass over the 17,300 affected files is about 25-40M tokens, plus about 20% for
audits.


## Spike 6: a hands-off orchestrator

A headless Claude Code session in a disposable clone got one prompt, "Improve the naming progress
in this repo", and the `tools/name_lane.py` line in AGENTS.md.

- It found the lane and ran blind Opus and Fable worker sides on the same files. The briefs banned
  reading votes or reporting names. It serialized commits and never bypassed a hook.
- It served 84 files in about 50 minutes, and 78 names landed byte-exact. When both models named an
  item they agreed 81 times in 93, but about 74% of items were skipped, so about 13% of what is
  served lands. A blind gpt-5.6-sol audit rated all 78 accurate.
- It cost about 36K tokens per landed name. The orchestrator scaled itself from 6 to 16 agents and
  would have kept going.
- The applier bugs it hit are fixed in the tool: missing tombstones, headers to adopt, one refused
  file blocking the batch, EA-labelled rows and method names several classes share.
- Parallel workers on one machine can read each other's answers from process command lines, so
  answers go in a file, never inline in a shell command.
- Same-vendor models share recall, so the lane now requires two vendors. The test's names carry the
  cross-vendor audit instead.
- The hand-rename check refuses only a pure placeholder rename. Replayed over 3000 master commits,
  it refused none.

Scripts, prompts and raw outputs were in that session's scratchpad (`naming/`, `lane_test/`).
