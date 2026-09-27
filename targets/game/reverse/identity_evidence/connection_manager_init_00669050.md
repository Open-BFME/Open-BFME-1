# ConnectionManager virtual init at RVA 0x00669050 (694 bytes)
Old: `?init@BFMEConnectionManager@@QAEXXZ`
New: `?init@ConnectionManager@@UAEXXZ`

Vtable VA 0x0111A2B0 slot 0 points through ILT 0x0001942F to this body.
The same vtable is installed by the complete constructor at 0x00669630 and
destructor at 0x00668D90. Independently matched Network::init (0x00681E40)
constructs a ConnectionManager and dispatches init through that slot.
Zero Hour ConnectionManager::init corroborates the two pending command lists,
frame data cleanup, disconnect manager and wrapper list creation, and file-map
clears. BFME's extent includes per-player state clears and final leave flags.
Only class identity and virtual qualifier are corrected; method name retained.
