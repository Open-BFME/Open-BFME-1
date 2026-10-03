# Opaque owned-member forwarding entry008D3040

Retail PE and Ghidra agree on complete8B ADD ECX,20; E9 ->008BDE20,
followed by eight INT3 bytes. Table VA01136E0C slot0 directly contains
VA00CD3040. Constructor008BE700 installs that table at008BE739 and
independently takes receiver+20 at008BE732 before calling the member
constructor008BE660 at008BE745. The same offset is therefore witnessed by
construction and this forwarding entry, not inferred from adjacency.

The existing opaque BfmeD1046::bfmeGo1046D provider at008BDE20 is54 bytes.
Its complete decode preserves incoming ECX in EDI, calls its reset helper
with zero, conditionally clears/releases its owned four-byte block, zeroes
[EDI], and ends plain RET at008BDE55. It consumes no incoming stack argument
and has no scalar-result computation. The existing native source matches
that no-argument void-thiscall ABI. No new pin or callee name is introduced.
callees.py was run for8B; its E8-only output omits this independently decoded
E9. Existing BfmeD1046 is declared only in TUs, not a covered shared header.

The new entry uses the fully opaque Rva008D3040::method name. No original
class identity or deleting-destructor contract is inferred from table slot0.
Only the observed member offset and existing cleanup binding are asserted.
The complete body passes the native resolved-callee gate.
