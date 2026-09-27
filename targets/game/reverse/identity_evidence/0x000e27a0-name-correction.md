# PlayerTemplate destructor layout names

The `PlayerTemplate` destructor at RVA `0xE27A0` has eight exact caller sites and an ILT pin at `0x181CE`. Its retail body spans 702 bytes and ends at `ret +0x2BD`.

The old bank used nine local type names for layout views. `callees.py 0xE27A0 702` resolves string cleanup to the retail `StringBase@D` and `StringBase@G` helpers. It resolves the calls at ILTs `0x32B5`, `0x32227`, and `0x2AC20` to function bodies without named classes. ILT `0x26AB2` has many competing destructor names. These calls prove the targets and cleanup behavior, but they do not prove the local names `BFMERetailAsciiString`, `BfmeStringBase`, or `BfmeMap*`.

The three sound slots decrement a pointer field and call through its vtable when the count reaches zero. The body does not identify the pointed-to class as a sound object. The 12-byte field at `+0x28` contains three floats, but no symbol names it `BfmeRGBColor`.

`name_oracle.py` reports no BFME witness for `PlayerTemplate+0x60`, `+0x6C`, `+0x80`, `+0x98`, `+0xE8`, `+0xF4`, `+0x100`, `+0x104`, or `+0x108`. Its Zero Hour hints at `+0x98` and `+0xE8` do not establish BFME identities. The oracle confirms `m_intrinsicSciences` at `+0x8C` with confidence 1.00.

The bank now names the unproved helpers with the destructor RVA and field offsets. Those names describe local layout views. They do not claim that retail has classes named `Rva000E27A0Object060` or `Rva000E27A0SoundRef`.
