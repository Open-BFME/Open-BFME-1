# RVA 0x002DECC0: string-vector dispatch

The complete 163-byte body ends at 0x002DED63 with ret8. Its first argument is unused and its SECOND argument is a nullable receiver: after the three EH pushes and saved EBX, `[esp+0x18]` addresses entry ESP+8. Keeping that order is essential; the receiver's dead incoming slot is reused for the temporary string.

The owner has a canonical vector of four-byte AsciiString objects at +0x58 and an unsigned value at +0x64. It copies each indexed string into a local, resolves the string's name, calls the external receiver with signed result and the unsigned owner value, then destroys the local and reloads vector size. String copy/set/release aliases naming GameSpyGroupRoom or UnicodeString in the disassembly are not type evidence: the actual calls are the established StringBase<char> bodies 0x887B60 and 0x887940. The empty literal is verified by the scoped gate.

Two additive address-derived body pins are independently justified:

- `Rva001C0930FindNameIndex(const char*)` at 0x1C0930, reached through ILT190F1, is a full 71-byte cdecl lookup. It scans the pointer table at VA0x12A6918, compares the input string via the imported comparator, returns the signed index or -1, and has a plain RET. The source does not adopt the ledger's uncertain BitFlags<38> specialization identity.
- `Rva001BE220Receiver::dispatch(int,unsigned)` at 0x1BE220, reached through ILT2852E, loads its receiver from +0x1DC and tail-jumps through ILT12B70 to 0x2572A0. The full 185-byte target is the established ObjectSMCHelper::setModelConditionState(int,unsigned): signed condition bounds, unsigned frame duration and ret8. Thus the old no-argument declaration of the 11-byte thunk does not describe this caller's ABI. This pin names the thunk BODY with its actual incoming receiver, not a route-only alias.

Canonical vector size/index access fixes the retail reload pattern. Direct copy initialization `AsciiString local = m_strings[i]` fixes the remaining eight register-allocation bytes. The final scoped gate verifies all 163 bytes and relocations with no shared header or existing caller edits. Both proposed pins were checked before insertion and the complete pin-consistency check passed afterward. This adds 163 C++ bytes with unchanged boundaries and total exact coverage.
