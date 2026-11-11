# BFME1 diagnostic link-cycle CRT/import providers

## Scope and provenance

Baseline BFME1: `99ae58b84f9f0c7116febe55e5bf8c443b49faec`.
Reviewed BFME2 donor: `76f0baefa6f285d54bc1ca922397674312a5913f`,
`tools/link_cycle.py` (`runtime_libraries`, `make_import_libs`,
`undecorate_stdcall_imports`), its runtime-link regression tests, and
`reverse/attempt_support/runtime-link-20261017/verification.md`.
The original donor repair commit is `fb62a1d7bbe571c2155d80155f4ec422cd9e89f6`
("Link the MSVC runtime and consolidate generated import providers"); its exact
patch and 108-pass/one-skip Wine evidence were reviewed separately from the
pinned donor's subsequent lazy-thunk changes.
The integration supervisor approved this narrow runner-setup adaptation.
No donor game source, address, header or compiler override is imported.

## Independent BFME1 evidence

The baseline runner passes `/NODEFAULTLIB`, supplies generated import archives,
and omits `msvcrt.lib` and `oldnames.lib`. A real MSVC 7.1 fixture containing a
native `_Sleep@4` FF25 thunk plus references to CRT statics and a legacy alias
fails without those archives. Its CODE import member simultaneously defines
`_Sleep@4` and `__imp__Sleep@4`, so it also produces `LNK2005` against the
fixture's real thunk. Supplying runtime archives alone preserves that duplicate;
supplying an IAT-only archive alone preserves the unresolved CRT references.
Both independent repairs are necessary for the strict fixture link.

BFME1 imports `MSVCR71.dll!_strcmpi`, not the donor fixture's `_stricmp`.
The adapted fixture uses the shipped `oldnames.lib` `_strcmpi -> __strcmpi`
weak legacy spelling and checks **every** selected DLL/name against BFME1's
actual import directory. Copying the donor fixture's `_stricmp` reference was
rejected by that stronger check and corrected; no new runtime alias was added.

## Adaptation constraints

- Keep the BFME1 single `.text` group, ILT routes, no-ICF, closure and shifted
  byte checks unchanged. Do not import the donor's later multi-group lazy-thunk
  archive transformation.
- A name alone cannot authorize IAT-only generation. Every source definition
  must have its own six-byte matched source extent, native FF25 bytes, a sole
  zero-addend DIR32 relocation to its same-named IAT cell, and a retail FF25
  operand reading the exact expected DLL/name slot. Missing, ambiguous,
  generated, wrong-slot, wrong-DLL, addended and unrowed competing definitions
  do not suppress the library CODE provider. Absolute and COMMON competitors
  also refuse suppression. Existing duplicate diagnostics remain visible.
- Change only short import members' stdcall name-mode bits, retaining the COFF
  `_name@N`, CODE/DATA type, archive sizes and offsets; the DLL exports the
  undecorated native name. The generated entries already require a retail name.
- Explicitly hash both shipped runtime archives in the start/end input state
  and receipt core. Missing archives fail rather than creating replacements.
  The committed archives remain read-only.

## Validation and limits

Source-named regressions: `tools/tests/test_link_cycle_runtime.py`, plus runtime
archive mutation coverage in `test_link_cycle_identity.py`. The real-toolchain
fixture links at bases `0x00400000` and `0x10000000`, with `/NODEFAULTLIB` and
`/OPT:NOICF`, without `/FORCE`, alternate-name directives or unresolved-symbol
stubs. It checks native imports, equal section layout, relocated DIR32 values,
unchanged non-relocation code/data bytes, and unchanged input archives.
Separate negative controls require duplicate and missing-runtime failures.

These are scoped runner-setup proofs, **not** a full-game no-FORCE link,
authenticated census, source-closure credit, or runtime/boot evidence.
The real-link cycle deliberately retains its existing `/FORCE`, labelled
fillers/stubs and rejected dependencies for diagnosis; those do not become
buildability evidence through this repair.

Exact command logs, maps, fixture images, input/provider hashes and full-cycle
state are retained in this experiment worktree's ignored `build/integration/`.
The lane handoff in the experiment control directory identifies the measured
HEADs and actual test outcomes.
