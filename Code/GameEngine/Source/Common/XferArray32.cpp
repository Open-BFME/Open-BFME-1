// cl: /DNDEBUG /MD /O2
#include "System/xfer.h"

struct XferException
{
	void *text;
	int tag;
};

struct XferTriple32
{
	int a;
	int b;
	int c;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern "C" void __cdecl gen00344750(Xfer *xfer, void *target);
extern "C" void __cdecl gen000d7010(Xfer *xfer, void *target);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

extern "C" Xfer &__cdecl xferRva00347BB0(Xfer &xfer, int (&targets)[32])
{
	int remaining = 32;
	unsigned int version = remaining;
	xfer == version;
	if (version != 32)
	{
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	int *target = targets;
	do
	{
		gen00344750(&xfer, target);
		++target;
	}
	while (--remaining != 0);

	return xfer;
}

extern "C" Xfer &__cdecl xferRva00347C40(Xfer &xfer, XferTriple32 (&targets)[32])
{
	int remaining = 32;
	unsigned int version = remaining;
	xfer == version;
	if (version != 32)
	{
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
	}

	XferTriple32 *target = targets;
	do
	{
		gen000d7010(&xfer, target);
		++target;
	}
	while (--remaining != 0);

	return xfer;
}
