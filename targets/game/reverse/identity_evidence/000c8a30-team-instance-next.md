# 0x000C8A30: Team instance-list advance

Retail `lotrbfme.exe` (retail-1.03-unpacked) body at RVA `0x000C8A30` is four
bytes, `8b 41 14 c3` (`mov eax,[ecx+14h]; ret`), followed by `cc` padding.

- ILT `0x00022A70` is `e9 bb 5f 0a 00`, a jump to `0x000C8A30`.
- symbols.csv pins `?_bfme_nextInInstanceList@Team@@QBEPAV1@XZ` (and its
  non-const and `BfmeTeamInstanceLink` spellings) at that ILT. Matched callers
  `AIPlayer::isSupplySourceAttacked` (AIPlayerIsSupplySourceAttacked.cpp) and
  `AIPlayer::selectTeamToReinforce` (AIPlayerSelectTeamToReinforce.cpp) pass it
  as the DLINK_ITERATOR<Team> advance over a TeamPrototype's team instances, so
  ECX is a Team and EAX the next Team.
- The prior ledger row `?m@Gen_000c8a30@@QAEHXZ` was a generated gen-shim
  scaffold (`game/gen_small/fun_000.cpp`, skeleton getter-d8) with no identity
  evidence: its `Gen_000c8a30::m` name and `int` return come from the shape
  generator, not from any caller.

The `_bfme_` spelling stays opaque. ZH's `MAKE_DLINK(Team, TeamInstanceList)`
accessor `dlink_next_TeamInstanceList` is already ledgered at `0x00629E60`, and
retail was linked without identical-COMDAT folding, so this second identical
body's EA identity is not established.
