# RVA 0x00374610 is CastleMemberBehavior::onLevelStart

The 388-byte body implements public virtual
`CastleMemberBehavior::onLevelStart(Dict*)`, receiving the secondary
BehaviorModuleInterface at complete module+0x0C. It is not Object's
checkAndDetonateBoobyTrap. Constructor/table ownership and a matched BFME
caller establish the name independently of the body match.

All binary addresses were checked with pefile and capstone against the
retail-1.03-unpacked lotrbfme.exe, base 0x00400000. GhidraMCP creates a
388-byte function at VA 0x00774610 and finds the little-endian stub pointer
`11 AE 40 00` only at VA 0x010E956C.

## Named module constructor and destructor identify the table

The clean matched CastleMemberBehavior constructor at RVA 0x0036CEA0,
in CastleMemberBehaviorConstructor.cpp, first constructs its base, then
writes these final tables:

    0076CED3 mov [esi],     010E9594h
    0076CED9 mov [esi+0Ch], 010E94D0h
    0076CEE0 mov [esi+10h], 010E94BCh

The clean matched complete destructor at RVA 0x0036BBA0 writes the same
+0x0C table at VA 0x0076BBC3 (immediate starts at 0x0076BBC6).
Ghidra's independent search for `D0 94 0E 01` returns exactly the constructor
and destructor immediates. The clean matched friend_newModuleInstance at
RVA 0x00114550 calls the named constructor, and matched getModuleNameKey
at RVA 0x0036CB60 uses the literal CastleMemberBehavior. These anchors
identify the owner without naming it from a nearby CastleBehavior callee.

The +0x0C table at VA 0x010E94D0 has 41 entries. Slot 39 at VA 0x010E956C
contains ILT VA 0x0040AE11, whose E9 targets VA 0x00774610. Slot 40 routes
through ILT 0x00017521 to the three-byte default RET4 at RVA 0x0011A110.
The early table entries are inherited behavior-interface acquisition slots.
The +0x10 dispatch pointer is a separate table; do not count this method
from that pointer or misidentify its receiver as module+0x10.

## Matched Object caller names slot 39

The clean matched Object::onLevelStart(Dict*) at RVA 0x001BF0A0, in
ObjectBehaviorFanout.cpp, iterates Object's behavior modules, invokes their
onLevelStart(properties), then invokes the Drawable's own onLevelStart.
The source declares BehaviorModuleInterface::onLevelStart(Dict*) at slot 39.
Native instructions independently reproduce the dispatch:

    005BF0B5 lea ecx,[eax+0Ch]
    005BF0B8 mov eax,[ecx]
    005BF0BA push edi
    005BF0BB call [eax+9Ch]

This proves both +0x0C subobject and slot 39 spelling in BFME. Zero Hour's
behavior interface does not include this added slot, so its declaration
order alone could not establish the identity.

## BFME-specific work corroborates level-start registration

The argument is a Dict-compatible receiver: StaticNameKey::key at
RVA 0x00090290 supplies the key and the matched Dict::getAsciiString route
through ILT 0x0002FF6D writes the returned AsciiString and presence flag.
When present, the function walks TheGameLogic's object list, compares each
Object name at +0x84 against the property string, looks up CastleBehavior
using the retail literal at VA 0x01083C50, and invokes the clean matched
CastleBehavior::registerOwnedObject at RVA 0x00373220. It then stores state
4 at CastleBehavior+0x9C.

The owned Object passed to registerOwnedObject comes from incoming
interface-4, equivalent to complete module+8, corroborating the adjusted
receiver. RET4 at RVA 0x00374791 and INT3 at 0x00374794 prove the 388-byte
extent. The earlier return at 0x0037468A also pops one pointer argument.

This resolves the identity blocker. Existing history records a 384-byte
source with 106 non-relocation differences and changed register-save/null
check placement; its normalized shape is not a byte match. This proof
installs no reconstruction and does not modify or bank that unavailable
scratch source. Exact string-comparison and EH/register scheduling remain
conversion work. The EA file hint CastleSystem.cpp corroborates the castle
subsystem, but the BFME table and matched caller determine this method name.
