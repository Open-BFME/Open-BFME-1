# 0x0005FEB0 compare alias: deliberate, keep (blocked)

## Question

`one_identity` reports two real names at 0x0005FEB0:

- `?compare@?$StringBase@D@@QBEHABV1@@Z` (StringBase.cpp, thunk 0x000220C5)
- `?compare@AsciiString@@QBEHABV1@@Z` (StringBase.cpp, `object-symbol=` base)

Is the second row an over-claim to retire (as with 0x0005F270)?

## Finding: no, it is a load-bearing alias row

- The row openly notes `object-symbol=?compare@?$StringBase@D@@QBEHABV1@@Z`;
  it is one of ~9976 `C++ alias` rows, the ledger's convention for "C++
  spells it X, the object emits Y" (`tools/build.py: ledger_object_symbol`,
  `link_census.object_name`). Retiring it would orphan the C++ spelling
  tree-wide, not fix an identity.
- The 92 bytes at 0x0005FEB0 are the genuine out-of-line base body (retail
  calls it from ~391 sites). `AsciiString::compare(const AsciiString&)` has
  its own inline body in `ascii_string.h` ("retail inlines this comparison
  at every AsciiString call site") and owns no separate out-of-line body.
- Object scan of the current build cache: 3 TUs still define the alias
  symbol (CrateSystem, Rva002157C0Refresh, ParticleSystem); none references
  it as undefined. The four task-3 reroutes already moved their call sites
  to the base spelling; that is the correct alias-row repair direction
  ("give the row its real body or name"), applied per TU as link blockers
  surface it.

## What would unblock this

Retire the alias only once no TU defines or references `?compare@AsciiString`
at all (all call sites rerouted to the base or inlined away). That is a
long-tail sweep across every AsciiString::compare call site, not a single
ledger edit. Revisit when the link queue stops serving compare blockers.
