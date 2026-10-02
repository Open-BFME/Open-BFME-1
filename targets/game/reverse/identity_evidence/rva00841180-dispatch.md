# RVA00841180 virtual dispatch conversion and name pairing

Retail RVAs 0x00841180, 0x008411A0, and 0x008411C0 each have these
19 bytes, preceded and followed by INT3 padding:

    8b442404 8b08 8b5104 8d0c02 8b01 6a00 ff10 c3

Independent decoding reads the stack pointer argument into EAX, its vbtable
into ECX, vbtable[1] into EDX, and adjusted-this into ECX with LEA. It then
loads adjusted-this's vtable into EAX and calls slot zero with a zero stack
argument. RET is at +0x12. There are no direct calls or relocations.

The old bank named its unknown slot `Rva00841180Target::invoke(int)`; neither
the old source nor retail established an original method name or owner.
Its manual adjustment emitted a different SIB/load order.

Inherited virtual-destructor syntax in an address-derived virtual-base
layout exactly reproduces all 19 bytes. Independent narrow istream and
ostream probes both reproduce them too, so these bytes do not establish a
stream specialization. Separate address-derived classes keep that uncertainty.

The name-regression tokenizer pairs the removed bank's `invoke` declaration
with the unrelated new `Rva008411A0Base` destructor declaration. No established
identity was renamed: these are different declarations, and the old generic
slot method is replaced by the compiler's destructor-dispatch expression.
The correction entry covers only these exact source snapshots. It documents
this false pairing and does not authorize any future semantic rename.

Validation: each entry independently decoded from the retail executable;
three probes exact with zero relocations; scoped add_match/build verifies
3/3 entries, retaining one row and one address-derived identity per address.
