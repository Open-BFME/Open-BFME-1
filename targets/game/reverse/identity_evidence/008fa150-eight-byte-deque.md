# RVA 0x008FA150: eight-byte deque map initialization

The old lift's PartitionCell-pointer identity is refuted by independent retail
arithmetic, even though its naked free-function object symbol copied the bytes.
The retail image is inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe.

- Entry takes the requested element count from the one stack argument and
  divides it by 16 (SHR EBX,4), then adds one for the number of nodes.
- Each node allocation requests 0x80 bytes. Start/end iterator node limits
  are advanced by exactly 0x80 bytes.
- The final current pointer is finish.first + (count & 15) * 8, using
  LEA EDX,[ECX+EAX*8] at +0xBC. Thus the element stride is eight bytes.
- This 32-bit executable has four-byte PartitionCell pointers; that old
  specialization would use 32 elements per node and a four-byte final stride.

The complete algorithm corresponds to inputs/vendor/stlport/stl/_deque.c
_M_initialize_map and its inlined _M_create_nodes: choose max(8,nodes+2),
allocate/center the map, allocate every node, and initialize both iterators.
The known deque layout has start at +0, finish at +0x10, map at +0x20 and
map size at +0x24. The only direct callees are existing operator new at
RVA 0x00881F30 and the native allocator at RVA 0x0082E540. tools/callees.py
reports both; no new pin is needed. Retail has no exception registration
around this loop, matching the existing no-exceptions deque emission TUs.

No source-backed lexical element identity is asserted. Rva008FA150Element is
an opaque eight-byte emission view. The ledger's Rva008FA150Owner::initialize
is likewise address-derived and maps through object-symbol to the actual
STLport instantiation. This replaces the unsupported PartitionCell claim
rather than proposing a different canonical specialization.

The entry has SUB ESP,8 and four saved registers. RET 4 at +0xC8 ends the
203-byte body; INT3 padding starts at +0xCB. The replacement preserves this
complete extent and deletes the naked lift. The explicit native instantiation
matches all 203 bytes modulo its three relocations before strict verification.

The pre-existing symbols.csv candidate for the PartitionCell specialization
is retained outside this body correction. A removal audit made the normal
hook reject two existing PartitionManager.cpp constructor rows: their emitted
four-byte specialization still calls this eight-byte target. Their constructors
and allocator proxies need a separate identity repair. That pin is NOT evidence
for PartitionCell here; the independent stride proof above refutes it. No new
semantic pin or fallback route is added by this conversion.
