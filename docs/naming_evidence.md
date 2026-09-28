# Where names come from

A byte match proves nothing about names: `m_pitchShift` compiles to the same bytes
as `m_priority`. The identity detectors are keyed on addresses, and a member name
has none, so none of them can see a wrong one.

## The rule

A name that admits ignorance is fine: `Rva0026C320Owner` says nobody knows yet and
greps out in a second. A plausible wrong name misleads every reader, and no gate
catches it.

| The name claims | What checks it | What to write |
|---|---|---|
| nothing (`Rva0026C320Owner`) | — | fine as a floor, never as an answer |
| a SHAPE (`FiveDwordElem`, `PooledNodeHeader`) | the body itself | when identity is unproven; **keep the address token** |
| an IDENTITY (`Player`, `AudioEventRTS`) | caller, vtable, string literal, ZH twin | only with evidence, and cite it |

- Drop the address only when evidence proves the identity. An unproven name without
  its address turns a visible unknown into an invisible one.
- With several retail copies of one template body, keep the address in each
  copy's name, and count call sites before giving one copy the plain name.

## Ask before you name

    python3 tools/name_oracle.py --class AudioEventRTS                # every witnessed member
    python3 tools/name_oracle.py --class AudioEventRTS --offset 0x20  # one offset
    python3 tools/name_oracle.py --todo     # placeholders the evidence can already name
    python3 tools/name_oracle.py --check    # sources that conflict with the witness

Exit status 2 means no BFME witness for that class or offset; any ZH member it
prints is a hint, not proof.

| Source | What it holds |
|---|---|
| `targets/game/reverse/zh_offsets.json` | `(class, member)` at Zero Hour offsets, from ZH headers |
| `targets/game/reverse/bfme_layouts.json` | members witnessed at BFME offsets (`docs/bfme_layouts.md`) |
| `targets/game/reverse/field_names.csv` | members from retail `FieldParse` tables and upstream `offsetof` |
| `targets/game/reverse/name_tables.tsv` | every shipped enum's names, in declaration order, from the image |
| `targets/game/reverse/exports.csv` | real mangled symbols at RVAs; authoritative |
| `lotrbfme.exe` strings | EA's `\bfme\Code\...` source paths; they anchor nearby vftables |

Function identity is thin and capped by evidence; more agents do not raise it.

## One body, one name

Retail was linked without identical-COMDAT folding, so every body has exactly one
identity. `python3 tools/one_identity.py` prints the proof from retail's bytes;
`--list` prints every address still carrying more than one real name; `--callers`
shows, per address, which symbol matched C++ callers name at retail's call sites.

When two real names claim one address, at most one is right. These decide it:

- **Matched callers**, when exactly one row name is called there. Generated and
  assembly callers do not count (they name whatever the ledger said when they were
  made), nor do C callers: where a C definition and a C++ wrapper share a body, keep
  the C name that C code calls.
- **A vtable slot** between named neighbours, through an owner named independently
  of the body, never through the body's own `??_G` name.
- **A pin.**

Retire each losing name: delete its row and add a tombstone to
`targets/game/reverse/deleted_rows.csv`, with the evidence as the reason. Stage the
tombstone with the deletion: `functions.csv` is union-merged, so a deleted row can
return on rebase, and only the tombstone lets `check_csv` catch it.

When nothing decides, add no second name and retire nothing on a guess. Rerun
`--callers` later; each newly matched caller can settle more.

## The member-name check

The commit hook runs `name_oracle.py --check --staged`. It compares each member's
offset in the source against the witnessed layout, and refuses a new placeholder at
an offset the evidence already names.

- A conflict is a question, not a verdict. The witness is inferred, and BFME forked
  the ZH layout, so a field BFME added can sit where ZH had another. A human
  settles it.
- `targets/game/reverse/name_oracle_baseline.csv` may only shrink. Never add a line
  to go green.
- Conflicts spread by copy-paste; one decision can clear a finding in many files.
- If your source conflicts with a shared witness you cannot settle, use an
  address-named partial layout view (e.g. `Rva0015C570GuardMachine`); never rewrite
  the witness to accept it.
- `--todo --apply` rewrites placeholders only; never rewrite a real name
  automatically, however confident the witness. The placeholder pattern decides
  what gets rewritten, so any change to it needs fixtures in
  `tools/tests/test_name_oracle.py` for what it must and must not match.
- The check computes offsets itself (declaration order, `/Zp8` alignment, a 4-byte
  vptr at +0 in a polymorphic class). It skips a struct it cannot model or whose
  stated offsets contradict it. After changing the model, run `--selfcheck
  --max-mismatch N`.
- Regenerate the witness with `python3 tools/layout_witness.py --compile`, then
  `python3 tools/layout_witness.py`. A rerun where reference compiles fail names
  fewer members: compare member and class counts before and after, and never commit
  a witness that names fewer.

## Keeping names

The commit hook runs `tools/name_regression.py OLD NEW` (`NEW` may be `:` for the
index); the push hook and the `Naming regression check` CI workflow also run
`tools/name_history.py OLD NEW` on every outgoing commit. They flag a descriptive
name replaced by an address or offset placeholder, following the body through
moves, renames and ledger RVAs. A comment keeping the old name does not count.

- Never replace an established name with an opaque one just to land a matching
  body. A rename to a better-evidenced name is allowed.
- Passing these checks does not prove an inherited name is right.

To replace a matched real-name row that independent evidence refutes:

    python3 tools/add_match.py <new-name> <rva> <size> <source> --model <model> \
        --replace-rva <rva> --correct-identity <old-name> \
        --identity-evidence targets/game/reverse/identity_evidence/<file>.md

It needs the exact old name and the same proven extent, verifies the new source,
and tombstones the old claim. Retire the orphaned source once it verifies. Plain
`--replace-rva` only replaces generated scaffolds.

An intentional descriptive-to-opaque correction needs an entry in the JSON list
`targets/game/reverse/name_corrections.json` with `old_path`, `new_path`,
`old_name`, `new_name`, `before_sha256`, `after_sha256`, `evidence` and `reason`:

- The hashes are SHA-256 of the exact UTF-8 source snapshots, line endings included.
- `evidence` is a nonempty tracked file under `docs/` or `targets/game/reverse/`
  that independently refutes the old identity; `reason` explains it.
- An entry covers only those snapshots and that name pair; it is not a reusable
  exemption. It also closes a false pairing when the checker matches a removed type
  to the wrong new one.

The check enforces only that the evidence exists; review it with the correction.

## Aliased base classes

`targets/game/reverse/symbols.csv` pins some invented classes' destructors onto a
real class's destructor body. That pin is the evidence the rule asks for. Open cases:

    SubsystemInterface  <- BfmeBase1134, BfmeDtorBase_00077560, Rva004948B0Base
    ModelConditionInfo  <- Gen0013C3F0
    LZHLDecompressor    <- Gen008267E0

- Leave generator-minted names (`Gen_t_*`, `Gen_uw*`, `Mem<n>`) alone: they are
  anonymous by design, reproducing a frame slot and a call, never a class.
- An alias whose target is itself invented (`BfmeHostZB`, `BfmeOwnVVE`) gives no
  real name.
- Renaming a class changes the mangled name of every member, so it is a large
  `functions.csv` edit. Do one class per commit, byte-verify every touched row, and
  require a green full gate.

## Traps

- A nested struct's offsets are relative to the nested type; do not fold them into
  the outer class's offsets.
- A type can be pinned without its bare name in the ledger: `Sub005C6A40` appears
  only inside `??1Sub005C6A40@@QAE@XZ`. Search decorated forms before calling a type
  free to rename.
- Do not paste the same member names into many TU-local shims. Count identifiers
  removed and duplicate definitions eliminated, not commits.
- In a renaming pass, a rename counts only when evidence lets the address go:
  `Q2Vt0110F978` -> `PolymorphicVptrBase0110F978` is longer, not clearer.
- Name things right when the file is created; cleanup cannot keep up with new files.
