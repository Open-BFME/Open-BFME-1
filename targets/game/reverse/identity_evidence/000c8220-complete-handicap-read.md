# Complete Handicap dictionary-reader extent

The362B claim at000C8220 ends after restoring FS:[0] at000C8383.
The same path then executes ADD ESP,30 at000C838A and RET4 at000C838D;
INT3 begins000C8390. Both nested-loop exits lead through the final string
release and this epilogue, proving a contiguous368B body. Local PE decode
and Ghidra read_memory004C8370..004C8397 independently agree.

The existing native Handicap_readFromDict_Thunk.cpp implements the literal
GeneralsMD Common/RTS/Handicap.cpp readFromDict twin: combine HANDICAP_,
BUILDCOST/BUILDTIME and GENERIC/BUILDINGS keys, query the dictionary and
store present real values. Retain this independently supported identity;
only enlarge the ledger extent after full native byte/reference checks.
No source declaration, lifecycle, callee pin or shared header is changed.
