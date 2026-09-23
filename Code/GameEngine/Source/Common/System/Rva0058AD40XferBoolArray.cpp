// cl: /DNDEBUG /MD /O2
// Calls through Xfer slots 29 and 35 match operator==(unsigned int&) and
// operator==(bool&), then the function transfers twelve booleans. Its name
// keeps RVA 0x0058AD40 because the body has no proven semantic owner.
#include "xfer.h"

struct XferException
{
	void *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

Xfer &__cdecl xferBoolArray12Rva0058AD40(Xfer &xfer, bool *values)
{
	unsigned int version = 12;
	xfer == version;
	if (version != 12)
	{
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
	}

	unsigned int index = 0;
	do
	{
		xfer == values[index];
		++index;
	}
	while (index < 12);

	return xfer;
}
