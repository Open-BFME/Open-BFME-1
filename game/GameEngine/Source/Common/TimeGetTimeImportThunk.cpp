// cl: /DNDEBUG /MD /EHs-c-
// WINMM.dll timeGetTime import stub at 0x007E4810: FF 25 [IAT].

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTimeIat(void);

extern "C" unsigned long __stdcall timeGetTime(void)
{
	return timeGetTimeIat();
}
