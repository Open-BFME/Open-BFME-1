# AptInGameChat identity

The matched 987-byte constructor at RVA 0x005160E0 constructs the 0x2A4-byte screen, registers seven `AptInGameChat::` selectors on the same receiver, and stores that receiver in its singleton. The complete destructor at 0x00511F50 resets the corresponding two vtables and unregisters InitGadgets only when the singleton equals this receiver. The scalar-deleting destructor at 0x00512860 and the matched update body identify the same lifetime. These retail witnesses corroborate the WorldBuilder class labels independently of pairing alone.

Rename only the stand-in class `BfmeAptScreenInGameChat` to `AptInGameChat`. Preserve the other address-derived views, members, signatures and legacy vtable alias-variable names.

For InitGadgets, the constructor associates the literal `AptInGameChat::InitGadgets` with callback ILT RVA 0x00010280. Its retail bytes `e9 db 5b 50 00` jump to 0x00515E60. The matched 510-byte body there takes gadget name/user data/GameWindow arguments and initializes the chat entry, friends list, chat box and friend controls. This directly corroborates the strong EA label `AptInGameChat::InitGadgets` at the same body address. Rename that method only; no other selector is used to guess an unproved C++ method name.

Verify all functions in the ten dependent sources and the full gate, including vtable DIR32 records, before normal master publication.
