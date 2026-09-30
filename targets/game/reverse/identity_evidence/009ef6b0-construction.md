# RVA 0x009EF6B0: standalone construction body

Baseline: `inputs/baselines/bfme1/retail-1.03-unpacked`.

## Boundary

The old carved candidate at `0x009EF280` spans 1,102 bytes and incorrectly
includes this separate routine. Its executable predecessor returns with
`ret 4` at `0x009EF68F` (offset `+0x40F`). Two alignment bytes follow.
The indirect jump at `0x009EF5D8` uses the seven-entry table at
`0x009EF694..0x009EF6AF`. Its targets are:

```
009EF5DF 009EF5F6 009EF617 009EF68A 009EF643 009EF65C 009EF673
```

Every table entry returns to the preceding body. The table ends exactly at
`0x009EF6B0`, where a new routine reads its own incoming stack argument and
ECX receiver, saves ESI, and calls the tree copy constructor. It balances its
own stack and returns with `ret 4` at `0x009EF6CB`. INT3 bytes at
`0x009EF6CE..0x009EF6CF` separate it from the EH prologue at `0x009EF6D0`.
The complete extent is therefore 30 bytes, excluding padding.

```
8b 44 24 04 56 50 8b f1 e8 23 f2 ff ff c7 46 0c
00 00 00 00 c6 46 10 01 8b c6 5e c2 04 00
```

This is a manual boundary recovery, not a Ghidra start claim. A scan of retail
finds no direct E8/E9 references to this entry and no literal pointer to its
VA. The independent calling frame, complete predecessor table, and separate
epilogue establish the boundary; there is no caller-based identity evidence.
`eligibility.carved_rows()` accepts the manually described 30-byte range as
uncovered by the current ledger.

## ABI and naming

The body passes its sole argument and unchanged ECX receiver to the 199-byte
tree copy constructor at `0x009EE8E0`. That callee copies the source tree,
returns the receiver in EAX, and ends with `ret 4`. Its existing ledger
identity is the STLport `_Rb_tree` copy constructor instantiated with the
address-qualified four-byte key `Gen_t_009ee8e0_k4`.

The new body then writes zero to receiver `+0x0C`, writes one byte with value
one to `+0x10`, and returns the receiver. The native STLport tree is 12 bytes;
the modeled containing object is 20 bytes. The same tree-copy and trailing
initialization pattern appears in the already matched asset-registry key
collection source, `AssetRegistryKeySet009EF7D0.cpp`, which also calls
`0x009EE8E0`. This supplies the assetmanager source placement and structural
context, without establishing the original type name.

The owner remains `Rva009EF6B0`; the trailing fields keep offset names.
The source uses the existing callee's template name and adds no pins.

## Verification

The native C++ constructor probe emits 30 bytes and matches all non-relocation
bytes. The sole relocation is the tree-copy call at offset `+0x08`.
`add_match.py` passed the scoped build gate (1/1 functions), including call
resolution to retail. No source or pin repair was needed for the callee.
