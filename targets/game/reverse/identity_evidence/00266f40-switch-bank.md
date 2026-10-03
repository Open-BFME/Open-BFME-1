# RVA 00266F40: switch boundary and draft contracts

This is evidence for an **unmatched bank**, not a new identity or pin.
The draft keeps `Rva00266F40::method` because this session has not established
an independent per-family WorldBuilder slot alignment for the suggested name.

Retail `00266F40..002671E9` is 681 executable bytes ending with `ret`.
`002671E9..002671EC` is a three-byte LEA alignment instruction. The indirect
jump at `0026704F` indexes the five-dword table at `002671EC`:
`00667056,0066706C,006671B8,006671DC,006671D2`. The table ends at
`00267200`, followed by INT3 padding. The existing 704-byte ledger extent
therefore is valid; probe's linear-disassembly warning at +2BF is decoding
inline table data. Ghidra's initial 291-byte region similarly omits switch
arms; decompilation recovers them. No ledger boundary change is required.

The sole table reference to ILT `00007DBA -> 00266F40` is VA `010B7494`.
Constructor `00266240` installs that table at +10, and initializes state at
+38, counter +3C, target ID +40, position +54, toggle +60, delta +64, pending
+70. Thus incoming receiver is complete object +10; object pointer and
module-data pointer are at incoming -8 and -C. The draft uses canonical
Object/Thing and Coord3D declarations, with an opaque secondary-interface
view for the unknown AI slots.

Independently decoded direct helpers:

* `001F8AB0`, reached through `0002FC7A`, is cdecl with one Object pointer.
  It initializes a NameKey from VA `01090B3C`, **DynamicPortalBehaviour**,
  walks Object+1F0 modules, compares their slot +10 results and returns the
  matching pointer or null. The WorkerAIUpdate/getPool ledger names are not
  evidence for this contract.
* `001F84C0`, through `0003C740`, consumes ECX, has no stack arguments and
  returns at `001F8532`. It checks receiver+3C, clears six pointer slots at
  +24, and invokes virtual deleting destructors. The draft calls the existing
  address-qualified thunk; it does not add a MemoryPool identity.
* `001F9180`, through `0003BFF7`, consumes one stack argument and returns a
  boolean-like AL. The caller passes zero and tests AL.
* `001F1370`, through `0001336D`, is a two-argument AI command, constructing
  command ID 31h before dispatching through the command receiver. It ends
  `ret 8` at `001F1438`, contradicting the inherited destructor name. The
  caller supplies receiver AI+20, zero, command source 2.
* `002666A0`, through `00020455`, returns a nontrivial Coord3D with hidden
  first result slot plus Object*, Coord3D*, bool*. See the previous bank's
  `002666a0-coordinate-return-bank.md`. Consuming that temporary directly
  avoids an extra wrapper copy. No helper pin has been added or renamed.

Native source experiments and measured residuals are recorded in re_attempts.
The first draft used a complete-object local and compiled 724 bytes. Keeping
incoming secondary `this` directly reduced it to 688 bytes. Limiting the first
coordinate's scope recovered retail frame 20h from 2Ch. Reusing one coordinate
instead made Object's position address stay live, adding a spill and frame24h.
All trials remain scratch/banked evidence; no source is promoted to game/.

Inlining the native three-word assignment body reduces the draft's remaining
structural discrepancies to one setup ordering and the EBX/EBP mirror (which
also changes the zero-displacement encoding and switch alignment). Native code
is 700/704 bytes, 468 differing non-relocation bytes, measured quality 0.3239;
normalized instruction shape 0.953 is **not** byte quality. Moving the target
pointer declaration ahead of the owner does not change emitted bytes. The
bank is not eligible for promotion until these differences and all canonical
helper/virtual-slot bindings are verified. In particular the class/struct
Coord3D mangling distinction must not be hidden with a fresh alias pin.
