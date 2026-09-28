# ConnectionManager constructor at RVA 0x00669630 (643 bytes)

Old: `?construct@BFMEConnectionManager@@QAEPAXXZ`  
New: `??0ConnectionManager@@QAE@XZ`

The independently matched `Network::init` at RVA `0x00681E40` constructs a
`ConnectionManager` with `new ConnectionManager` and then dispatches its
virtual `init`. The `symbols.csv` constructor entry identifies ILT `0x00049A94`
as `??0ConnectionManager@@QAE@XZ` and records this body at `0x00669630`; that
entry was independently decoded as installing vtable `0x0111A2B0` and
initializing the connection arrays. `vtable_lookup.py 0x0111A2B0` confirms that
this body installs the same table as the matched `ConnectionManager` destructor
at `0x00668D90`.

The old `construct` name came from the naked lift's local
`BFMEConnectionManager::construct` shim, not from the matched caller. The
caller, constructor ILT, and installed manager vtable establish the retail
constructor identity and contradict that lift label.
