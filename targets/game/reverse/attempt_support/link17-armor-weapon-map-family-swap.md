# Link queue #17 `?findArmorTemplateSet@ThingTemplate` (losers): Armor/Weapon map-family names are swapped

Session a1 s543 (2026-11-02), census d08539a550, no local census index.

ThingTemplate.cpp's findArmorTemplateSet (0x00146780) compiles byte-exact, but its
relocations name the Armor map family, whose ledger rows sit at the *Weapon* bodies.
Retail 0x00146780 calls ILT 0xAE20 -> 0x001412A0 and ILT 0x36C0A -> 0x001451E0; the
ledger rows there are the Weapon `_M_find` / `map::operator[]`.

Retail evidence (independent of every ledger name):

- findBestInfoSlow 0x00144300 walks 0xC-byte elements (ArmorTemplateSet: flags,
  armor, fx); 0x00144000 walks 0xEC-byte elements (WeaponTemplateSet). 0x00146780
  calls 0x00144300, so 0x00146780 is findArmorTemplateSet (ledger agrees).
- MapHelper bodies: 0x001407A0 loops 11 bits (`cmp edx,0xb`), 0x00140740 loops 29
  (`cmp edx,0x1d`). SparseMatchFinderMapHelperThunks.cpp's comments already note the
  "Armor" shim runs 29 and the "Weapon" shim 11: the symptom of the swap.
- Following direct calls/ILT jumps (build/a1_aw.py), every map-family body reaching
  0x001407A0 is called from the Armor finder chain and every body reaching 0x00140740
  from the Weapon chain.

Rows whose name disagrees with the reached helper (Armor name <-> Weapon name):

| member | ledger Armor at | should be | file(s) |
|---|---|---|---|
| ??RMapHelper ILT | 0x0000A9A2 | 0x00010B1D | SparseMatchFinderMapHelperThunks.cpp |
| _Rb_tree::_M_lower_bound | 0x00140A60 | 0x00140AB0 | ThingTemplate.cpp |
| insert_unique (167 B) | 0x00140F90 | 0x00141150 | STL{Armor,Weapon}TemplateSetBitFlagsHintedInsertUnique.cpp |
| _M_find | 0x00141220 | 0x001412A0 | same |
| insert_unique (629 B) | 0x001426A0 | 0x001429C0 | same |
| map::insert | 0x00144450 | 0x001444A0 | ThingTemplate.cpp |
| map::operator[] | 0x00145100 | 0x001451E0 | ThingTemplate.cpp |
| findBestInfo | 0x00146310 (shared with Weapon) | 0x00146360 (row ?dup_00146360) | ThingTemplate.cpp |

ILT rows 0x00010F1E (two "Weapon" insert_unique names) jump to 0x001429C0, the
Armor body; 0x00042D1B (Weapon _M_find) correctly reaches 0x00141220. symbols.csv
pins ??RMapHelper Armor @0xA9A2 / Weapon @0x10B1D are swapped too; the
_M_find/operator[] pins at 0xAE20/0x36C0A/0x42D1B/0x19155 are right.

Not done: the fix is a coordinated swap of ~16 ledger rows, ILT rows and pins across
six files (identity_guard / ilt_guard / pin_consistency), more than one session slot.
The ILT oracle contradicts both ??RMapHelper spellings at either ILT, so the
BitFlags<11>/<17> template arguments are themselves suspect (Weapon may be 29 bits).
