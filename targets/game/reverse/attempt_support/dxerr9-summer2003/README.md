# DXErr9 Summer 2003: archive-to-source proof packet

This batch replaces four unchanged native `.lib` owners with ordinary C++ lookup
switches. It is **not** new unclaimed coverage, game-algorithm recovery, a rename,
or a closure result. Identity/provenance and byte/data distinctions are in
`targets/game/reverse/identity_evidence/dxerr9-summer2003-source.md`.
`proof.json` records the four exact input/output identities, hashes and metrics.

## Results

- Normal admissions: all four `add_match.py --replace-existing` calls passed.
- Combined normal scoped gate: 4/4 functions; 8183 literal references; 11256
  embedded jump-table entries; zero baselined findings, unverified or skipped
  references. No new pins, global data, aliases, masks or verifier changes.
- Complete target-domain traversal: all 4294967296 HRESULT inputs per function;
  zero unsupported instructions, escaping paths, unbounded table domains,
  overlapping/incomplete input partitions or unclassified function bytes.
- Three read-only evidence tests pass: partition boundary/wrap behavior, exact
  source case/literal membership, and reproduction of all four final C++ bodies.
- Full union: 163077 bytes = 111499 instruction bytes + 51578 embedded table bytes.
  Frozen `progress.real_split` convention excludes every 0xCC occurrence, so the
  **unique nonpadding source delta is 162756 bytes** = 111307 instruction bytes +
  51449 table bytes. The 321 excluded bytes occur in classified code/data, not
  unclassified padding. No other base row intersects the four replaced ranges;
  their previous owners were solely the attached archive. Lost source bytes: 0.
- Published bytes remain 0 until parent approval/publication. Commit count and
  existing library-covered executable bytes are not the recovery metric.

## Reproduction (from repository root)

The scripts below write only to the explicitly supplied private output directory;
they do not edit source, ledgers, pins, verification rules or admissions.

```sh
python3 targets/game/reverse/attempt_support/dxerr9-summer2003/recover.py \
  --out-dir build/dxerr-review
python3 targets/game/reverse/attempt_support/dxerr9-summer2003/test_recovery.py \
  --evidence-dir build/dxerr-review
python3 targets/game/reverse/attempt_support/dxerr9-summer2003/emit.py \
  --evidence-dir build/dxerr-review --out-dir build/dxerr-review/candidates
./build.sh game/Libraries/Source/DirectX/dxerrstringa.cpp \
  game/Libraries/Source/DirectX/dxerrstringw.cpp \
  game/Libraries/Source/DirectX/dxerrdescriptiona.cpp \
  game/Libraries/Source/DirectX/dxerrdescriptionw.cpp
python3 tools/check_csv.py
```

Compilation must use the normal project environment and a private Wine prefix,
with `WINEARCH=win64`, empty `DISPLAY`/`WAYLAND_DISPLAY`, `BUILD_POOL=1`, nice 10.
This run initialized a new prefix at `build/wineprefix-spike2`; it did not copy
old prefixes, objects or dependency receipts. Actual compiler banner is MSVC
13.10.3077 for 80x86. `proof.json` object hashes identify the observed normal
objects; COFF timestamps/path context need not reproduce across worktrees.
No game, GUI, desktop input or remote CI/census execution was used.

## Prior attempts and lessons retained

1. Direct BFME2 August2005 `dxerrdescriptiona.cpp` compiled privately with BFME1's
   normal compiler and explicit output. Its match scan found zero placements:
   summer2003 target cases differ, so donor body/4035 override cannot be copied.
2. Target original COFF has no legacy source-line table. Donor source-line
   evidence is inapplicable; target behavior was recovered from the entire CFG.
3. Description grouped aliases `Invalid flags` / `Invalid group` yielded 10939
   bytes instead of native 10933. Separate identical returns fix the shared-tail
   placement. Return-offset ordering works for the name switches, but applying it
   indiscriminately to descriptions still yields +6: retained donor-compatible
   source groups are the successful description context.
4. The first description admission passed instruction comparison but correctly
   failed the literal gate with ten D3DRM misbindings. It reverted the ledger.
   `d3drm-order-repair.patch` preserves the precise failed-to-success source-order
   change. Examples included `Internal error` bound to native `No template`,
   `Bad intrinsics` bound to `Bad array size`, and `No internet` bound to
   `Internal error`. The corrected family passes literals **and** jump tables.
   The original failure log was overwritten during the correction; this is a
   faithful observation/repair summary, not a fabricated raw log.
5. The first metadata token `openai/gpt-6.1-sol:high` was refused before ledger
   writing because `:` is excluded by the normal writer. Parent explicitly
   approved metadata-only token `gpt-6.1-sol`; runtime remained exactly the
   requested model with high reasoning. No parser/model substitution occurred.
6. Initial `check_csv.py` passed. A pre-stage rerun correctly refused four new
   untracked source paths; explicit staging resolves that input-tracking gate.

## Discovery/provenance controls

The donor checkout was initialized without recursion, then checked against
GitHub official master `9ace59152e2ce8f6a512859817dc98d0c1fef5f5`.
The base pointer was `76f0baefa6f285d54bc1ca922397674312a5913f`; both revisions
are retained. The four reviewed DXErr sources, license and donor handoff are
unchanged between those revisions; target TUs use no donor/shared include paths.
The current BFME2 scan examined 11946 bodies (128..4000 bytes), found 2118
placements, and current ranked packets were inspected. This is not an exhaustive
large-body reference claim. A Zero Hour initial sample built 16/20 TUs (four
explicit diagnostics), then matched 565 functions and regenerated its one current
packet. The sample is a setup/ranking control, not exhaustion of Zero Hour.
No old WinMain/shared-Ascii or paused GDI+/D3DX admission trials were repeated.

Original run logs/objects/private trial receipts reside under this lane's
`build/spike2/` and `build/bfme2_sweep/trials/`; the control-root review packet
identifies the immutable commit, exact commands/exits and publication state.
