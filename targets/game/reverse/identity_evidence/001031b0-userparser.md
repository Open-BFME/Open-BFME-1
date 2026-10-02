# UserParser destructor identity

Retail lotrbfme.exe SHA256 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75.

Matched DataChunkInput::registerParser at RVA00103840 (113 bytes) allocates0x1C bytes, writes vptrVA01086348 to [allocated+0] at instructionRVA00103852 (entry+0x12), sets labels at+10/+14, callback+0C, user data+18 and next/previous+4/+8. Those roles are independently visible in the matched parse caller and native DataChunkInput layout. This identifies the allocated class as UserParser rather than using an anonymous destructor name as evidence.

Raw retail vtable first DWORD atVA01086348 isVA0042572F; its E9 routes toRVA00103180. That30-byte body callsILT000068CF, tests the deleting flag and calls operator delete, returns this, ret4. ILT000068CF routes toRVA001031B0.

RVA001031B0 is83 bytes through ret at+52 with followingCC padding, agreeing with the independent Ghidra boundary. It writes exactlyVA01086348, destroys member+14 then+10 through887940 (the narrow StringBase release body), and has an EH state frame for those members. It emits no pool or base cleanup; this does not prove absence of an empty base or authorize a new inheritance claim. This is the UserParser complete destructor used by the vtable deleting destructor. Native UserParser already declares a public virtual destructor; this repair preserves that ABI declaration and field layout.

The old Gen_001031B0 identity in Bfme5TwoMemberDestructors.cpp is an address-based placeholder. Its two member offsets and vptr agree, but it fails to supply the real unresolved UserParser destructor. Only that placeholder class identity is replaced in the same provider source; its empty destructor body and canonical ascii_string.h-backed members remain unchanged. The Gen_0014B790 sibling remains. No authored EH row belongs to the old source: generic uw_00bfc990 and eh_00bfc99b rows remain unchanged.

Independent peer review confirmed the EH binding directly: destructor FuncInfoVA011E9F74 has maxState1 and unwind mapVA011E9F6C with(-1,VA00FFC990). FuncletRVA00BFC990 takes savedthis[ebp-0x10]+0x10 and routes throughILT0000D828 to0005EE90 then00887940. The generic uw_00bfc990 and eh_00bfc99b rows remain unchanged.

The generated deleting-wrapper row at00103180 remains unchanged because the supported add_match replacement workflow does not accept gen-dtor rows. Its existing Gen_dtor_00103180 destructor pin atILT000068CF is retained for the untouched generated source. Existing dir32 addresses for the old and native vtable symbols are not removed; only the independently proven83-byte real-source destructor row changes identity. The wrapper chain above is retained evidence for a separately supported follow-up.

Final provider scope: rename Gen_001031B0 to UserParser within Bfme5TwoMemberDestructors.cpp, retaining the already-clean provider and its canonical ascii_string.h include. DataChunkInput.cpp is unchanged. A tested but abandoned move into Input was byte-exact but its local string declarations produced link-selection mismatch; that shape is not part of the final patch. The proof names the existing padded class slice only; it does not add field names or infer inheritance.
