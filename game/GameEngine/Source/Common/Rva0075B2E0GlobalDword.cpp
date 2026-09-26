// Global dword load at 0x0075B2E0.
//
//     mov eax, dword ptr [g_rva0075b2e0_value] / ret
//
// Free-function __cdecl load of a module-level dword. The DIR32 is filled
// from retail. Identity is not recovered.

unsigned int g_rva0075b2e0_value;

unsigned int Rva0075B2E0()
{
	return g_rva0075b2e0_value;
}
