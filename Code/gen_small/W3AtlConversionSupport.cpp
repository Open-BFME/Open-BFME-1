// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the three support bodies the ANSI/wide conversion macros in this
// binary share.
//
// 0x0005B820 is the one-shot platform choice for "which code page does a
// conversion use". It fills a 0x94-byte OSVERSIONINFOA -- that size is what
// fixes the struct as OSVERSIONINFOA and not the EX form -- tests
// dwPlatformId == 2 and dwMajorVersion >= 5, and InterlockedExchanges one of two
// getters into the slot at [0x012A64C0] before tailing into whatever it just
// stored. The two candidates are ILT thunks: 0x00402C34 reaches the six-byte
// constant getter at 0x0005B810 (NT5 and later), 0x0041B770 reaches the
// locale-text parser at 0x0005B7A0 in W3AtlStringConversion.cpp. Same
// self-patching idiom as the wide-API thunks in
// Code/GameEngine/Source/Common/T3Win9xWideApiThunks.cpp, minus the arguments.
//
// 0x0005B8E0 is the out-of-line copy of the wide-to-ANSI conversion helper. Its
// `ret 0x10` and the pushes at its call sites give four arguments, and the
// order is read straight off the WideCharToMultiByte pushes: destination,
// source, destination length, code page. It guards BOTH pointers, stores a
// terminator into the destination before converting, and finishes with
// `neg / sbb / and` -- the branchless `converted ? destination : NULL`. Every
// W9x fallback shim inlines this same body, so those live in a different
// translation unit; this copy is the one some caller took out of line.
//
// 0x0005BA60 turns the last Win32 error into an HRESULT and hands it to the
// throw helper. `test eax,eax / jle` over the OR of 0x80070000 is exactly the
// HRESULT_FROM_WIN32 macro, whose negative-passthrough arm is why the mask and
// the OR sit inside a branch instead of running unconditionally.
//
// Identity is address-derived.

typedef unsigned short WCHAR;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef int BOOL;
typedef long LONG;
typedef long HRESULT;

typedef UINT (__stdcall *W3AtlAcpProc)(void);

struct W3OsVersionInfoA
{
	DWORD dwOSVersionInfoSize;
	DWORD dwMajorVersion;
	DWORD dwMinorVersion;
	DWORD dwBuildNumber;
	DWORD dwPlatformId;
	char szCSDVersion[128];
};

extern "C"
{
	__declspec(dllimport) BOOL __stdcall GetVersionExA(W3OsVersionInfoA *info);
	__declspec(dllimport) LONG __stdcall InterlockedExchange(LONG *target, LONG value);
	__declspec(dllimport) DWORD __stdcall GetLastError(void);
	__declspec(dllimport) int __stdcall WideCharToMultiByte(UINT codePage, DWORD flags,
		const WCHAR *wideCharStr, int wideCharCount,
		char *multiByteStr, int multiByteCount,
		const char *defaultChar, int *usedDefaultChar);
	__declspec(dllimport) int __stdcall MultiByteToWideChar(UINT codePage, DWORD flags,
		const char *multiByteStr, int multiByteCount,
		WCHAR *wideCharStr, int wideCharCount);

	UINT __stdcall W3AtlThreadAcp(void);							///< ILT 0x00402C34 -> 0x0005B810
	UINT __stdcall W3AtlParseLocaleAcp(void);						///< ILT 0x0041B770 -> 0x0005B7A0

	__declspec(noreturn) void __stdcall W3AtlThrow(HRESULT hr);
}

extern W3AtlAcpProc g_pfnGetConversionAcp;							///< retail [0x012A64C0]

// ?Rva0005B820GetConversionCodePage@@YGIXZ
UINT __stdcall Rva0005B820GetConversionCodePage(void)
{
	W3OsVersionInfoA info;
	W3AtlAcpProc chosen;

	info.dwOSVersionInfoSize = sizeof(info);
	GetVersionExA(&info);

	if (info.dwPlatformId == 2 && info.dwMajorVersion >= 5)
	{
		chosen = W3AtlThreadAcp;
	}
	else
	{
		chosen = W3AtlParseLocaleAcp;
	}

	InterlockedExchange((LONG *)&g_pfnGetConversionAcp, (LONG)chosen);
	return g_pfnGetConversionAcp();
}

// ?Rva0005B880GetConversionAcpThunk@@YGIXZ
UINT __stdcall Rva0005B880GetConversionAcpThunk(void)
{
	return g_pfnGetConversionAcp();
}

// ?Rva0005B890AnsiToWide@@YGPAGPAGPBDHI@Z
WCHAR *__stdcall Rva0005B890AnsiToWide(WCHAR *destination, const char *source,
	int destinationLength, UINT codePage)
{
	int converted;

	if (destination == 0 || source == 0)
	{
		return 0;
	}

	*destination = 0;
	converted = MultiByteToWideChar(codePage, 0, source, -1,
		destination, destinationLength);

	return converted ? destination : 0;
}

// ?Rva0005B8E0WideToAnsi@@YGPADPADPBGHI@Z
char *__stdcall Rva0005B8E0WideToAnsi(char *destination, const WCHAR *source,
	int destinationLength, UINT codePage)
{
	int converted;

	if (destination == 0 || source == 0)
	{
		return 0;
	}

	*destination = '\0';
	converted = WideCharToMultiByte(codePage, 0, source, -1,
		destination, destinationLength, 0, 0);

	return converted ? destination : 0;
}

// ?Rva0005BA60ThrowLastWin32@@YGXXZ
__declspec(noreturn) void __stdcall Rva0005BA60ThrowLastWin32(void)
{
	DWORD error = GetLastError();

	W3AtlThrow((HRESULT)error <= 0
		? (HRESULT)error
		: (HRESULT)((error & 0x0000FFFF) | 0x80070000));
}

extern "C" int __stdcall GdipDeleteGraphics(void *graphics);

class Rva0005BB50
{
public:
	void release(void);

	void *m_ptr;
};

// ?release@Rva0005BB50@@QAEXXZ
void Rva0005BB50::release(void)
{
	GdipDeleteGraphics(m_ptr);
}


