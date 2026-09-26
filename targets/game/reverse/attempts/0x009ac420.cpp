// ?Rva009AC420@@YAXPAURva009AC240State@@II@Z
// partial score=0.7209 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
struct Rva009AC240State
{
    int m_words[5];
    void *m_pointer;
};

void __cdecl Rva009AC420(Rva009AC240State *state, unsigned int, unsigned int probability)
{
    unsigned int range = (unsigned int)state->m_words[1];
    unsigned int code = (unsigned int)state->m_words[0];
    int count = state->m_words[3];
    unsigned int bound = (((range - 1) * probability) >> 8) + 1;
    while (bound < 128)
    {
        bound <<= 1;
        if ((int)code < 0)
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
    state->m_words[0] = (int)code;
    state->m_words[1] = (int)bound;
    state->m_words[3] = count;
}
