// Open-BFME: clock delta reconstructed from retail RVA 0x008793B0.

extern "C" __declspec(dllimport) long __cdecl clock(void);

int Rva008793B0(int start)
{
    return clock() - start;
}
