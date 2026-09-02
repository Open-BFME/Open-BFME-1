// cl: /DNDEBUG /MD /EHs-c-
// MSVCR71.dll _XcptFilter import stub at 0x009F7EEC: FF 25 [IAT].

extern "C" __declspec(dllimport) int __cdecl XcptFilterIat(unsigned long code, void *info);

extern "C" int __cdecl _XcptFilter(unsigned long code, void *info)
{
	return XcptFilterIat(code, info);
}
