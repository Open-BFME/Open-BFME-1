// cl: /DNDEBUG /MD /EHs-c-
// MSVCR71.dll _mbslen import stub at 0x007AE2D0: FF 25 [IAT].

extern "C" __declspec(dllimport) unsigned int __cdecl mbslenIat(
	const unsigned char *text);

extern "C" unsigned int __cdecl _mbslen(const unsigned char *text)
{
	return mbslenIat(text);
}
