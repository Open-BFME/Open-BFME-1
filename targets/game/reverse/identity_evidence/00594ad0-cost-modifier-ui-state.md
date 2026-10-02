# RVA 0x00594AD0: cost-modifier UI state helper

The old PartitionFilterIsValidCarriage::allow assignment is unsupported. This
524-byte native body maintains a twelve-byte UI state subobject; no authentic
owner or member spelling has been established. Keep its address-derived dump.

Retail ILT RVA 0x000474BF reaches the body. Its sole executable caller is
0x0059751E within anonymous body 0x00597130. At 0x0059751A it pushes EBX,
then sets ECX = EBP + 0x1C at 0x0059751B. The receiver is therefore an embedded
subobject at +0x1C of the caller's receiver, not the caller's complete object.
No stored body/stub pointer was found, so there is no witnessed vtable slot.

The candidate resolves native literal CostModifierUpgrade, VA 0x01090004,
at 0x00594B29, and later constructs APT:CostModifierUpgrade, VA 0x0110C068,
at 0x00594C39. It calls the existing apt-text helper through ILT 0x0000BDCA
at 0x00594C6F, using a UnicodeString result built by formatting the integer
at 0x00594C21. The two niladic UI-event helpers at 0x00563F50/0x00563F80 are
called when receiver byte zero changes. Receiver +1 is the cached-valid flag,
+2 a cached byte, +4 a word reset to zero, and +8 the cached formatted integer.
The value provider 0x0058B590 is called with the object-associated Player.
These native string and field facts do not establish a C++ method spelling.

Normal RET 4 is at 0x00594CB6; the last exit's RET 4 is at 0x00594CD9,
followed by INT3 at 0x00594CDC: exactly 524 bytes. Routes, strings and full
instructions were checked against retail-1.03-unpacked lotrbfme.exe via
pefile/Capstone. No source, pin or ledger identity is changed.
