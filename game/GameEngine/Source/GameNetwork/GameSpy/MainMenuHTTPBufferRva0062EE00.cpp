// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0062EE00: retain a completed HTTP buffer and resume online startup.
#include <string.h>
void *__cdecl operator new[](size_t);
void __cdecl operator delete[](void *);

typedef int GHTTPRequest;
typedef int GHTTPResult;
enum GHTTPBool { GHTTPFalse = 0, GHTTPTrue = 1 };
extern int timeThroughOnline;
extern int checksLeftBeforeOnline;
extern char *MOTDBuffer;
volatile unsigned char g_rva012F7178PatchCheckLayoutActive = 0;
void Rva004C5490();
// Defined by the matched retail body at 0x0062EA60 (Rva0062EA60StartOnline.cpp).
extern void Rva0062EA60StartOnline();

GHTTPBool rva0062EE00MainMenuOnlineCallback(GHTTPRequest request, GHTTPResult result,
	char *buffer, __int64 bufferLen, void *param)
{
	if ((int)param != timeThroughOnline)
		return GHTTPTrue;
	if (MOTDBuffer) {
		delete[] MOTDBuffer;
		MOTDBuffer = 0;
	}
	if (buffer && bufferLen > 0) {
		char *copy = new char[(unsigned int)bufferLen];
		memcpy(copy, buffer, (unsigned int)bufferLen);
		MOTDBuffer = copy;
		copy[bufferLen - 1] = 0;
	}
	--checksLeftBeforeOnline;
	if (g_rva012F7178PatchCheckLayoutActive && !checksLeftBeforeOnline) {
		Rva004C5490();
		g_rva012F7178PatchCheckLayoutActive = false;
	}
	if (!checksLeftBeforeOnline)
		Rva0062EA60StartOnline();
	return GHTTPTrue;
}
