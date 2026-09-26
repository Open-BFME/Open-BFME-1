# Ghidra inventory (optional accelerator)

The PE export table names only ~1,300 of the binary's ~78,000 functions. Ghidra recovers
the rest — candidate boundaries, owned-address counts, and the call graph — which gives
boundary evidence for `functions.csv`, callee addresses for `symbols.csv`, and string anchors used to map
anonymous functions to Generals source. The outputs are pinned to the baseline binary;
regenerate only if the baseline changes (it shouldn't).

## Setup (one-time)
1. Install Ghidra (https://github.com/NationalSecurityAgency/ghidra/releases) and a JDK 21.
   Note: Ghidra 12 dropped bundled Jython — these scripts are Java, run via `-scriptPath`.

## Decompiling (optional, any OS)

`python tools/ghidra_decompile.py 0xRVA [0xRVA ...]` (or `./ghdec 0xRVA`) prints, per function, the references to
its entry, its direct callees and Ghidra's decompile. `--out DIR` writes one `<rva>.c` per function. It finds Ghidra
in `$GHIDRA_INSTALL_DIR` or `inputs/toolchains/ghidra_*`, and a JDK in `$JAVA_HOME`, `inputs/toolchains/jdk-*` or on
`PATH`; both are plain unpacked archives, no installer. Analyze once per host (about 13 minutes on a desktop):

    python tools/ghidra_decompile.py --analyze

The project is written to `inputs/toolchains/bfme_ghidra` (untracked). A call costs about 10 s of JVM start-up, so
pass several RVAs at once. The output is a DRAFT of control flow, call order and argument passing. Ghidra's names
and types are invented; decompiled C is never byte-match proof and never identity evidence (AGENTS.md).

## Regenerate (≈3 min)
Run from the repo root; replace `$EXE` with `inputs/baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe`:

    analyzeHeadless /tmp/bfme_ghidra bfme -import $EXE -overwrite \
        -scriptPath tools/ghidra -postScript list_functions.java $PWD/targets/game/reverse/ghidra_functions.csv
    # reuse the saved project (no re-analysis) for further scripts:
    analyzeHeadless /tmp/bfme_ghidra bfme -process lotrbfme.exe -noanalysis \
        -scriptPath tools/ghidra -postScript list_string_xrefs.java $PWD/targets/game/reverse/string_xrefs.tsv

Outputs (gitignored, derived from the binary, like `targets/game/reverse/exports.csv`):
- `targets/game/reverse/ghidra_functions.csv` — `rva,size,name` for every function. Consumed by `tools/harvest.py`.
- `targets/game/reverse/string_xrefs.tsv` — `string<TAB>referencing function rvas`. For identification.
- `targets/game/reverse/vtables.tsv` — `vtable_rva<TAB>label<TAB>slot<TAB>func_rva<TAB>func_name` for every
  recovered vtable. Read BFME's exact class vtable slot order instead of hand-triangulating.
  Generate (reuse the analyzed project, store it on disk not /tmp — tmpfs quota):
    analyzeHeadless inputs/toolchains/bfme_ghidra bfme -process lotrbfme.exe -noanalysis \
        -scriptPath tools/ghidra -postScript export_vtables.java $PWD/targets/game/reverse/vtables.tsv

## Use
- **Sizes:** `list_functions.java` exports `getBody().getNumAddresses()`, not
  `last address - entry + 1`. Gaps inside a body can shorten that count. Verify
  the complete contiguous retail extent before using it as `target_size`.
  Examples: Team's facility query at `0x000EF340` is 99 bytes, not inventory 96;
  `Object::affectedByUpgrade` at `0x001C5A30` is 270, not 267; and
  `Debug::SimpleMatch` at `0x0088A3A0` is 135, not 132. All three short counts
  omit part of the final epilogue when interpreted as a contiguous span.
  Do not fix this by blindly taking the largest Ghidra body address: shared or
  discontiguous tails can span other functions. Keep the inventory as evidence,
  and prove the actual range from retail control flow.
- **Calls:** a call target's address (e.g. `__ftol2` at `0x9F6E38`) goes in `targets/game/reverse/symbols.csv`.
- **Identification:** ~12% of `.text` is in functions referencing strings that are greppable in
  the Generals source — anchoring them to a specific source file. See `tools/harvest.py` and `../../docs/matching.md`.

## Decompile a queued candidate

`tools/next_work.py --tier ghidra` prints an RVA backed by source-string xrefs.
Decompile it, including callers/data references and direct callees, with:

    analyzeHeadless inputs/toolchains/bfme_ghidra bfme -process lotrbfme.exe -noanalysis \
        -scriptPath tools/ghidra -postScript decompile_function.java 0x82190

## Windows

`analyzeHeadless.bat` is the entry point, and the project directory **must
already exist** — headless aborts with "Directory not found: ..." rather than
creating it, which looks like a script error and is not. Ghidra 12.1.2 with
Microsoft OpenJDK 21 reproduces this repository's artifacts exactly (see the
validation note below), and neither is packaged in winget: take the Ghidra
release zip from GitHub and the JDK zip from `aka.ms/download-jdk`, and expand
both with PowerShell's `Expand-Archive` — Git Bash's GNU `tar` cannot read a
zip, and `--force-local` fixes only the drive-letter path, not the format.

```powershell
$root = "<repo root>"
$env:JAVA_HOME = "$root\build\toolchains\jdk21\jdk-21.0.12+8"
$env:PATH = "$env:JAVA_HOME\bin;$env:PATH"
New-Item -ItemType Directory -Force "$root\build\toolchains\bfme_ghidra"
& "$root\build\toolchains\ghidra_12.1.2_PUBLIC\support\analyzeHeadless.bat" `
    "$root\build\toolchains\bfme_ghidra" bfme `
    -import "$root\baselines\bfme1\workshop-vanilla-1.03\files\lotrbfme.exe" -overwrite `
    -scriptPath "$root\tools\ghidra" -postScript list_functions.java `
    "$root\reverse\ghidra_functions.csv"
```

Analysis takes about 13 minutes and recovers ~78,500 functions. Reuse the saved
project with `-process lotrbfme.exe -noanalysis` for the other two scripts;
those finish in seconds.

## Is the inventory any good?

Two independent checks, worth re-running after any Ghidra upgrade.

**Against a tracked artifact.** `targets/game/reverse/vtables.tsv` is committed. Re-exporting
it with `export_vtables.java` must produce a byte-identical file (562 lines, 205
vtables). If it does, this Ghidra version agrees with the one the project was
built against; if it does not, treat every other export as suspect before using
it.

**Against the ledger.** A `matched` row is a byte-verified fact, so the fraction
Ghidra reproduces is a real score. Measured 2026-08-04 with 12.1.2:

| Row kind | rows | rva is a Ghidra function start | size exact |
|---|---|---|---|
| real source | 14,737 | 65.2% | 96.4% of those |
| `gen_small` | 76,884 | 32.9% | 100% of those |
| `masm_dumps` | 179 | 91.1% | **81.0%** of those |

Read it as: where Ghidra has a boundary it is nearly always right, so
`harvest.py` taking its sizes is safe, and the third of real-source rows it
misses are simply absent rather than wrong. The `masm_dumps` row is the outlier
and it is not a Ghidra defect — 19% of dump rows disagree with it because dumps
byte-verify at any length.

## Without the inventory

`locate.py`, `harvest.py`, `explain_mismatch.py`,
`decode_calls.py` and `drift_classify.py` all raise `FileNotFoundError` on a
fresh clone, because `targets/game/reverse/ghidra_functions.csv` is gitignored. That is the
whole function-finding pipeline, and the failure is loud but easy to
misdiagnose as a broken checkout. Regenerate before concluding a tool is
broken.
