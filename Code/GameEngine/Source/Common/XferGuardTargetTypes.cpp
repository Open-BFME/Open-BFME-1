// cl: /DNDEBUG /MD /O2
#include "System/xfer.h"

struct XferException
{
	void *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern "C" void __cdecl bfmeXferGuardTargetType(Xfer *xfer, void *target);
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
		bfmeXferGuardTargetType(&xfer, target);
		++target;
	}
	while (--remaining != 0);

	return xfer;
}
