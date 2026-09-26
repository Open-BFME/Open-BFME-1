// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the self-patching wide-API thunks and their shared platform test.
//
// Seven bodies in d_0005b6c0.asm open with the identical eight instructions
//
//     test byte ptr [0x012ED26C],1 / jne / or dword ptr [0x012ED26C],1
//     call GetVersion / shr eax,0x1F / and al,1 / mov byte ptr [0x012ED268],al
//
// which is one function-local static of scalar type: 0x012ED26C is the MSVC
// once-guard bitfield and bit 0 is the FIRST such static in its translation
// unit, so all seven were compiled together and share one inline "are we on
// Windows 9x" predicate. GetVersion's sign bit is the 9x flag.
//
// The six 71-byte bodies then differ only in three copied DIR32 operands: a
// function-pointer slot in the 0x012A6814..0x012A6828 block, a Win9x fallback
// ILT thunk, and the __imp_ slot of the real wide API. Each one is
//
//     InterlockedExchange(&slot, is9x ? fallback : realWideApi);
//     jmp slot;          // tail call, arguments untouched
//
// so the argument list never appears in the code and the six bodies are
// byte-identical outside their relocations. The slots pair up as
//   0x012A6814 CompareStringW          0x012A6818 GetStringTypeExW
//   0x012A681C lstrcmpiW               0x012A6820 CharLowerW
//   0x012A6824 CharUpperW              0x012A6828 GetEnvironmentVariableW
// and each fallback is an ILT thunk into a body that converts to ANSI with
// MultiByteToWideChar/WideCharToMultiByte around the A-suffixed API, i.e. the
// usual statically linked Microsoft-Layer-for-Unicode style shim.
//
// The seventh body at 0x0005DCD0 is the same choice without the tail call: a
// __cdecl helper that patches a caller-supplied slot. It is what fixes the
// predicate as an INLINE function rather than a call -- if it were the shared
// implementation the six thunks would call it instead of re-inlining the guard.
//
// Identity is address-derived: nothing in the image names these, so the ledger
// rows carry Rva-prefixed names. Only the three DIR32 operands per body are
// unproven, and those are copied from retail rather than resolved.

typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned short WCHAR;

extern "C"
{
	__declspec(dllimport) DWORD __stdcall GetVersion(void);
	__declspec(dllimport) LONG __stdcall InterlockedExchange(LONG *target, LONG value);

	__declspec(dllimport) int __stdcall CompareStringW(DWORD locale, DWORD flags,
		const WCHAR *a, int lenA, const WCHAR *b, int lenB);
	__declspec(dllimport) int __stdcall GetStringTypeExW(DWORD locale, DWORD infoType,
		const WCHAR *src, int count, unsigned short *charType);
	__declspec(dllimport) int __stdcall lstrcmpiW(const WCHAR *a, const WCHAR *b);
	__declspec(dllimport) WCHAR *__stdcall CharLowerW(WCHAR *str);
	__declspec(dllimport) WCHAR *__stdcall CharUpperW(WCHAR *str);
	__declspec(dllimport) DWORD __stdcall GetEnvironmentVariableW(const WCHAR *name,
		WCHAR *buffer, DWORD size);

	// the Win9x fallbacks; each is an ILT thunk into a convert-call-convert body
	int __stdcall Rva0005E9A0_CompareStringW9x(DWORD, DWORD, const WCHAR *, int, const WCHAR *, int);
	int __stdcall Rva0005DD20_lstrcmpiW9x(const WCHAR *, const WCHAR *);
	WCHAR *__stdcall Rva0005DE80_CharLowerW9x(WCHAR *);
	WCHAR *__stdcall Rva0005B930_CharUpperW9x(WCHAR *);
	DWORD __stdcall Rva0005F680_GetEnvironmentVariableW9x(const WCHAR *, WCHAR *, DWORD);
}

namespace ATL
{
	int __stdcall GetStringTypeExWFake(DWORD locale, DWORD infoType,
		const WCHAR *src, int count, unsigned short *charType);
}

typedef int (__stdcall *PFNCOMPARESTRINGW)(DWORD, DWORD, const WCHAR *, int, const WCHAR *, int);
typedef int (__stdcall *PFNGETSTRINGTYPEEXW)(DWORD, DWORD, const WCHAR *, int, unsigned short *);
typedef int (__stdcall *PFNLSTRCMPIW)(const WCHAR *, const WCHAR *);
typedef WCHAR *(__stdcall *PFNCHARLOWERW)(WCHAR *);
typedef WCHAR *(__stdcall *PFNCHARUPPERW)(WCHAR *);
typedef DWORD (__stdcall *PFNGETENVIRONMENTVARIABLEW)(const WCHAR *, WCHAR *, DWORD);

extern PFNCOMPARESTRINGW g_pfnCompareStringW;					///< retail [0x012A6814]
extern PFNGETSTRINGTYPEEXW g_pfnGetStringTypeExW;				///< retail [0x012A6818]
extern PFNLSTRCMPIW g_pfnLstrcmpiW;								///< retail [0x012A681C]
extern PFNCHARLOWERW g_pfnCharLowerW;							///< retail [0x012A6820]
extern PFNCHARUPPERW g_pfnCharUpperW;							///< retail [0x012A6824]
extern PFNGETENVIRONMENTVARIABLEW g_pfnGetEnvironmentVariableW;	///< retail [0x012A6828]

static bool isWindows9x(void)
{
	static bool is9x = (GetVersion() & 0x80000000) != 0;		///< guard bit 0 of [0x012ED26C]
	return is9x;
}

// ?Rva0005DCD0_patchWideProc@@YAJPAJJJ@Z
LONG Rva0005DCD0_patchWideProc(LONG *slot, LONG win9xProc, LONG wideProc)
{
	return InterlockedExchange(slot, isWindows9x() ? win9xProc : wideProc);
}

// ?Rva0005EB60_CompareStringW@@YGHKKPBGH0H@Z
int __stdcall Rva0005EB60_CompareStringW(DWORD locale, DWORD flags,
	const WCHAR *a, int lenA, const WCHAR *b, int lenB)
{
	InterlockedExchange((LONG *)&g_pfnCompareStringW,
		isWindows9x() ? (LONG)Rva0005E9A0_CompareStringW9x : (LONG)CompareStringW);
	return g_pfnCompareStringW(locale, flags, a, lenA, b, lenB);
}

// ?Rva0005FA00_GetStringTypeExW@@YGHKKPBGHPAG@Z
int __stdcall Rva0005FA00_GetStringTypeExW(DWORD locale, DWORD infoType,
	const WCHAR *src, int count, unsigned short *charType)
{
	InterlockedExchange((LONG *)&g_pfnGetStringTypeExW,
		isWindows9x() ? (LONG)ATL::GetStringTypeExWFake : (LONG)GetStringTypeExW);
	return g_pfnGetStringTypeExW(locale, infoType, src, count, charType);
}

// ?Rva0005DE20_lstrcmpiW@@YGHPBG0@Z
int __stdcall Rva0005DE20_lstrcmpiW(const WCHAR *a, const WCHAR *b)
{
	InterlockedExchange((LONG *)&g_pfnLstrcmpiW,
		isWindows9x() ? (LONG)Rva0005DD20_lstrcmpiW9x : (LONG)lstrcmpiW);
	return g_pfnLstrcmpiW(a, b);
}

// ?Rva0005DF80_CharLowerW@@YGPAGPAG@Z
WCHAR *__stdcall Rva0005DF80_CharLowerW(WCHAR *str)
{
	InterlockedExchange((LONG *)&g_pfnCharLowerW,
		isWindows9x() ? (LONG)Rva0005DE80_CharLowerW9x : (LONG)CharLowerW);
	return g_pfnCharLowerW(str);
}

// ?Rva0005DFE0_CharUpperW@@YGPAGPAG@Z
WCHAR *__stdcall Rva0005DFE0_CharUpperW(WCHAR *str)
{
	InterlockedExchange((LONG *)&g_pfnCharUpperW,
		isWindows9x() ? (LONG)Rva0005B930_CharUpperW9x : (LONG)CharUpperW);
	return g_pfnCharUpperW(str);
}

// ?Rva0005F880_GetEnvironmentVariableW@@YGKPBGPAGK@Z
DWORD __stdcall Rva0005F880_GetEnvironmentVariableW(const WCHAR *name, WCHAR *buffer, DWORD size)
{
	InterlockedExchange((LONG *)&g_pfnGetEnvironmentVariableW,
		isWindows9x() ? (LONG)Rva0005F680_GetEnvironmentVariableW9x : (LONG)GetEnvironmentVariableW);
	return g_pfnGetEnvironmentVariableW(name, buffer, size);
}
