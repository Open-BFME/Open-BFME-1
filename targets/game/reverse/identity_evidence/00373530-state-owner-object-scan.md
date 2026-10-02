# RVA 0x00373530: state-owner object scan

The body is reached only through ILT 0x00040629; the sole call is 0x00377812
in existing matched state-update body 0x00377740. That call pushes zero at
0x0037780D and forms ECX = ESI - 0x10 at 0x0037780F. It therefore operates
on the enclosing owner of the caller's +0x10 state interface, not the interface.

Retail constructor-shaped body 0x00376250 installs table VA 0x010E9B28 at
receiver +0x10 (immediate at 0x00376298); slot zero routes through ILT
0x0001B7AC to the caller. These native routes establish an address-qualified
owner association. Existing sources identify this family as CastleBehavior;
the prior 00377060.md evidence documents a neighbouring method's native
Castle ... Packed(aka:DIE) trace. This note leaves the current member spelling
unresolved and does not infer it from those source labels.

The candidate reads the owner's object at +8, iterates ObjectIDs in the
+0xC4/+0xC8 range, performs inline GameLogic hash lookup and queries nearby
objects with filters. In particular, its native stack-local vptr immediate at
0x0037367E is VA 0x01083B80; the old attempt's VA 0x01085DC0 is not that
retail value. No corrected C++ body or new type/field spelling is claimed.

Native last RET 4 is 0x003739F2 followed by INT3 0x003739F5, establishing
1221 bytes. Route census, constructor operand, receiver subtraction, filter
immediate and complete extent were cross-checked against retail-1.03-unpacked
lotrbfme.exe using pefile/Capstone. Existing banks and production are unchanged.
