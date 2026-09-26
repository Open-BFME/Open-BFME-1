// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: three of the six Win9x fallbacks that
// game/GameEngine/Source/Common/T3Win9xWideApiThunks.cpp declares and patches
// into its function-pointer slots. All three are the same convert-call-convert
// shape and all three use the PLAIN stack conversion, not the guarded one --
// `lea eax,[n+3] / and eax,-4 / call __alloca_probe / mov reg,esp` with no size
// test and no heap fallback -- which is what separates them from the three
// remaining fallbacks at 0x0005E9A0, 0x0005F680 and 0x0005F8E0.
//
// The conversion helpers are INLINE here. Retail inlines both of them into all
// three bodies (the `neg / sbb / and` tail appears once per conversion, never as
// a call), while the out-of-line copy of the wide-to-ANSI helper sits at
// 0x0005B8E0 in W3AtlConversionSupport.cpp -- so that copy belongs to some other
// translation unit and cannot be shared with this one.
//
// The code page comes from the self-patching slot at [0x012A64C0], read once per
// body before anything else; 0x0005B820 is what fills it.
//
// The two Char* bodies convert, call the ANSI API for its side effect only --
// its return value is dropped, the shim keeps using its own pointer -- and copy
// the result back over the caller's buffer with wcscpy before returning that
// same buffer. The compare body converts both arguments and returns lstrcmpiA
// of them; retail converts the SECOND argument first, which is just MSVC
// evaluating the argument list right to left.
//
// Identity is address-derived.

#include <malloc.h>

typedef unsigned short WCHAR;
typedef unsigned long DWORD;
typedef unsigned int UINT;

typedef UINT (__stdcall *W3AtlAcpProc)(void);

extern "C"
{
	__declspec(dllimport) int __stdcall lstrlenA(const char *str);
	__declspec(dllimport) int __stdcall lstrlenW(const WCHAR *str);
	__declspec(dllimport) int __stdcall lstrcmpiA(const char *a, const char *b);
	__declspec(dllimport) char *__stdcall CharUpperA(char *str);
	__declspec(dllimport) char *__stdcall CharLowerA(char *str);
	__declspec(dllimport) int __stdcall WideCharToMultiByte(UINT codePage, DWORD flags,
		const WCHAR *wideCharStr, int wideCharCount,
		char *multiByteStr, int multiByteCount,
		const char *defaultChar, int *usedDefaultChar);
	__declspec(dllimport) int __stdcall MultiByteToWideChar(UINT codePage, DWORD flags,
		const char *multiByteStr, int multiByteCount,
		WCHAR *wideCharStr, int wideCharCount);
	__declspec(dllimport) WCHAR *__cdecl wcscpy(WCHAR *destination, const WCHAR *source);
}

extern W3AtlAcpProc g_pfnGetConversionAcp;							///< retail [0x012A64C0]

inline char *w3WideToAnsi(char *destination, const WCHAR *source,
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

inline WCHAR *w3AnsiToWide(WCHAR *destination, const char *source,
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

// ?Rva0005B930_CharUpperW9x@@YGPAGPAG@Z
WCHAR *__stdcall Rva0005B930_CharUpperW9x(WCHAR *str)
{
	UINT acp = g_pfnGetConversionAcp();
	int convert;
	char *ansi;

	ansi = (str == 0)
		? 0
		: (convert = (lstrlenW(str) + 1) * 2,
			w3WideToAnsi((char *)_alloca(convert), str, convert, acp));

	CharUpperA(ansi);

	wcscpy(str, (ansi == 0)
		? 0
		: (convert = lstrlenA(ansi) + 1,
			w3AnsiToWide((WCHAR *)_alloca(convert * 2), ansi, convert, acp)));

	return str;
}

// ?Rva0005DE80_CharLowerW9x@@YGPAGPAG@Z
WCHAR *__stdcall Rva0005DE80_CharLowerW9x(WCHAR *str)
{
	UINT acp = g_pfnGetConversionAcp();
	int convert;
	char *ansi;

	ansi = (str == 0)
		? 0
		: (convert = (lstrlenW(str) + 1) * 2,
			w3WideToAnsi((char *)_alloca(convert), str, convert, acp));

	CharLowerA(ansi);

	wcscpy(str, (ansi == 0)
		? 0
		: (convert = lstrlenA(ansi) + 1,
			w3AnsiToWide((WCHAR *)_alloca(convert * 2), ansi, convert, acp)));

	return str;
}

// ?Rva0005DD20_lstrcmpiW9x@@YGHPBG0@Z
int __stdcall Rva0005DD20_lstrcmpiW9x(const WCHAR *a, const WCHAR *b)
{
	UINT acp = g_pfnGetConversionAcp();
	int convert;

	return lstrcmpiA(
		(a == 0)
			? 0
			: (convert = (lstrlenW(a) + 1) * 2,
				w3WideToAnsi((char *)_alloca(convert), a, convert, acp)),
		(b == 0)
			? 0
			: (convert = (lstrlenW(b) + 1) * 2,
				w3WideToAnsi((char *)_alloca(convert), b, convert, acp)));
}
