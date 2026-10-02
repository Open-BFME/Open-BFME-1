# RVA 0x0058E390 is the HelpBoxText Apt callback of Rva00592640Owner

BFME callback registration proves the logical selector and bound receiver.
Its authentic C++ class/method spelling remains unknown. This is evidence
only, not a 1810-byte conversion. Addresses were checked against
retail-1.03-unpacked lotrbfme.exe (base 0x00400000) with pefile and capstone.

## Native capture, selector and invocation route

The 339-byte constructor 0x00592640 pushes literal HelpBoxText at
0x005926FF, constructs the selector string, and at 0x0059271E loads
member code VA 0x0043524C into EDI. ILT 0x0003524C reaches 0x0058E390.
It allocates a 16-byte refcounted wrapper, installs table VA 0x0110BD00
at 0x00592732, writes its own receiver ESI at wrapper+8 (0x00592738),
and writes code EDI at wrapper+0xC (0x0059273B). It registers the selector
and holder through the matched registerAptCallback route at 0x00592757.
The unique immediate reference to the target ILT is this capture.

Table slot 1 resolves ILT 0x0001F613 -> matched 0x0058D210. The native
invoker is MOV EAX,ECX; MOV ECX,[EAX+8]; JMP [EAX+0Ch]. It forwards the
existing stack arguments and swaps to the captured receiver without an
adjustment. It does not prove a zero-argument callback: its generic matched
TU's void(void) pointer-to-member shape was sufficient for those eight
instruction bytes but cannot override the target's actual RET 16 contract.

The target preserves that receiver in ESI and uses the five DisplayString*
fields +0x14 through +0x24 proven by the constructor/destructor and matched
DisplayStringManager slot9/10 methods. It also reads the resource Image*
at +0x28 and state bytes zeroed by the same constructor. The owner is the
member of Rva00597FC0Client at +0x488, not the real GameClient; see the
00592640-palantir-base-member and existing enclosing-owner identity proofs.

## Stack contract and extent

The target establishes EBP, aligns ESP to eight bytes and maintains an SEH
UnicodeString lifetime. It reads the original arguments at [EBP+8] and
[EBP+0Ch] as coordinate data; other argument types remain opaque. The native
return paths use RET 16, proving four stack words forwarded by the invoker.
Fourteen imported floor calls and text/image virtual calls explain drawing
behavior, but behavior alone does not prove an authentic method spelling.
Final RET 16 at 0x0058EA9F ends at 0x0058EAA2; INT3 begins there, confirming
1810 bytes. No new helper pin, typed callback binding, ledger row or source
body is introduced. The old no-owner/no-registration rationale is superseded;
concrete widget contracts and authentic C++ spelling remain outstanding.
