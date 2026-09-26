// ?Rva009AC390@@YAXPAURva009AC240State@@II@Z
// partial score=0.96 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
struct Rva009AC240State
{
    int m_words[5];
    void *m_pointer;
};

void __cdecl Rva009AC390(Rva009AC240State *state, unsigned int, unsigned int probability)
{
    int count = state->m_words[3];
    unsigned int code = (unsigned int)state->m_words[0];
    unsigned int range = (unsigned int)state->m_words[1];
    unsigned int bound = (((range - 1) * probability) >> 8) + 1;
    range -= bound;
    code += bound;
    while (range < 128)
    {
        range <<= 1;
        if ((code & 0x80000000) != 0)
        {
            int i = state->m_words[4] - 1;
            while (i >= 0 && ((unsigned char *)state->m_pointer)[i] == 255)
            {
                ((unsigned char *)state->m_pointer)[i] = 0;
                --i;
            }
            ++((unsigned char *)state->m_pointer)[i];
        }
        code <<= 1;
        if (++count == 0)
        {
            volatile int &index = state->m_words[4];
            ((unsigned char *)state->m_pointer)[index] = (unsigned char)(code >> 24);
            count = -8;
            ++index;
            code &= 0xffffff;
        }
    }
    state->m_words[1] = (int)range;
    state->m_words[0] = (int)code;
    state->m_words[3] = count;
}
