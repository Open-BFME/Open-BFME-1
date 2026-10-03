# RVA 002435F0: native map visibility

The bank at attempts/0x002435f0.cpp reproduced 737 bytes and 13 relocation
slots, with nine differences at +290..298: retail prepares the second key
address before storing through the first lookup result. The bank declared
lookup as an opaque external call. Previous local lifetime/order variants
were recorded without progress.

Replacing that declaration with native STLport map<int,int> makes the
737-byte caller exact modulo relocation slots. Both signed and unsigned key
experiments have the same caller shape; the independently decoded callee
uses signed comparisons, so the production source uses signed int keys.
An address-qualified comparator preserves a separate binding for this retail
copy. No volatile access, compiler barrier, assembly or codegen pragma is used.

## Boundary and identity

Ghidra creates a 737-byte function at VA 006435F0. Independent Capstone decoding
of the unpacked retail image ends in POP EBP/EBX/EDI/ESI, ADD ESP,60, RET at
RVA 002438D0 (+2E0); INT3 begins at 002438D1 (+2E1).
The source retains the bank's address-qualified Rva002435F0View::run identity.
Its formation-slot behavior does not prove an EA method name.

The receiver offsets and opaque views remain those of the bank. The body
calls the containment interface at vtable +104, visits list nodes, compares
overrides and weapon fields, computes distances and updates the index map.
No stronger semantic identity is asserted by the file or function name.

## Map lookup binding at 00226FA0

All four retail map calls route through ILT 0001F91F to 00226FA0.
Ghidra creates a 115-byte function at VA 00626FA0. Independent byte decoding
confirms signed key comparison at +17 followed by JL +1A, key at node+10,
result at node+14, two RET4 exits (+64 and +70), and INT3 from +73.
Incoming ECX is the tree receiver; the sole stack argument points to a
four-byte key. The missing-key path builds a key/value pair with zero value,
then calls ILT 0000ED2C -> 00224AD0, native tree insert_unique.

The address-qualified native operator[] emitter also measures 115 bytes,
with no non-relocation differences and one call relocation at +53. This is
independent algorithm, layout and ABI evidence for binding its entry to
00226FA0. The existing generic map<int,int> pin instead routes to 00227110;
it is deliberately not reused or changed. The comparator's address token
keeps the copies distinct. The helper's pre-existing ledger claim is not
renamed, rehomed or counted as new progress.

## Other callees

callees.py identifies the four targets (with repeated calls):

- 000022BB -> 00087A80: existing getFinalOverride@Overridable const.
- 00019736 -> 002350C0: existing Rva00233F30::rva002350c0, returning the
  established 16-byte BfmeRva44E60Record through the hidden result pointer.
- 0001F91F -> 00226FA0: the map access above.
- 00031A7F -> 001BE230: existing Object::getCurrentWeapon(WeaponSlotType *).

The bank's unused fillFormationPosition alias is removed. No callee is
assigned a guessed semantic name. The strict caller gate, including its
constant reference, is the final acceptance check.

Strict add_match verification passed 1/1 caller, its float constant and the
single DIR32 reference. Pin consistency reports no new inconsistent pins.
