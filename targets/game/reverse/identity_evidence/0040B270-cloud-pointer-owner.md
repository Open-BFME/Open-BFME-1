# CloudBreakEffect: scalar system-pointer owner

The existing `?TheCloudSystem@@3PAVCloudSystem@@A` DIR32 record names
VA 0x012F10F0. No source defined it and no data row owned that cell.
The matched 82-byte parser at RVA 0x0040B270 reads the pointer and dispatches
slot 9 when it is nonnull. GameClient initialization at 0x0042F5A0 stores
the niladic cloud-break factory result in the same cell and calls inherited
subsystem initialization. Its matched destructor at 0x00431380 deletes
and clears the same pointer. These independent consumers establish a
four-byte pointer cell, rather than a CloudBreakEffect settings object.

Define only this scalar as `CloudSystem *TheCloudSystem = 0` in its existing
parser unit. The native `add_data_match.py` admission proves the compiler's
four-byte size and the retail cell's four zero bytes and adds its sole data
row. The address is in the PE .data section's virtual zero-filled tail:
reading the file at a naively translated offset instead reaches bytes of
the following section. The native image reader accounts for virtual data.
The initializer is a scalar null and emits no constructor or CRT initializer.

Prior attempts deferred the adjacent saved/active settings because their
AsciiString initialization and destruction were unproven. Those records at
VA 0x012F10F4 and 0x012F10F8 remain external and unresolved. This repair does
not infer raw storage or lifetimes for either object.

Donor review: BFME 2 reference f6c3838e7b, source
`Code/GameEngine/Source/GameClient/GameClientDrawableTOC.cpp`, uses a
`CloudBreakEffectManager *TheCloudBreakEffectManager` factory result and
the same subsystem operations. That is a lead, not a BFME 1 class/name or
provider proof. Its different global spelling is not adopted; BFME 1's
existing recorded pointer name and addresses are retained.

An isolated object comparison preserves all 82 parser bytes and all its
relocations. The native paired parser/initializer gate passes 2/2 functions,
three data rows, all twenty string references and 78 DIR32 references.
The declared-unmatched check finds no remaining body in the parser unit.
The before census preview at 2026-11-14 12:41 / 1a248a7b47 has three missing
globals and LINKED 0 bytes. Additional linked bytes, a complete link,
runtime behavior and crash/memory improvements require separate proof.
The staged native preview is UNKNOWN after its 45-second deadline; it
does not establish a new linked-byte figure or a complete unit link.
