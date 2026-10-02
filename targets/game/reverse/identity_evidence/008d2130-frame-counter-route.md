# RVA 0x008D2130: frame-counter update route, names unresolved

This 393-byte body has nine native direct callers and no stored entry pointer.
The old audit considered only two placeholder wrappers; the current census
also finds 0x008AE419, 0x008C5712, 0x008C5742, 0x008C5ADC, 0x008CA8F0,
0x008CADA2 and 0x008D2889, as well as 0x008ACF6F/0x008ACF9F.

The matched callback at 0x008C5700 reads receiver+0x50, loads its +0x18
counter, increments it at 0x008C570E and passes it to the candidate at
0x008C5712. The counterpart at 0x008C5730 decrements that same counter at
0x008C573E and calls at 0x008C5742. Both clear flag 0x02000000 at the
receiver+0x50 record's +0x1C after returning.

Another caller is within matched address-qualified interpreter handler
0x008CAC20. The dispatch table at RVA 0x00ED5A68 has index 0x9F's entry at
RVA 0x00ED5CE4 (VA 0x012D5CE4), containing VA 0x00CCAC20. This handler
pushes its computed frame at 0x008CAD9F, sets ECX=EDI, and calls the candidate
at 0x008CADA2 before changing the same 0x02000000 flag. Native dispatcher
placement plus these independent increment/decrement callers establish the
frame-counter role; they do not recover an original C++ class/member spelling.

The body bounds-checks its one int argument, skips the current value, takes
a fast path for current+1, and otherwise rebuilds state before advancing to
the requested value. At 0x008D2288 it calls helper 0x008BDE60 with ECX=EDI
and three pushed pointers (0x008D2280/81/82). That helper's original receiver
and method identity remain unknown. Competing CBC/CBD reconstruction pins
are not evidence of two identities for this one body and are not changed here.

RET 4 at 0x008D22B6 and INT3 at 0x008D22B9 delimit exactly 393 bytes.
Routes, dispatch pointer and complete instructions were cross-checked against
retail-1.03-unpacked lotrbfme.exe with pefile/Capstone. No source, pin or
production ledger identity is changed; no conversion is claimed.
