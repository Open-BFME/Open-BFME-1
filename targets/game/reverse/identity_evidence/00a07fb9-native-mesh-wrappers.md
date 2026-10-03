# Two native mesh dispatch wrappers

The original d3dx9.lib member `obj\i386\createmesh.obj` supplies independent
code COMDAT sections354/372. Both are thirteen bytes, without relocations:
`8b81340200008b0850ff5130c3`. Their original signatures are:

- `?UnlockVB@?$GXTri3Mesh@G$00$0PPPP@@@QAEJXZ` (ushort family)
- `?UnlockVB@?$GXTri3Mesh@I$0A@$0?0@@QAEJXZ` (uint family)

The `QAEJXZ` suffix establishes public thiscall, long return, no explicit
arguments, non-const receiver. The two enclosing original code sequences
are distinct: sections354..368 concatenate to91 bytes occurring once at
RVA00A07FB9, while sections372..386 concatenate to89 bytes occurring once at
RVA00A08036. Their final getter bookends use word and dword indexing,
respectively. See the separately committed mask-family evidence for their
section tables. Thus identical wrapper bytes do not merge their entries.
The complete RETs are at A07FC5 and A08042; the next original code section
begins immediately afterward. Ghidra read_memory agrees with retail.

Retail loads the object pointer at receiver+234 into EAX, loads that object's
table into ECX, pushes EAX, calls through table+30, and returns immediately.
The indirect callee therefore consumes the one four-byte stack receiver:
there is no caller stack adjustment. Its result propagates unchanged to the
original long return. A typed `long (__stdcall *)(opaque_object *)` slot
models precisely this contract; ECX is a scratch table pointer, not a new
thiscall receiver. No new semantic slot or interface name is claimed.

Both ordinary C++ bodies reproduce all thirteen bytes on their first probe.
Address-qualified owner, interface and table views preserve the measured
storage/dispatch ABI without importing a guessed external interface layout.
There are no data references or callee pins to mask a mismatch.
