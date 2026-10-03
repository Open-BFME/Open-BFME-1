// ?rva0090FE80@@YAXPAXHMMH@Z
// partial score=0.4524 date=2026-10-03
// cl: /O2 /G6 /MD
// Retail complete extent 0090FE80..0090FEDE (95B), then INT3.
// Ghidra body membership is86B because it excludes9B of internal loop alignment.
// Existing readonly pins: VA01075334=1.0f; VA01075350=0.0f.
// Best tested native shape84B/46 non-reloc differences; all4 relocation
// offsets drift. Missing JMP+9-byte alignment and FLD/store scheduling remain.
extern const float Rva00C75334One;
extern const float Rva00C75350Zero;

struct Rva0090FE80Pair
{
    float at0;
    float at4;
};

void rva0090FE80(void *destination, int stride, float at0, float at4, int count)
{
    for (; count; --count)
    {
        Rva0090FE80Pair *pair = static_cast<Rva0090FE80Pair *>(destination);
        pair->at0 = at0;
        pair->at4 = at4;
        if (at0 != Rva00C75350Zero)
        {
            at0 = Rva00C75350Zero;
            at4 = Rva00C75334One - at4;
        }
        else
        {
            at0 = Rva00C75334One;
        }
        destination = static_cast<char *>(destination) + stride;
    }
}
