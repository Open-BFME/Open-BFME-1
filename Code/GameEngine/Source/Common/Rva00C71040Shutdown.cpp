// Open-BFME: shutdown helper reconstructed from retail RVA 0x00C71040.

extern "C" __declspec(dllimport) void __stdcall Rva01358D0CReset(void *body);

void Rva00C71040Shutdown()
{
    Rva01358D0CReset(reinterpret_cast<void *>(0x012D6DE0u));
    *reinterpret_cast<unsigned char *>(0x012D6DF8u) = 0;
}
