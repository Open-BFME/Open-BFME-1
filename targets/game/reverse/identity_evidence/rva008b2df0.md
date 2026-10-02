# RVA 0x008B2DF0 destructor

The 97-byte retail body ends with `ret` at +0x60 followed by INT3.
The already matched tail destructor at RVA 0x008B3980 writes vtable
VA 0x01136A40 and jumps directly to this body. Its source,
`VptrTailJumpDestructors.cpp`, already declares the virtual destructor of
the address-derived `Rva008B2DF0TailBase`; this conversion uses that existing
owner and symbol. No EA class or method identity is asserted.

Retail clears words at receiver offsets 0x20 and 0x24 before installing
vtable VA 0x01136058. It then calls RVA 0x008975D0 with two zero arguments,
clears the word at offset 0x18, destroys the member at offset 8 through
RVA 0x0089CC70, and installs the final vtable VA 0x01135D68. The existing
callee identities from `tools/callees.py` are retained: `Q4Base00D35D68::notify`
and `Q4Sub00C9CC70::~Q4Sub00C9CC70`. The latter entry is an ILT route to
RVA 0x0089C900. No new pin is needed.

The retail EH handler at RVA 0x00C58A93 references FuncInfo 0x00E47D6C.
`tools/eh_info.py` decodes two cleanup states: state 0 -> -1 invokes
RVA 0x00891800 on the receiver (the seven-byte final-vtable setter);
state 1 -> 0 invokes RVA 0x0089CC70 on receiver +8. These independently
support the member/base teardown order.

The source represents the initial two clears in a novtable outer destructor
and the common vptr-setting cleanup in a force-inlined intermediate destructor.
`Rva008B2DF0Middle` is an address-derived ABI view used to express that order,
not a claim about EA's original inheritance hierarchy. A flat destructor
from the bank had the same length but scheduled the initial stores differently.
The split C++ lifecycle matches all 97 bytes and the relocation targets under
the normal strict source gate. The vtable and member layouts reuse the Q4
family already reconstructed in this source directory.

All addresses, instruction extents, direct calls, and EH cleanup routes above
were checked against the unpacked BFME1 1.03 retail executable. No assembly,
generated-source edit, shared-header change, or new canonical name is used.
