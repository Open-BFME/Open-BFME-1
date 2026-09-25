# RVA 0x002D53F0: Object module dispatch

The 133-byte retail body ends at 0x002D5475 with a plain RET. The original receiver identity is unknown; `Rva002D53F0::dispatch` preserves that uncertainty and address. The receiver stores an Object pointer eight bytes before its incoming subobject address; retail dereferences `[ecx-8]`, rather than subtracting eight from Object itself.

The canonical Object layout witnesses its behavior list at +0x1F0, model-condition flags at +0x110 (40 bytes), optional AI interface at +0x204, and ID at +0x74. Each behavior contributes an interface subobject at +0x0C. Its virtual slot +0x08 returns another interface; that interface's slot +0x08 returns a bool (retail tests AL), and slot +0xE8 takes one integer. These interfaces remain address-qualified; their broader identities are not asserted.

The condition word at +0x12C and mask 0x10000000 identify bit 252 in the 320-bit model-condition field. The canonical STLport unchecked bitset access pattern already used by `ObjectSMCHelperSetModelConditionState.cpp` reproduces the register-held mask and all 133 bytes. A manual word/mask implementation emitted 132 bytes with 82 differing non-relocation bytes; no ABI or behavior change was needed for this lever.

Both direct callees were decoded in full independently: ILT 0x2191D reaches Object::notifyModelConditionChanged at 0x1BE1C0 (46 bytes; Drawable notification and optional AI tail dispatch), and ILT 0xDE9F reaches Object::getProjectileUpdateInterface at 0x1BF630 (45 bytes; behavior slot +0x94 lookup). Their existing typed symbols resolve the scoped gate without new pins. The final returned interface is invoked at slot +0x08 with Object's ID; this body's return value is unused and not assigned semantic meaning.

Validation: `tools/probe.py` reports exact 133-byte instruction shape; `tools/add_match.py --replace-rva 0x002D53F0` verifies 1/1 including both REL32 operands. The original ASM dump is retained untouched. This replaces 133 ASM-only bytes with maintainable C++ and does not change boundaries or total exact coverage.
