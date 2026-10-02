# RVA 0x00592640 constructs the +0x488 member of the AptPalantir base

Keep the opaque Rva00592640Owner identity. Older verdicts calling the
containing owner GameClient predate its independently documented identity
correction in 00431380-gameclient-vs-00597fc0-client.md. The containing class
is Rva00597FC0Client, base of AptPalantir, whose authentic spelling is unknown.
All facts below were checked against retail-1.03-unpacked lotrbfme.exe,
base 0x00400000, with pefile and capstone.

## Containment and extent

ILT RVA 0x000176A7 is an E9 to 0x00592640; its sole direct caller is
0x005980BA inside the 1953-byte constructor beginning 0x00597FC0. At
0x005980AF that body LEAs ECX,[ESI+488h], then invokes the ILT. The
matched Rva00597FC0Client destructor independently destroys +0x488.
AptPalantir's native constructor/destructor call the enclosing class at
0x00597FC0/0x00596500. This proves containment, not the contained class name.
The target ends RET at 0x00592792, then INT3 at 0x00592793: 339 bytes.

## Five DisplayString pointers, not integer handles

The target loads singleton VA 0x012F12CC five times and calls slot 9
(+0x24), saving EAX into +0x14/+0x18/+0x1C/+0x20/+0x24. Matched
WinInstanceDataDisplayStrings.cpp identifies this singleton as
TheDisplayStringManager and this slot as newDisplayString returning
DisplayString*. Slot 10 (+0x28) is freeDisplayString(DisplayString*),
as independently used by the matched owner destructor 0x005927F0.
Its old TU-local opaque integer-handle view is not authoritative for the
constructor ABI. Canonical manager types are available; do not add a new
void slot-9 declaration or infer a new manager identity from that old view.

The resource image field at +0x28 comes from an AsciiString Resource_Icon
lookup; +0x2C is zeroed. The HelpBoxText callback registration constructs a
16-byte refcounted single functor with table VA 0x0110BD00, receiver=this at
+8 and member thunk VA 0x0043524C at +0xC. That E9 reaches still-dumped
0x0058E390. Table slots resolve to single-wrapper deleting destructor
0x0058D580 and matched invocation 0x0058D210. The wrapper has no semantic
class name; existing single-binding wrappers establish the ABI family only.

No BFME string/caller identifies the contained class's authentic spelling.
The Resource_Icon/HelpBoxText strings identify behavior, not a C++ owner.
No constructor reconstruction or changes to the matched destructor's
call contracts are made here. The older bank remains unchanged.
