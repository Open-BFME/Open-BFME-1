// cl: /DNDEBUG /MD /EHs-c-
// KERNEL32.dll Sleep import stub at 0x007E9BB0: FF 25 [IAT].

extern "C" __declspec(dllimport) void __stdcall SleepIat(unsigned long ms);

extern "C" void __stdcall Sleep(unsigned long ms)
{
	SleepIat(ms);
}
