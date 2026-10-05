# TheRecorder at VA 0x012ED62C

The datum is one four-byte `.data` pointer cell, initially zero. Its canonical type is `RecorderClass *` and its spelling is `?TheRecorder@@3PAVRecorderClass@@A`. No other datum or DIR32 name starts inside those four bytes. A zero initializer has no pointer relocation; the executable has no PE base relocation directory.

Zero Hour Common/Recorder.cpp:359 and Common/Recorder.h:158 define and declare RecorderClass *TheRecorder. Retail startup registers this cell; replay UI readers and GameLogic mode tests read the recorder fields, and the existing singleton pin names getLastReplayFileName from GetReplayFilenameFromListbox. All observed retail reads use the same four-byte cell. The address-derived forwarder and update views are explicitly cast from the canonical RecorderClass pointer.

The datum has no function receiver or argument contract. Its users load it as the receiver or address of the single object described above. Each use that needs a different existing field or method layout explicitly casts the canonical pointer. No inheritance, method identity, wrapper, forwarder or function body is introduced by this correction.

The declaration observation for each competing decorated spelling is recorded in `build/rlink/pointer-globals-20261005/singleton-spelling-counts.log`. The typed declaration counts distinguish the spelling from the bare identifier; missing declarations and comments do not count as live definitions.

Raw evidence is `build/rlink/pointer-globals-20261005/retail-012ed62c.log`, `retail-xrefs.log`, `xref-bodies.json`, `singleton-pins.log`, `zh-declarations.log` and `retail-identity-strings.log`. Every detected read or write and its retail containing body appears in those logs. Calls in their instruction windows have their raw five-byte E9 chains followed to the final target. `retail-class-tags.log` records the BFME-only subsystem literals.

A consumer loading a different address, a different writer/tag/constructor chain, a receiver layout incompatible with the observed accesses, a nonzero initial dword, an overlapping datum, or any changed compiled instruction would refute this correction. Source builds must retain Functions OK for every existing row, and add_data_match must prove this cell independently.
