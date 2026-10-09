// cl: /O2 /MD
// Retail 0x00C6B240 (22 B) is the dynamic initializer of the bool g_aiTargetDispatchSuppressed
// (VA 0x012F08A0). It passes the address in ECX to the fastcall state initializer
// @Rva00385FB0Initialize@4 (matched in Rva00385FB0State.cpp, reached through ILT 0x00012AD5),
// then registers the cleanup bfmeForward_00C6FE70 with atexit.

extern bool g_aiTargetDispatchSuppressed;
extern "C" void __fastcall Rva00385FB0Initialize(void *state);
void bfmeForward_00C6FE70(void);

void rva00C6B240Initialize(void)
{
	Rva00385FB0Initialize(&g_aiTargetDispatchSuppressed);
	atexit((void (*)(void))bfmeForward_00C6FE70);
}
