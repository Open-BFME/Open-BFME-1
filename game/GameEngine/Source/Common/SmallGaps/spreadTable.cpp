// ?spreadTable@@YAXXZ
extern unsigned short* Rva009C0D10Src;
// Defined here, the one routine that fills it: retail keeps it zero-filled in
// .bss at VA 0x013566C0, and this loop writes exactly 0x100 entries.
unsigned short Rva009C0D10Table[0x100];
void spreadTable()
{
	unsigned short* src = Rva009C0D10Src;
	for (int i = 0; i < 0x100; i += 4, src += 2) {
		Rva009C0D10Table[i] = *src;
		Rva009C0D10Table[i + 1] = *src;
		Rva009C0D10Table[i + 2] = *src;
		Rva009C0D10Table[i + 3] = *src;
	}
}
