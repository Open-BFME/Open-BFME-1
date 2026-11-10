# Q1 local-set destructor reconciliation

Queue rank 42, census 90c15cdeca. BFME 1 base cbbf3cae8d plus session evidence commit.

The older `Q1Receiver0134FAAC_m009F0E50.cpp` destroyed its 12-byte tree by instantiating the pointer-set destructor. Its emitted `Q1ReceiverLocalSet` destructor consequently differed from the first unpinned copy selected at the census. The recently recovered `assetmanager_impl.cpp` already uses the witnessed ILT `j_00015d7a`, preserving the x86 thiscall receiver through a single-inheritance member pointer. Adopt that existing local teardown in the older consumer; no new name, pin, layout or body row.

BFME 1 evidence: original consumer comment records retail cleanup ILT 0x00015D7A -> 0x00140950; its scoped 327-byte row remains exact after the change, including all relocation, constant, DIR32 and body guards. The provider `assetmanager_impl.cpp` passes all 7/7 function rows and its data row. `find_declared_unmatched.py` reports no unmatched definitions.

Before: `link_check.py --census-only game/Libraries/Source/assetmanager/Q1Receiver0134FAAC_m009F0E50.cpp` reports COMDAT destructor differs from first copy, 0 linked bytes. After: same command reports LINKS, preview 0 -> 327 bytes. This is a census preview, not a fresh census or a full executable link; current-dependency check is recorded separately when available.

Donor review (read-only existing reference at 2bac16a657d32220670e4b9c7ec056986de61692): `Code/Libraries/Source/assetmanager/assetmanager_impl.cpp` uses the same ILT-bound member-pointer destruction pattern in Q1ReceiverTreeStorage. Paths map Code/Libraries to game/Libraries; no donor addresses or compiler flags imported. BFME 1's already verified implementation supplies the actual binding and the target evidence.

Current-dependency check: `link_check.py --compile-limit 0` returns LINKED PREVIEW UNKNOWN because 22,802 new/changed ledger objects are unavailable in this isolated worktree. No current linked-byte gain is claimed.
