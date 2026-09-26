// Open-BFME: arena cursor advance and tail call reconstructed from retail RVA
// 0x00897110.  The cursor and target routine are identified by the surrounding
// arena implementation at 0x00897050/0x00897120.

extern char *g_bfmeArenaCursor;

void __cdecl bfmeArenaReady(void);

void __cdecl Rva00897110ArenaReadyThunk(void)
{
    g_bfmeArenaCursor += 0x60;
    bfmeArenaReady();
}
