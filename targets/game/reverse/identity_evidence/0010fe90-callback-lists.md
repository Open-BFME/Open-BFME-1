# RVA 0x0010FE90: callback list insertion

Replace the lifted claim
`?parsePreferredAgainst@WeaponTemplateSet@@CAXPAVINI@@PAX1PBX@Z`
with `?rva0010fe90@Rva00110790Receiver@@QAEXPAX0@Z`.

The matched callback `rva00110790Forward` at 0x00110790 loads its second
argument into ECX and pushes its third and first arguments before calling
ILT 0x0001F546, which jumps to 0x0010FE90. The target uses ECX as its
receiver, reads two stack arguments, and returns with `ret 8`. This
contradicts the old static four-argument INI parser identity and supports
the existing address-derived receiver declaration and symbol pin. The
owner's semantic class remains unknown.

The target spans 204 bytes: both exits use `ret 8`, the last at +0xC9,
followed by INT3 padding. It calls the item's virtual slot +8 for a name,
compares the literal strings `Object` and `Weapon`, and inserts into list
members at receiver offsets +0x48 and +0x4C.

The Object branch calls the already matched 47-byte
`_STL::list<Rva0010EBE0Element>::push_front` through ILT 0x0003F13E
(body 0x0010EBE0), passing the original item argument's address. It then
calls `Rva0010ECA0List::push_back` through ILT 0x000303D7 (53-byte body
0x0010ECA0) with the item/value pair. The fallback inlines both insertions
and calls `_STL::__node_alloc<true,0>::_M_allocate` at 0x0082E540 for
12-byte and 16-byte nodes. The Weapon branch returns without insertion.

The reconstruction includes native STLport list operations. Keeping the
actual push_front definition visible and noinline removes the bank's
extra argument-home store; a declaration-only alias instead spills the
item. The helper independently reproduces all 47 bytes, including its
allocator relocation. Only the 204-byte caller is new C++ progress.
