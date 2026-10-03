# Two complete fixed-member forwarding bodies

Both entries are11B ADD ECX,imm32; E9, followed by five INT3 bytes.
Retail PE and Ghidra memory agree. Existing generated rows00516A36 and
0075BF26 cover only the final E9 instructions and have no independent
Ghidra references. The tables and ILT routes enter their six-byte prefixes.
Retire those two interior rows with tombstones, preserving generated source.

| Entry | Positive entry route | Independent table installation | Callee |
| --- | --- | --- | --- |
| 00516A30 | VA01105A78 slot12 -> VA0044480F -> VA00916A30 | ctor00519F90 at00519FE1; dtor005199A0 at005199BF | this+25C -> ILT282A9 ->00527050 |
| 0075BF20 | VA01122470 slot25 -> VA004090C5 -> VA00B5BF20 | ctor00751CF0 at00751D18; teardown00751E80 at entry | this+178 -> ILT4A8A9 ->00458310 |

00516A30 retains the existing MpGameSetup::GadgetInit binding. Its complete
176-byte native provider uses ECX, consumes no explicit stack arguments,
and ends plain RET005270FF. The owning constructor independently takes
receiver+25C at00519FD6 for member construction; teardown also accesses
that same member. There is no covering MpGameSetup header, so only its
existing method declaration is repeated. No new owner or wrapper semantic
identity is inferred from the callee or surrounding old names.

0075BF20 adopts the canonical GameClient/RadiusDecal.h declaration.
The complete34-byte00458310 provider clears receiver+0, conditionally calls
the shadow at+4 through virtual+8, clears+4, sets byte+8 and ends plain
RET00458331. Its no-argument void-thiscall ABI agrees with the header.
Several independently installed drawing tables share the same wrapper,
but no containing owner-name claim is made. Both new wrappers remain
fully address-qualified and no shared header/pin is modified.

callees.py was run for both complete11B extents; its E8-only output omits
the independently decoded E9 routes. Both probes match and the production
native gates resolve the existing callee targets.
