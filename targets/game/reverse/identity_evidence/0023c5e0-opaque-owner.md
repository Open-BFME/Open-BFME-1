# RVA 0023C5E0: extent and opaque owner

The preferred bank calls its owner MemberSelection0023C5E0. This is a
convenience description of the reconstruction, not a recovered BFME class
name. No named caller, in-exe name table, Zero Hour twin, or aligned vendor
vtable establishes that owner or the member name. name_oracle reports no
witnessed layout for Rva0023C5E0. The new source therefore uses the fully
opaque Rva0023C5E0::method identity rather than promote the bank name.

Retail's random-call source strings identify HordeContain/HordeContain.cpp
at lines 4092 and 4151. They establish source placement, not a member name.
The body queries a list through a secondary receiver at this-0xC4, virtual
slot +0x104, and traverses a set at this+0x30. Those offsets justify only the
address-qualified layout views in the reconstruction.

The old 784-byte dump stops before the complete epilogue. Direct disassembly
of the retail-1.03-unpacked image proves:

* +30E pop edi; +30F pop esi;
* +310 pop ebp; +311 pop ebx; +312 add esp,0x18;
* +315 ret 12; INT3 starts at +318.

The full extent is 792 bytes. Initial Ghidra function creation also stopped
at the old 784-byte boundary; the retail epilogue, not that truncated extent,
is the boundary evidence. No other ledger row starts within the added bytes.

The preferred bank emits seven differing bytes. Archived alternative
438269d555fe3264cdd05231d30d742b15f0762ad9a11c42df24449149994f0c
emits four over the full extent. Including the existing
Common/Thing/GameLogicObjectLookup.h with BFME_GAMELOGIC_LOOKUP_VISIBLE
exposes the already matched, noinline lookup's read-only effects and removes
those four register differences. Its ABI and bindings remain unchanged.

Strict verification passes all 792 bytes and 15 relocations, both debug
literals, three float constants and six DIR32 references. No new pin or
semantic callee alias is introduced.
