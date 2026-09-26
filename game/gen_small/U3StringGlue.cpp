// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: three Win32/CRT string helpers out of d_0005b6c0.asm.
//
// Rva0005B890AnsiToWide is the ANSI-to-wide half of the Microsoft-Layer-for-
// Unicode style shim family the wide-API thunks in
// game/GameEngine/Source/Common/T3Win9xWideApiThunks.cpp dispatch into: it
// calls KERNEL32 MultiByteToWideChar through `ff 15 [__imp_]`, so the import is
// declared dllimport rather than as a direct REL32 extern. The argument order
// is read straight off the pushes -- codePage, 0, source, -1, destination,
// destination length -- and the `neg / sbb / and esi` tail is
// `return converted ? destination : NULL` compiled without a branch.
//
// Rva0005DC30Compare and Rva0006DF50CompareNoCase are the same function twice,
// once case-sensitive and once not. Both take (pointer, length, pointer,
// length), compare min(lenA,lenB) bytes and fall back to the length difference
// when those bytes are equal. The case-sensitive one has NO call in it at all:
// `repe cmpsb` followed by `sbb eax,eax / sbb eax,-1` is the MSVC memcmp
// intrinsic expanded inline, which is what proves the source said memcmp and
// not a hand-written loop. The case-insensitive twin has to call, because
// _memicmp has no intrinsic form, and it goes through `ff 15 [__imp__memicmp]`
// -- a six-byte indirect call, which is the dllimport form the real vendored
// <string.h> gives under /MD.
//
// Identity is address-derived: nothing in the image names these three.

#include <string.h>

typedef unsigned short WCHAR;
typedef unsigned long DWORD;
typedef unsigned int UINT;

extern "C"
{
	__declspec(dllimport) int __stdcall MultiByteToWideChar(UINT codePage, DWORD flags,
		const char *multiByteStr, int multiByteCount,
		WCHAR *wideCharStr, int wideCharCount);
}

// ?Rva0005B890AnsiToWide@@YGPAGPAGPBDHI@Z
WCHAR *__stdcall Rva0005B890AnsiToWide(WCHAR *destination, const char *source,
	int destinationLength, UINT codePage)
{
	if (destination != 0 && source != 0)
	{
		*destination = 0;

		return MultiByteToWideChar(codePage, 0, source, -1, destination, destinationLength) != 0
			? destination : 0;
	}

	return 0;
}

// ?Rva0005DC30Compare@@YAHPBDH0H@Z
int Rva0005DC30Compare(const char *a, int lengthA, const char *b, int lengthB)
{
	int count = lengthA < lengthB ? lengthA : lengthB;
	int result = memcmp(a, b, count);

	if (result != 0)
	{
		return result;
	}

	return lengthA - lengthB;
}

// ?Rva0006DF50CompareNoCase@@YAHPBDH0H@Z
int Rva0006DF50CompareNoCase(const char *a, int lengthA, const char *b, int lengthB)
{
	int count = lengthA < lengthB ? lengthA : lengthB;
	int result = _memicmp(a, b, count);

	if (result != 0)
	{
		return result;
	}

	return lengthA - lengthB;
}
