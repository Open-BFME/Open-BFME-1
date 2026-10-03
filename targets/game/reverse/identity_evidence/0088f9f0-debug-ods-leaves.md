# DebugIOOds inline virtual leaves

The native Zero Hour `debug/internal_io.h` defines both methods inline:
EmergencyFlush(void) and Execute(Debug&,const char*,bool,unsigned,
const char* const*), returning void. The existing debug_io_ods.cpp includes
that header through _pch.h and already emits both exact native COMDATs.
It passes its existing three strict claims before adding these two.

Retail table VA01135060 is independently installed by the matched
DebugIOOds constructor0088F990 and Create0088FA10. Slot3 is the named
Write0088F950 implementation with the same native three-argument contract.
BFME adds an is-readable boolean slot at2; accounting for that insertion,
EmergencyFlush is slot4 and Execute slot5. The two table operands are
00C8F9F0 and00C8FA00. The native sibling DebugIONet family has independently
landed EmergencyFlush at the same slot4 (0088FCD0), corroborating the
per-family alignment, rather than assuming unshifted ZH slot numbers.

Ghidra read_memory at00C8F9F0 matches all32 baseline bytes: one RET at
0088F9F0 then fifteen INT3; RET14h at0088FA00 then thirteen INT3.
The latter pops five four-byte stack arguments, exactly as the native
Execute declaration requires. Each slot is a separate positive entry
witness and its own complete body.

Historical commit934fef7c47 withdrew the free-cdecl opaque alias at
0088F9F0 pending this native method. That alias remains tombstoned. These
claims use the existing native header definitions and real method names;
there is no new standalone stub, alternate identity, source layout or pin.
