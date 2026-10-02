# RVA 0x001CEE10 is Object::loadPostProcess

The 336-byte body at RVA 0x001CEE10 is Object's protected Snapshot override
`?loadPostProcess@Object@@MAEXXZ`. Its incoming receiver is the Snapshot
subobject at complete Object+0x60. This establishes identity, not a C++
byte conversion.

All binary addresses below were checked against
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, image base
0x00400000, with pefile and capstone. GhidraMCP independently finds
`1B D5 41 00` at VA 0x0109EE48, reads the same four table pointers at
VA 0x0109EE44, and creates a 336-byte function at VA 0x005CEE10.

## Native Object owner, rather than a guessed adjusted receiver

The Object constructor at RVA 0x001D29A0 stores these tables (instructions
decoded from the proven function start, not from an arbitrary byte offset):

    005D2A1E  mov dword ptr [esi],       0109EE58h
    005D2A24  mov dword ptr [esi+60h],   0109EE44h
    005D2A2B  mov dword ptr [esi+64h],   0109EE28h
    005D2A32  mov dword ptr [esi+6Ch],   0109EE00h

The clean, matched Object destructor at RVA 0x001D4010 independently writes
the same +0x60 table. Its Snapshot table at VA 0x0109EE44 contains:

| Slot | Stub RVA | Body RVA | Native evidence |
|---|---|---|---|
| 0 | 0x00031E1C | 0x001D3F40 | `sub ecx,60h; jmp` through ILT 0x00046F33 to matched Object scalar deleting destructor 0x001D5CF0 |
| **1** | **0x0001D51B** | **0x001CEE10** | **This body** |
| 2 | 0x00005B00 | 0x001D3E60 | Returns VA 0x010838C0, the retail literal `Object` |
| 3 | 0x000441C5 | 0x001D48A0 | Long snapshot-transfer body, still generated |

The class-name literal identifies the owner independently of a destructor
label; the constructor, clean destructor and -0x60 adjustor corroborate it.
ILT 0x0001D51B is an E9 to VA 0x005CEE10. Its pointer occurs only at table
slot 1, VA 0x0109EE48.

## BFME Snapshot slot 1 is loadPostProcess

The independently matched BFME loadPostProcess methods for ObjectModule,
ObjectTypes, GhostObject, W3DGhostObject and W3DRenderObjectSnapshot occupy
slot 1 of their own Snapshot tables. See the tracked proofs
`00113d20.md`, `001dc240.md`, `001b3dd0.md` and `006bc8b0.md` in this directory.
The independently named W3DRenderObjectSnapshot table likewise has its
class-name literal getter at slot 2 and xfer at slot 3.

Zero Hour's Object declaration explicitly overrides protected
loadPostProcess, and its body resolves the saved contained-by object ID
through TheGameLogic::findObjectByID or clears the pointer. BFME's first
block does that same operation: Snapshot receiver+0x1B8 is complete
Object+0x218; its resolved pointer is stored at receiver+0x1B4, complete
Object+0x214. The lookup goes through ILT 0x0001F253 to the matched
GameLogic::findObjectByID at RVA 0x0009A510. This distinctive source twin
supports the slot-derived identity without inventing an offset name.

## BFME post-load work and exact extent

After resolving the contained-by ID, BFME drains saved string/slot records,
resolves their values via a virtual lookup, and restores per-object entries.
It calls Object::rva001CE530 after subtracting 0x60 from the receiver. It
passes complete Object to the matched WeaponSet::updateWeaponSet while the
WeaponSet address is Snapshot receiver+0x204, complete Object+0x264.
Pathfinder maintenance and addObjectToPathfindMap likewise receive complete
Object after that same subtraction.

RET at RVA 0x001CEF5F and INT3 at 0x001CEF60 prove the 336-byte, no-stack-arg
extent. EBP is a saved general register holding the adjusted receiver, not
an ordinary EBP exception-frame base. The body uses compiler-generated
exception cleanup for its AsciiString/list work. Exact field, iterator and
EH code generation still need recovery; the previous identity/owner blocker
is resolved. Do not convert this as an ordinary unadjusted Object receiver
or infer that its anonymous transfer-table neighbour has already matched.
