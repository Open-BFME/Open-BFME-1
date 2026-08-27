// Open-BFME: imported-call result mask reconstructed from retail RVA 0x006BB530.

extern "C" __declspec(dllimport) int __stdcall Rva006BB530Imported(int value);

int Rva006BB530Invoke(void)
{
	return Rva006BB530Imported(0x14) & 1;
}
