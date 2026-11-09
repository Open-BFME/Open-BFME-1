# 00C6FF10 duplicate storage

The 2026-11-06 handoff documents a one-byte initializer definition competing with the separately matched 12-byte tree cell at VA 0x012F10DC. Deleting the initializer removes compiler-generated startup rows. A trial marking only that one-byte definition select-any retained all 15 rows, but does not fix a collision with an exclusive definition.

Both definitions now provide twelve zero bytes with select-any linkage. The initializer remains in its original TU; its `.CRT$XCU` entry is separate from the data COMDAT. Both scoped provider gates pass (15/15 functions and the data row), as do the two tree consumer gates (5/5) and S3SingletonForwarders (120/120). A focused MSVC 7.1 link of the two objects with `/FORCE:UNRESOLVED` produced no duplicate-definition diagnostic and retained the CRT section; unresolved externals mean this is not a full-link proof.

`link_check.py` on Rva0040AC30Owner reported LINKED 0 -> 0 on the old census before the change. The current preview after it is UNKNOWN: 4,187 changed ledger objects were unavailable, so no linked-byte gain is claimed. A full census was started to refresh the object set. BFME 2 donor revision 2bac16a657d32220670e4b9c7ec056986de61692 has no matching linking provider packet; this repair is based on BFME 1's data and initializer evidence.
