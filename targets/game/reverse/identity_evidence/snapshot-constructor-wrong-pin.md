# Snapshot constructor pin points to a different constructor

The retail PE export `??0Snapshot@@QAE@XZ` is at ILT RVA00024C80. Its bytes `e9fb640400` reach RVA0006B180. That complete nine-byte body is `8bc1c70044370701c3`: return the receiver in EAX, install vptr VA01073744, RET, followed by INT3 padding. The existing canonical function row already identifies that body.

The symbols.csv pin instead gives the same name RVA00044030. Those bytes are `e9cb311e00`, reaching RVA00227200. This is a 398-byte SEH constructor, whose first32 bytes are `6aff68b7d2000164a10000000050648925000000005153568bf18974240833db`. The body is independently established as OpenContainModuleData by its installed vtable, derived constructors and module factories in `00227200-open-vs-cave-contain.md`. It cannot be the exported nine-byte Snapshot constructor.

Both stubs and both body heads were checked through Ghidra MCP read_memory (program lotrbfme.exe) and direct pefile decoding of the unpacked retail baseline, SHA256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`. No callee name inferred from another guessed pin is needed for this contradiction: the original export names the real Snapshot constructor.

AGENTS.md warns that pins are candidates, and a resolver match does not validate a pin. Delete this wrong candidate while retaining the exported Snapshot function row and all legitimate OpenContainModuleData bindings. The deletion-impact scan identifies seven possible caller rows; inspect their actual relocations and byte-verify the affected scope. No source or signature change is required if the current callers already use the genuine OpenContainModuleData constructor.
