# RVA 0x00238D10: member-goal helper route, names unresolved

The body has one ILT route (0x000263F0) and one native caller at 0x00244450,
inside body 0x002440E0. The caller pushes seven words at 0x00244430, 0x00244435,
0x0024443D, 0x00244442, 0x00244443, 0x00244448 and 0x00244449. Before calling
it adjusts ECX by -0xE4 at 0x0024444A. The callee immediately uses its first
stack word as an Object-like receiver and overwrites ECX; the caller's ECX
adjustment alone cannot establish whether the original helper was a member
with unused this or another calling convention.

The caller itself is reached through ILT 0x0002BE6D. Two retail table entries,
VA 0x010AEE74 and VA 0x010B08FC, contain that stub's VA 0x0042BE6D. Both
have the same neighbouring sequence: 0x00243EA0, 0x0023D850, 0x00244080,
this caller, 0x00243990, 0x002439F0 and 0x00243C40. Existing matched sources
for these neighbours retain address-qualified owners and describe member-goal
refresh/target/list operations. Those reconstruction labels suggest contain
context but do not independently prove an authentic class or helper spelling.
Ghidra get_xrefs_to finds no references because this project is not auto-analysed;
the direct retail pointer census and E8/E9 decode establish these routes.

The candidate calls native Pathfinder geometry routines, selects an object's
current weapon, and tests goal attack range. Its last RET 0x1C is at
0x002393CB, with INT3 at 0x002393CE: 1726 bytes. The sole caller's seven pushes
corroborate that cleanup. These routes and full instruction boundaries were
checked against retail-1.03-unpacked lotrbfme.exe with pefile/Capstone.

No original owner/member name, pin, conversion or new layout is asserted.
Existing nonmatching reconstruction evidence is preserved.
