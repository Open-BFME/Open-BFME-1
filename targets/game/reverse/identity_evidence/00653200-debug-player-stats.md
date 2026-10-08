# Retail 0x00653200 player-stat debug walk

The dump is the static `debugDumpPlayerStats(const PSPlayerStats&)` from `PersistentStorageThread.cpp`, adapted to BFME's existing `BfmePlayerStats` view. The Zero Hour donor contains the same release-build map traversal: `DEBUG_LOG` disappears, but iterator increments remain. BFME omits `techCaptured` and appends the four streak maps. The independent landed formatter at 0x00655360 and merger at 0x00656D60 use this view. No new layout or callee pin is introduced.

## Boundary and ABI

The preceding body returns at 0x006531EC and is followed by INT3 padding through 0x006531FF. The target begins at 0x00653200, contains only the map walks, and returns at 0x00653560. Every conditional branch targets an instruction within that extent. There is one return, no outgoing jump, no stack argument access, no indirect call, no receiver adjustment, and no exception registration or cleanup.

ESI is a borrowed input pointing to the statistics record. The target never writes it or any record field. EAX carries the iterator, ECX holds the header, and each increment call pushes one node pointer and removes that argument with `add esp,4`. The complete callee 0x0082B870 takes its argument from the stack, returns a node pointer in EAX, and preserves ESI. Its field accesses are the parent, left and right pointers at node offsets 4, 8 and 12. The canonical declaration is `_STL::_Rb_global<bool>::_M_increment`.

A scan of the baseline sections finds no direct CALL or JMP to this entry and no stored absolute VA of the entry. This establishes no retail caller evidence; the source does not claim a live caller. The complete body itself fixes the incoming ESI and stack contract. Same-TU compilation emits that private convention from ordinary static C++. An explicitly absent-from-retail emitter retains the helper without changing the real matched `trackPlayerStats` body.

## Container evidence

The complete merger at 0x00656D60 reads each key at node+0x10 and its count at node+0x14, stores the latter through the map subscript result, and uses an unsigned `jbe` guard for positive counts. Its actual call at 0x00656D81 reaches ILT 0x0003DD2A, whose decoded JMP reaches 0x000A56D0. That complete subscript uses signed `jl` and `jge` key comparisons and constructs an eight-byte value containing the key followed by a zero count. It returns node+0x14 on both result paths.

The subscript call at 0x000A5722 reaches ILT 0x000296BD and the complete hinted insertion at 0x000A4C90. Its allocation path reaches ILT 0x00015087 and the complete insertion at 0x000A3D70. Both value-construction calls in that body reach ILT 0x0002C3A4 and the complete helper at 0x000A36F0. This helper checks destination null, then reads exactly two dwords from source+0 and source+4 and writes destination+0 and destination+4 before returning. There are no additional field accesses or destructor calls in the value helper. Thus the payload evidence is `pair<const int,unsigned int>`, not a size-based assumption. All maps traversed by the target have corresponding independently decoded merger operations.

## Experiments and refutation

The original TU compiles but removes the unused static helper. A scratch copy with the authentic caller enabled and the BFME map order produces the complete target exactly. Replacing that scratch-only caller change with the emission anchor gives the same bytes; retaining the donor's scalar debug statements does too. The checked extents, complete decoded bodies, source snapshots and unedited probe outputs are retained under `build/target-00653200/`. The production gate passes every claimed body in the changed translation unit; `gate-final-bash.log` is the raw receipt. `verify-evidence-v2.log` checks every branch destination, compares all map header offsets against the complete merger, and decodes the emitter that supplies ESI. The raw baseline scan is `xrefs.log`; the value helper is `decode-construct.log`.

This identity would be refuted by a different complete entry or return boundary, an incoming ABI use contradicting the ESI input, a value helper that reads or writes another field, a signed count guard, or a donor/view loop order that differs from the retail record offsets. Byte equality alone is not the identity evidence.
