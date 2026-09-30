// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME5: retail 0x007E5820 (21 bytes), four-argument import forwarder.

extern "C" __declspec(dllimport) void __stdcall RaiseException(
	void *first, void *second, int third, int fourth);

void rva007e5820_call(void *first, void *second)
{
	RaiseException(first, second, 0, 0);
}
