// cl: /DNDEBUG /MD /O2
#include "System/xfer.h"

struct XferException
{
	void *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
// 0x0010C100 is the 25-byte virtual-slot-0x90 forwarder (ledger:
// ?Rva0010C100@@YAXPAVMidVirtualSlot90Receiver@@PAX@Z); the receiver type is
// spelled the way the other forwarder callers spell it.
class MidVirtualSlot90Receiver
{
};
void __cdecl Rva0010C100(MidVirtualSlot90Receiver *receiver, void *target);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

extern "C" Xfer &__cdecl xferGuardTargetTypes(Xfer &xfer, int (&targets)[2])
{
	int remaining = 2;
	unsigned int version = remaining;
	xfer == version;
	if (version != 2)
	{
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	int *target = targets;
	do
	{
		Rva0010C100(reinterpret_cast<MidVirtualSlot90Receiver *>(&xfer), target);
		++target;
	}
	while (--remaining != 0);

	return xfer;
}
