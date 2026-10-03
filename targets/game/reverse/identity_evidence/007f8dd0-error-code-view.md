# Address-qualified table method at007F8DD0

Matched destructor007F8DA0 and deleting wrapper007F8F40 install table
VA0112B954. Its slot2 explicitly points to RVA007F8DD0, independently
establishing the entry. The full20B body ends in RET4 at007F8DE1, followed
by twelve INT3 bytes. Ghidra read_memory at00BF8DD0 agrees over all32B.

Retail reads the global pointer at VA012C3B28, takes its one stack word
as the message receiver in ECX, pushes a zero fallback and the key, then
calls007E8900. The global's shipped DWORD is0112B948, whose complete
string is `errorCode\0`. The source retains the writable pointer load;
it does not replace that indirection with a hardcoded literal. Its new
extern name is explicitly VA-qualified and creates no storage or pin.

The callee inventory names the existing matched BfmeThingRF::bfmeGoRF
binding at007E8900. Its complete45B body reads the message's+10 record,
calls the established tag lookup007EBCA0, returns the fallback if absent,
or calls the signed-decimal parser007EE720. The matched TID/PID consumer
008037A0 in BfmeConv1287.cpp already declares this legacy opaque getter
as two pointer-sized arguments/result and converts its returned32 bits to
int. The new wrapper reuses precisely that binding and conversion; it
does not revive the competing bfmeGetSA pin or invent another identity.
The pointer spelling is the existing ABI view, not evidence that the
parsed integer is an actual object pointer.

The new table method returns that integer unchanged and pops its one
message-pointer argument. Its actual owner and method spelling remain
unknown, so the entry is fully address-qualified. There are no new fields,
callee aliases, shared declarations or pins. Strict verification checks
the complete20B body, existing direct callee and global-pointer operand.
