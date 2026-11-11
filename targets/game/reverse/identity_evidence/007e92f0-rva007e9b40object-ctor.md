# 0x007E92F0 is the out-of-line constructor of Rva007E9B40Object

Was `??0Rva007E92F0Object@@QAE@PAX@Z`, a private class view whose own
vftable names (`??_7Rva007E92F0BaseB@@6B@`,
`??_7Rva007E92F0Object@@6BRva007E92F0BaseA@@@`/`...BaseB@@@`) were dir32
gate debt at 0x01129744 / 0x01129810 / 0x01129808.

BFME 1 target evidence (retail bytes, 32 B body):

* `mov [esi+4],0x01129744` then the payload store at +8 — the common second
  base vftable that every Q3MakeDerivedFamily factory installs; dir32 records
  it as `??_7Q3MakeBaseB@@6B@`.
* `mov [esi],0x01129810` / `mov [esi+4],0x01129808` — dir32 records these as
  `??_7Rva007E9B40Object@@6BQ3MakeBaseA@@@` and
  `??_7Rva007E9B40Object@@6BQ3MakeBaseB@@@`, the derived pair the matched
  factory `?Rva007E9B40@@YAPAVRva007E9B40Object@@PAX@Z` (0x007E9B40,
  Q3MakeDerivedFamily.cpp) installs.

A constructor that installs exactly one class's vftable pair over the common
bases is that class's constructor; the factory inlines it, and this is the
out-of-line copy. Same reconciliation as 0x007F3850
(`??0Rva007F40F0Object@@QAE@PAX@Z`, Rva007F3850Constructor.cpp).

The class's real identity is still unknown; the name stays address-derived.
