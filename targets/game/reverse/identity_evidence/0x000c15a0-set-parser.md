# 0x000C15A0: vector-to-set INI callback

The retail body is 227 bytes, ending in `ret` at +0xE2. Its first direct call
at +0x37 reaches `INI::parseAsciiStringVector` at 0x008542B0. That remains a
callee in the new C++ source; it is not the identity of this callback. The
old partial bank declared and called the same parser, but its exported
`parseAttributeModifierAura` owner and helper ABI were conjectures. The
banked source is preserved in `targets/game/reverse/attempt_history/0x000c15a0/`.

The retail body then allocates a 20-byte STLport tree header through the
allocator entry at 0x0082E540, inserts vector values through
ILT 0x00019C45 into the verified `__copy` at 0x000C11D0, exchanges two
words at `instance+8` and `instance+12`, and calls the set and vector
destructors through ILTs 0x000235E7 and 0x00026AB2. The native
vector-to-set-and-swap C++ emits exactly 227 bytes with all nine relocation
slots aligned. No named caller establishes a semantic owner or field name,
so the callback keeps its address in `Rva000C15A0ParseAsciiSet`.

`name_regression.py` aligned the old bank's *callee* identifier
`parseAsciiStringVector` to the new source's *callback* identifier
`Rva000C15A0ParseAsciiSet`. Those refer to distinct physical bodies, and
the callee declaration and call remain unchanged. The matching correction
record in `targets/game/reverse/name_corrections.json` applies only to these two exact
source snapshots; it does not permit renaming the parser itself.

The source includes STLport containers before the vendored `Common/INI.h`.
That header already declares `INI::parseAsciiStringVector`; including it
after the containers preserves retail's node-allocator call, while including
it first switches the emitted call to a distinct global `operator new`.
No production header declaration or alias pin is needed.
