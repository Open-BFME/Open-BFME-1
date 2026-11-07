# Apt route-key consumer trial at 0x01338480

The 178 four-byte slots beginning at VA 0x01338480 have one emitted owner,
`_bfmeObjDAE`. The matched native array initializer and registered cleanup
prove that extent. The three historical g_bfmeRouteKeys1282 spellings
also map to 0x01338480 in dir32_addresses.csv. BfmeConv1569.cpp already
references the emitted owner.

A trial switched the nine remaining authored C++ consumers to the emitted
symbol. The before and after builds both pass all 21 rows across the nine
consumers and the owner. Eleven compiled bodies change only 18 DIR32 symbol
bindings, with the same relocation offsets, operand addends and effective
retail VAs. The local link preview times out on both sides.

The name regression check rejects all nine replacements because it sees a
descriptive name replaced by a placeholder. The original name describes
those particular consumers, even though it labels only one use of a shared
array. No evidence invalidates that descriptive use, so the batch was
reverted. Three generated assembly units also retain the old name. Closure
requires a source representation that keeps the descriptive identity and
a supported reconciliation for those generated references.
