# EA's own names from WorldBuilder internal builds

An identity correction that cites this file renames a row to the name EA's own build gives
its address. The per-address evidence is that address's `name` row in
`targets/game/reverse/ea_evidence.csv`, written by `tools/ea_evidence.py`.

BFME1's and BFME2's WorldBuilders are internal builds of the game engine. A function in them
references a `Class::method` string naming itself. The game function at this address is
paired with that WorldBuilder function in one of three ways:

- directly with BFME2's (89.5% held-out precision);
- through BFME1's WorldBuilder (98.4% game to BFME1, then 94.4% BFME1 to BFME2);
- by BFME1's own label.

Only strongly paired addresses are corrected this way: every pairing leg is a shared export,
a unique shared string or a BSim unique match. The routes that reached an address must agree.
The label must name exactly one function.

`tools/ea_queue.py` serves only renames that keep the body's shape: the same class with
another method, or a stand-in class renamed whole. It skips any row where a label is known to
mislead:

- a structor labelled as a method (a label inherited from an inlined callee);
- a free function EA calls a member;
- a lone virtual override;
- any row whose current name Zero Hour declares.

Measurements and caveats: `targets/game/reverse/analysis/worldbuilder_evidence.md`.
