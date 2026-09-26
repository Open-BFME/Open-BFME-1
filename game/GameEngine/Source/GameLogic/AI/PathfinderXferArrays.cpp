// cl: /DNDEBUG /MD /O2
#include "../../Common/System/xfer.h"

struct XferException
{
	void *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
void __cdecl bfmeCalcTGC(void *xfer, int *target);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

extern "C" Xfer &__cdecl xferRva003D6CB0(Xfer &xfer, int (&targets)[512])
{
	int remaining = 512;
	unsigned int version = remaining;
	xfer == version;
	if (version != 512)
	{
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	int *target = targets;
	do
	{
		bfmeCalcTGC(&xfer, target);
		++target;
	}
	while (--remaining != 0);

	return xfer;
}

extern "C" Xfer &__cdecl xferRva003D6D40(Xfer &xfer, float (&targets)[64])
{
	int remaining = 64;
	unsigned int version = remaining;
	xfer == version;
	if (version != 64)
	{
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	float *target = targets;
	do
	{
		xfer == *target;
		++target;
	}
	while (--remaining != 0);

	return xfer;
}
