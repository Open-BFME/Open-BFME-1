# 0x01142BA0 is one table with two spellings

dir32_addresses.csv records both `?g_bfmeVp6SelectorMap@@3PAEA` and
`?Rva01142BA0Table@@3QBGB` at VA 0x01142BA0; neither had a definition.
Retail .rdata there holds ten dwords {1,0,1,1,1,2,2,1,2,2} (the VP6 per-mode
reference-frame map), followed by zero padding up to the 0x01142BE0 mask table.

Readers: 0x009B4880 (BfmeVp6PredictValue.cpp, byte read at [selector*4]),
0x009AB950 and 0x009AB990 (word reads at [index*4]). One datum can carry one
name, so the table keeps the address-derived `Rva01142BA0Table` that two
readers already use; "SelectorMap" described only one reader's use and is not
an evidenced identity. All three readers still byte-match.
