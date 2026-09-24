# Emitter aliases in the staged-source claim check

## Reproducer and design checkpoint before code

The staged InGameUI identity correction preserves the 132-byte source method
`subtitleLabelRva0043E510` as its physical emitter while the ledger records
the proved retail identity `militarySubtitle`. The row carries
`object-symbol=?subtitleLabelRva0043E510...`, which `build.py` uses in a
successful scoped byte and relocation gate. `find_declared_unmatched.py
--fail --staged` nevertheless rejects the same staged source definition as
undeclared, because it searches only retail ledger names. This made the
normal pre-commit hook fail. It is a check inconsistency, not byte evidence
or permission to bypass the hook.

Smallest fix: when loading matched ledger rows, read each row's physical
emitter through `build.ledger_object_symbol` and associate an explicit alias
with **that row's source only**. The staged-source check may accept the alias
for a definition in that source, and may recognise a marker for it as stale.
Keep the semantic ledger names and every existing global-name check. Rows
without `object-symbol=`, non-matched rows, and aliases from a different source
do not gain permission. The byte gate remains authoritative for whether the
alias actually emits the claimed body; this static check only verifies that a
staged source definition has a declared matched emitter.

One alternative is to leave the wrapper source unstaged, but that preserves a
false identity comment and makes a routine comment edit fail later. Renaming
the method to the semantic name creates a second definition in InGameUI.cpp.
A blanket exception or whitelist would weaken the claims gate. A second
parser for `object-symbol=` risks disagreeing with `build.py`; reuse its
existing parser.

## Adversarial questions and verification

An alias is a string in ledger notes, so accepting it globally could excuse
an unrelated source's definition. Scope it to the exact matched row's source,
and test a same-named definition in another source still fails. An unmatched
row or a note without `object-symbol=` must not pass. The new positive test
must call the production checker on a temporary ledger/source fixture (and
the real InGameUI staged case), while negative tests keep the failure path.
The test must not merely duplicate alias parsing. Re-run the naming, ledger,
byte, relocation, identity and normal hook checks after the tool patch.

The expected benefit is preserving a verified identity correction without
weakening staged-source accounting. There is no game-code byte or fleet
throughput change.
