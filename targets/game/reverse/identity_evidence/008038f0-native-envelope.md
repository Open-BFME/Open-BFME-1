# RVA 008038F0: native envelope lifetime

The complete retail body is 123 bytes, starting at RVA 008038F0 and ending
with RET 4 at 00803968..0080396A. INT3 padding begins at 0080396B.
Ghidra was created/decompiled at VA 00C038F0; all facts below were checked
against the unpacked retail PE and its complete decoded instruction stream.

## Identity and ABI

Keep the existing address-derived `Rva008038F0Sender::send(BfmeC994 *)`
spelling already used by the neutral sender pin. No original EA class or
method name is asserted. The receiver arrives in ECX; one incoming message
pointer is read at ESP+30 after the 24-byte frame and two saved registers.
The body reads message offsets 1C, 20, 10 and 14, preserving their raw dwords.
`BfmeC994` is the existing opaque message ABI view, with only those accesses
modeled here. No shared header defining that type exists.

The sender reads its pointer at +10, adjusts the pointed-to receiver by +4,
then calls vtable slot +0C with one stack pointer to the beginning of the
local envelope. The call has no caller stack cleanup; its result is unused.
The dispatch view names slots by offset and asserts no semantic method name.
Its pointer parameter exposes the prefix; the enclosing envelope and its
trailing subobject remain alive until after the call.

## Constructor and destructor evidence

The local occupies 36 bytes: a 20-byte prefix followed by a 16-byte polymorphic
tail. Retail zeroes four prefix dwords and one byte, then calls RVA 007E86B0
with the tail address. That complete 16-byte helper returns its incoming
receiver in EAX, installs table VA 01129358, and clears receiver+4. This
independently proves the existing `Rva007E86B0Base` constructor contract.

After the constructor, the caller copies the four message dwords into the
prefix, installs tail table VA 011296B0, and clears tail+8, +C and +4. The
native derived constructor reproduces these stores without manual vptr writes.
The tail's destruction calls RVA 007E86C0, whose complete seven-byte body
restores table VA 01129358 and returns. This is the existing paired base
destructor binding; no new callee pin was added. Both pins pass individual
pin-consistency checks, and the full pin check passes.

Both retail tables have one entry followed immediately by string data.
The tail entry at VA 011296B0 points to VA 00BE8E70. Independently decoded
RVA 007E8E70 is a complete 30-byte scalar-deleting destructor: it calls
007E86C0, checks flag bit 0, optionally invokes global delete at 00881EB0,
returns its receiver and pops four argument bytes.

The native COFF table has one relocation to the compiler-generated weak
`??_E` symbol, whose auxiliary record selects the emitted `??_G` destructor.
That emitted 30-byte scalar-deleting destructor was independently compared
against retail, resolving its two REL32 operands to 007E86C0 and 00881EB0;
all 30 bytes agree. Thus the local table is supported by its actual entry,
not merely by a masked DIR32 operand. The tail is an address-derived layout
view of this lifetime; no additional constructor/destructor ledger claims
or identities are introduced.

## Byte result and controls

The served bank was 123 bytes with 15 differing bytes. It used volatile
prefix fields, a manual guard open/close pair, and an explicit vptr store.
Replacing that model with a prefix constructor, native base/derived tail
construction, and automatic destruction reproduces all 123 bytes. No volatile,
barrier, inline assembly, forced register or manual vptr write remains.
The scoped `add_match` gate verifies all three relocation operands as well
as the full body; it reports one consistent DIR32 reference and no literal
or floating-point references. Existing global bindings and baselines are unchanged.

## Narrow bank-name corrections

The removed bank's `Bfme*1250` identifiers are local experiment tags, not
ledger or pin identities: none of its six class names occurs in functions.csv
or symbols.csv. Its first-line submit name does not even name its emitted
BfmeThing1250 function. These tags contain no retail address. No established
sender or callee name is retired: the new entry uses the pre-existing neutral
sender pin and the two pre-existing native lifetime bindings.

The raw constructor/destructor bodies positively refute the bank's
`BfmeGuard1250::open/close` operation model: they are base construction and
virtual destruction, not an independent guard API. The name checker pairs
that one removed class with both the genuine base declaration and its new
derived tail; this is a type split, not two new names for one retail body.
The prefix and envelope remain explicit layout views of the observed stack
storage. The +4 field is a polymorphic receiver, not an apply operation.
The function at its slot +0C has no name witness, so the new declaration
names only its slot. Exact-snapshot corrections cover these unpinned bank
identifiers and keep all production binding identities intact.
