// ?d_004533f0@@YAXXZ
// partial score=0.77 date=2026-09-24
// cl: /DNDEBUG /MD
class BfmeItemUW { public: unsigned char m_pad[8]; void *m_payload; };
char __cdecl bfmeSameUW(void *payload, BfmeItemUW *item, void *other);
struct Rva004533F0Record {
    unsigned char m_byte0, m_byte1, m_byte2, m_pad3;
    int m_word4;
    BfmeItemUW *m_item8;
    int m_serialC;
    int m_unused10;
};
char __cdecl rva004533f0(const Rva004533F0Record *first,
                           const Rva004533F0Record *second)
{
    const Rva004533F0Record *a = first;
    const Rva004533F0Record *b = second;
    for (int i = 0; i < 8; ++i, ++a, ++b)
    {
        if (a->m_byte0 != b->m_byte0 || a->m_byte1 != b->m_byte1 ||
            a->m_byte2 != b->m_byte2 || a->m_word4 != b->m_word4 ||
            a->m_serialC != b->m_serialC)
            return 0;
        BfmeItemUW *item = a->m_item8;
        if (!bfmeSameUW(item->m_payload, item, b->m_item8->m_payload))
            return 0;
    }
    return 1;
}
