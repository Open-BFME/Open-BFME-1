# Complete opaque GiantBird contact/movement draft

Retail 0x002C38B0 has RET4 at 0x002C3AD4 and 0x002C3AEF; complete
extent ends 0x002C3AF2 (578 bytes). Ghidra and independent Capstone decode
agree. The complete NUL-terminated filename at VA0x010C7710 is
F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp.
This locates the implementation family but does not prove a declaring class
or EA method spelling, so owner and method remain address-qualified.

Parent+0x1C points to the state machine; its +0x10 is native Object. Native
Object+0x204 supplies AI. Model-condition bit145 lives at Object+0x120,
mask0x20000; the draft uses canonical BitFlags<320> with the native Object
header rather than substituting its storage. It clears the bit before lookup,
then conditionally sets it near the target, notifying through ILT2191D.

Native contact-point calls and their ABIs come from callees.py and the
matched declarations at 272800 and1C3160. Random fallback calls96CF0 with
0,12345678,full filename,line623; the apparent Ghidra LAB_00bc614e is the
integer maximum12345678. A preceding push0 belongs to the subsequent
contact call, not to the random call. Goal setup2BC260 and StateMachine
setGoalPositionA0880 are now real matched source, resolving the old dump
dependency observation. All seven ILT names come from callees.py.

The two lengths compare against AI+470 times4 and times8, with a separate
10-unit stale-goal test. Read retail floats at VA1075340=4,1075C74=10,
10C7448=8 directly. Optional terrain adjustment uses AI+1CC data+44 and
TerrainLogic slot18. Both flag-controlled goal descriptors at VA12F02D4
and12F02DC are retained as opaque address-named externs; they are in BSS
and require independently justified pins before any strict landing.

The full draft is evidence only. It preserves native Coord3D operations,
all early returns and both final goal calls. No generated source or ledger
identity changed.

Measured best:568 versus578 bytes,356 non-relocation differences, first+56,
shape0.902,quality0.3495. Native BitFlags restores the full initial test/clear/
notify sequence. Embedding random generation inside the contact-call argument
restores the pre-pushed false argument, improving374 to356 differences.
Both coordinate declaration orders retain wrong contact stack offset (+28
instead of+1C in the four-save frame). Remaining blockers are coordinate
lifetimes/copies and x87 scheduling, plus final BSS descriptor pin evidence.
No inline assembly or invented behavioral helper was used.
