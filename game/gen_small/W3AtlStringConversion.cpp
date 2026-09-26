// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the ANSI/wide conversion-holder bodies out of d_0001466e.asm.
//
// Three functions that only make sense together. 0x0005DA80 and 0x0005DB10 are
// the same routine in each direction: a thiscall member taking (string, code
// page) with `ret 8`, whose object is one pointer at this+0 backed by a fixed
// 128-unit buffer the CONSTRUCTOR points that pointer at -- which is why the
// short path here stores nothing and simply reloads this+0 before converting.
// Both open by testing the incoming string against NULL, storing NULL into
// this+0 and returning early; both then take lstrlen+1, compare the BYTE count
// against 128, and only in the long arm reach for malloc. The store of the
// malloc result happens BEFORE the failure test (`test eax,eax / mov [reg],eax
// / jne`), so the source assigned the member and then tested the member, not a
// local. A zero from the conversion API tails into the last-Win32-error throw
// helper.
//
// 0x0005B7A0 is the code page those two are normally handed: the thread
// locale's LOCALE_IDEFAULTANSICODEPAGE read as text into a 7-byte buffer and
// parsed with a plain `n = n*10 + (*p - '0')` loop -- `lea esi,[eax+edx*2-0x30]`
// over `lea edx,[esi+esi*4]` is that multiply-by-ten with the '0' subtraction
// folded into the displacement. GetACP() is the fallback for both a failed
// query and a parse that yields zero, and the two failures share one block.
//
// malloc arrives as `ff 15 [__imp__malloc]`, the dllimport form the real
// vendored <stdlib.h> emits under /MD. The throw helpers are reached through
// the low-RVA ILT thunks at 0x00019ACE and 0x00032AF1 (bodies 0x0005BA40 and
// 0x0005BA60); both are noreturn, which is what lets the failure arms fall
// straight into the join instead of restoring a register across the call.
//
// Identity is address-derived: nothing in the image names these three.

#include <stdlib.h>

typedef unsigned short WCHAR;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef long LONG;
typedef long HRESULT;

#define W3_E_OUTOFMEMORY ((HRESULT)0x8007000EL)
#define W3_LOCALE_IDEFAULTANSICODEPAGE 0x1004

extern "C"
{
	__declspec(dllimport) DWORD __stdcall GetThreadLocale(void);
	__declspec(dllimport) int __stdcall GetLocaleInfoA(DWORD locale, DWORD lcType,
		char *lcData, int cchData);
	__declspec(dllimport) UINT __stdcall GetACP(void);
	__declspec(dllimport) int __stdcall lstrlenA(const char *str);
	__declspec(dllimport) int __stdcall lstrlenW(const WCHAR *str);
	__declspec(dllimport) int __stdcall WideCharToMultiByte(UINT codePage, DWORD flags,
		const WCHAR *wideCharStr, int wideCharCount,
		char *multiByteStr, int multiByteCount,
		const char *defaultChar, int *usedDefaultChar);
	__declspec(dllimport) int __stdcall MultiByteToWideChar(UINT codePage, DWORD flags,
		const char *multiByteStr, int multiByteCount,
		WCHAR *wideCharStr, int wideCharCount);

	__declspec(noreturn) void __stdcall W3AtlThrow(HRESULT hr);
	__declspec(noreturn) void __stdcall W3AtlThrowLastWin32(void);
}

// ?Rva0005B7A0GetConversionCodePage@@YGIXZ
UINT __stdcall Rva0005B7A0GetConversionCodePage(void)
{
	char codePageText[7];
	UINT codePage = 0;
	DWORD locale = GetThreadLocale();

	if (GetLocaleInfoA(locale, W3_LOCALE_IDEFAULTANSICODEPAGE, codePageText, 7))
	{
		const char *p;

		for (p = codePageText; *p != '\0'; ++p)
		{
			codePage = codePage * 10 + (*p - '0');
		}
	}

	if (codePage == 0)
	{
		return GetACP();
	}

	return codePage;
}

class Rva0005DA80WideToAnsi
{
public:
	void init(const WCHAR *source, UINT codePage);

	char *m_text;										///< retail this+0x00
	char m_buffer[128];									///< retail this+0x04
};

class Rva0005DB10AnsiToWide
{
public:
	void init(const char *source, UINT codePage);

	WCHAR *m_text;										///< retail this+0x00
	WCHAR m_buffer[128];								///< retail this+0x04
};

// ?init@Rva0005DA80WideToAnsi@@QAEXPBGI@Z
void Rva0005DA80WideToAnsi::init(const WCHAR *source, UINT codePage)
{
	int wideCount;
	int ansiCount;

	if (source == 0)
	{
		m_text = 0;
		return;
	}

	wideCount = lstrlenW(source) + 1;
	ansiCount = wideCount * 2;

	if (ansiCount > 128)
	{
		m_text = (char *)malloc(ansiCount);
		if (m_text == 0)
		{
			W3AtlThrow(W3_E_OUTOFMEMORY);
		}
	}

	if (WideCharToMultiByte(codePage, 0, source, wideCount, m_text, ansiCount, 0, 0) == 0)
	{
		W3AtlThrowLastWin32();
	}
}

// ?init@Rva0005DB10AnsiToWide@@QAEXPBDI@Z
void Rva0005DB10AnsiToWide::init(const char *source, UINT codePage)
{
	int ansiCount;

	if (source == 0)
	{
		m_text = 0;
		return;
	}

	ansiCount = lstrlenA(source) + 1;

	if (ansiCount > 128)
	{
		m_text = (WCHAR *)malloc(ansiCount * 2);
		if (m_text == 0)
		{
			W3AtlThrow(W3_E_OUTOFMEMORY);
		}
	}

	if (MultiByteToWideChar(codePage, 0, source, ansiCount, m_text, ansiCount) == 0)
	{
		W3AtlThrowLastWin32();
	}
}
