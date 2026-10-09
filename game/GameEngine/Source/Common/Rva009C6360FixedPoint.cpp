// Ported from Open BFME 2 Code/Libraries/Source/Theora/IDct1.c.
// ?Rva009C6360@@YAXPBF0PAI@Z
void __cdecl Rva009C6360(const short *first, const short *second, unsigned int *output)
{
    int loop;
    short value;

    value = (short)((int)(first[0] * second[0] + 15) >> 5);
    for (loop = 0; loop < 64; loop++)
        ((short *)output)[loop] = value;
}
