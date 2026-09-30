// Open-BFME: imported-call result mask reconstructed from retail RVA 0x006BB530.

extern "C" __declspec(dllimport) int __stdcall GetKeyState(int value);

int Rva006BB530Invoke(void)
{
	return GetKeyState(0x14) & 1;
}
