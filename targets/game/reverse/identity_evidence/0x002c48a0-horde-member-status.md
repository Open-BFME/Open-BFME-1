# Shared horde-member slot at 0x002C48A0

The 83-byte retail function at 0x002C48A0 ends with `ret 8`: it is a
`__thiscall` member with two explicit four-byte arguments. Its sole direct
call at +0x3C goes through ILT 0x000307E7 to the matched 0x001C7370 body,
`Object::setStatus(const BitFlags<86>&, bool)`. The retail code passes true
and builds a three-word mask with `0x20` in its middle word: bit 37. The
retail ObjectStatus name table and matched `ObjectRva001CFF30.cpp` identify
bit 37 as `OBJECT_STATUS_HORDE_MEMBER`.

The entry is in slot 12 (+0x30) of vtables 0x010C8240 and 0x010C8638.
Constructors 0x002C43A0 and 0x002C4A70 install these tables, respectively;
their independently matched identities are `HordeAIUpdate` and
`HordeWorkerAIUpdate`. Both tables use ILT 0x00028A0B at this slot. This
proves a shared virtual slot but does not establish its declaring class or
source method name. The replacement therefore keeps `Rva002C48A0` in its
owner name and uses a method name that describes the observed bit operation.

The body reads an Object pointer at `this - 0x338`, then its containment
module at Object+0x1FC. It calls containment slot +0x68 and returns false if
that yields null. Otherwise it marks the first explicit Object argument as a
horde member, passes that Object to the returned interface's slot +0x20, and
returns false. The second explicit argument is not read. The scope of the
method and the meanings of the two virtual calls remain unproven.

The clean C++ probe with `_STL::bitset<86>::_Unchecked_set(37)` matched all
83 bytes modulo relocations. The strict scoped gate must also confirm the
physical call target; a masked probe alone does not establish it.
