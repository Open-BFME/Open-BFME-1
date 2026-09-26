# Callee ledger alias diagnostic, 2026-09-24

At starting commit `83f507fd18`, `tools/callees.py:ledger_names()` overwrites
earlier names for a shared target RVA. Its output for `0x00887B60` is
`??0GameSpyGroupRoom@@QAE@ABV0@@Z`, the lexically last row. The same ledger
has a matched `StringBase<char>` copy-constructor body at that address and
marks the GameSpy row `object-symbol=...StringBase...;C++ alias`. Existing
`targets/game/reverse/name_corrections.json` explicitly rejects inferring a GameSpy owner
from that alias. All 13 existing callee tests pass because none exercises the
real ledger-name grouping path.

Proposed narrow fix: group rows by target RVA and use
`build.ledger_object_symbol()` to expose the compiled body label. Preserve the
current single-name display when no alias exists. When multiple ledger names
share an RVA and agree on one object symbol, show that symbol plus the number
of ledger names, explicitly labelled as an object symbol, not a semantic
identity or ABI. When the rows point at different object symbols, show an
ambiguity warning rather than arbitrarily choosing one. Keep the
`--unpinned-only` meaning (the address has ledger rows), and the existing
warning that ledger names do not prove signatures. Do not edit ledger claims,
pins, byte gates, or acceptance rules.

Adversarial review before implementation: selecting the first row is unsafe
because alias rows can sort before the physical emitter; selecting the last is
the observed defect. A unique object symbol is only an emitter label and may
appear as an alias at multiple retail RVAs, so the output must not call it the
retail identity. If multiple object symbols share a retail RVA, choosing any
one would reintroduce a false claim; report ambiguity. A single alias row
should retain its ledger name and identify the object symbol separately, since
there is no same-RVA consensus. A malformed row must not replace a valid
name. Tests should call the actual `ledger_names` function with a fixture in
adversarial row order and check the current repository example separately.

Decision: proceed with the diagnostic-only change. It reduces a demonstrated
source of false naming hints without altering match, relocation, or pin state.
