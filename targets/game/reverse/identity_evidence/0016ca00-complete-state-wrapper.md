# Complete 0016CA00 state-table wrapper

Retail PE and Ghidra read_memory agree on19 bytes beginning0016CA00:
MOV EAX,[ECX+1C]; MOV ECX,[EAX+10]; MOV DWORD PTR[ESP+4],1;
E9 to ILT00007513 ->001C9B80. Thirteen INT3 bytes start0016CA13.
Table VA01097D40 slot5 directly holds ILT VA0040D06C, which jumps to
VA0056CA00. Constructor00171250 stores this table at00171271 after its
base constructor. Five more constructor-family stores reference the same
table. These establish the complete entry and receiver chain, not a full
original class or method name.

Existing generated j_0016ca0e is the final E9 instruction of that body.
It has no independent Ghidra references and neither the table nor ILT enters
there. Retire only its ledger row, with a tombstone; do not edit its generated
source. The native replacement claims all19 bytes once.

callees.py was run for the19-byte extent; its E8-only list omits the E9.
The complete53-byte001C9B80 callee independently consumes the one incoming
stack word into EDI at+15, forwards it to receiver+1FC virtual slot+158
when nonnull and receiver+264 helper, and ends RET4 at001C9BB2. It does
not dereference the incoming word. The existing opaque
BfmeThing916D::bfmeGo916D(void*) binding remains unchanged. The literal
reinterpret_cast<void*>(1) expresses exactly the forwarded physical word;
it is not a semantic pointer-parameter claim. The wrapper's overwritten
incoming word is likewise explicitly unsigned ABI storage of unknown
original type. No new callee identity or pin is introduced.

The wrapper and both observed member offsets have address-qualified names.
The scratch probe matches all19 bytes modulo its one call relocation, and
the production gate verifies that relocation against the existing callee.
