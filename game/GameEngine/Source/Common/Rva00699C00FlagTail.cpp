// Open-BFME: global flag update and tail dispatch reconstructed from retail RVA 0x00699C00.

__declspec(noreturn) void j_0002fbbc();
// Retail .data VA 0x012BA144 is one byte holding 1.
unsigned char g_012BA144 = 1;

void Rva00699C00SetFlag()
{
    g_012BA144 = 1;
    j_0002fbbc();
}
