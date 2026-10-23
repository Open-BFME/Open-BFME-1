// Open-BFME: global flag update and tail dispatch reconstructed from retail RVA 0x00699C00.

__declspec(noreturn) void j_0002fbbc();
// Retail .data VA 0x012BA144 is one byte holding 1.
unsigned char g_012BA144 = 1;

// 0x00699BF0 is the clearing twin of 0x00699C00: the same byte store and
// tail jump with 0 instead of 1 (its ILT entry lands on the store, not on the
// jmp at +7 that a generated row used to claim).
void Rva00699BF0ClearFlag()
{
    g_012BA144 = 0;
    j_0002fbbc();
}

void Rva00699C00SetFlag()
{
    g_012BA144 = 1;
    j_0002fbbc();
}

// Five channel setters follow: each stores its float argument in the Miles
// channel volume global that AudioManagerInit (0x006B8220) initialises, then
// reuses the argument slot for the channel index and tail-jumps to ILT
// 0x00047F3C. Channels 3 and 4 sit in swapped address order in retail.
void j_00047f3c();
extern float g_milesVolume012BA12C;
extern float g_milesVolume012BA130;
extern float g_milesVolume012BA134;
extern float g_milesVolume012BA138;
extern float g_milesVolume012BA13C;
static __forceinline void applyMilesChannel00699C10(int channel)
{
    ((void (__cdecl *)(int))j_00047f3c)(channel);
}

void __cdecl Rva00699C10(float volume)
{
    g_milesVolume012BA12C = volume;
    applyMilesChannel00699C10(0);
}

void __cdecl Rva00699C30(float volume)
{
    g_milesVolume012BA130 = volume;
    applyMilesChannel00699C10(1);
}

void __cdecl Rva00699C50(float volume)
{
    g_milesVolume012BA134 = volume;
    applyMilesChannel00699C10(2);
}

void __cdecl Rva00699C70(float volume)
{
    g_milesVolume012BA13C = volume;
    applyMilesChannel00699C10(4);
}

void __cdecl Rva00699C90(float volume)
{
    g_milesVolume012BA138 = volume;
    applyMilesChannel00699C10(3);
}
