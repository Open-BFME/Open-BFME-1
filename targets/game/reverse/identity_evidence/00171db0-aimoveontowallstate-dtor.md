# AIMoveOntoWallState complete destructor owns the 106-byte body at 00171DB0

0x00171DB0 (106 B, SEH frame) stores VA 0x01098540 at [this], which
dir32_addresses.csv records as ??_7AIMoveOntoWallState@@6B@; it then shuts down
and deletes the owned pointer at +0x24 and calls the base destructor through
ILT 0x00016725 -> 0x000A1B30 (ledgered ??1Rva000A1B30Holder@@QAE@XZ). ??_GAIMoveOntoWallState
(slot zero of that vftable via ILT 0x0003125A) calls it as its complete
destructor through ILT 0x00010C4E (tools/callees.py). A destructor that
re-seats a class's own vftable and is called by that class's scalar-deleting
destructor is that class's destructor, so ??1Rva00171DB0@@UAE@XZ is
??1AIMoveOntoWallState@@MAE@XZ (protected, matching the ??_G row's access).
