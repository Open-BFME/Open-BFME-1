# Garrison transfer caller declaration

The 403-byte GarrisonContain::xfer body at RVA 0x0021DAA0 calls
ILT 0x00008CA1 at 0x0021DBAF. Retail bytes at that ILT jump to
0x0010C3E0, the 25-byte body already owned by Rva0010C3E0 in
Common/MidVirtualSlot90Forwarders.cpp. No function ledger row owns
that body under BfmeParticleSystemXferHandle.

The former name is a caller-side descriptive declaration, pinned to the
ILT. It does not establish a second real provider identity. The operation
on a particle-system field remains the same; this repair reuses the
existing address-derived provider instead of inventing another body or
renaming the provider based on one caller's field description.

Independent retail disassembly proves the contract: the callee loads the
second pointer from [esp+8] and receiver from [esp+4], then calls receiver
vtable slot 0x90 with table VA 0x01089218, that context pointer, and 4.
It ends with bare ret. The caller pushes the field address and receiver
at 0x0021DBAD/0x0021DBAE, and adds 8 to ESP at 0x0021DBB9. The replacement
uses the existing cdecl void two-pointer signature with unchanged values.
It does not claim that the address-derived name is an EA source spelling.

The current caller and provider pass 61/61 byte checks and 62 DIR32 checks.
With the actual provider refreshed against frozen a23092df4e, caller
unresolved names fall from four to three; other blockers and linked bytes
are unchanged. No header, provider, ledger ownership or pin is changed.
