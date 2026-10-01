// cl: /DNDEBUG /MD /EHsc
// RVA 0x009AC240: initialize six 32-bit slots of an address-derived state.
struct Rva009AC240State
{
    int m_words[5];
    void *m_pointer;
};

void __cdecl Rva009AC240Init(Rva009AC240State *state, void *pointer)
{
    state->m_words[0] = 0;
    state->m_words[1] = 255;
    state->m_words[2] = 0;
    state->m_words[3] = -24;
    state->m_pointer = pointer;
    state->m_words[4] = 0;
}

// RVA 0x009AC270: flush the pending 32-bit word as four bytes.
void __cdecl Rva009AC270(Rva009AC240State *state)
{
    int bit = state->m_words[3];
    int shift;
    if (bit < -16)
        shift = 24;
    else
    {
        shift = 16;
        if (bit >= -8)
            shift = 8;
    }
    shift -= bit & 7;
    state->m_words[0] = (unsigned int)state->m_words[0] << shift;
    ((unsigned char *)state->m_pointer)[state->m_words[4]++] = ((unsigned char *)&state->m_words[0])[3];
    ((unsigned char *)state->m_pointer)[state->m_words[4]++] = ((unsigned char *)&state->m_words[0])[2];
    ((unsigned char *)state->m_pointer)[state->m_words[4]++] = ((unsigned char *)&state->m_words[0])[1];
    ((unsigned char *)state->m_pointer)[state->m_words[4]++] = ((unsigned char *)&state->m_words[0])[0];
}

// RVA 0x009AC390: independently decoded 133-byte cdecl body.
// Three incoming words; the second is unused. Source void is chosen for
// ignored-result transport; the native declared return/type/owner is unknown.
// This uses the existing six-word address view, with no codec or lifetime claim.
// Unsigned arithmetic models wrapping bits; signed conversions use fixed
// VC7.1 32-bit behavior. The borrowed pointer permits carry-touched bytes,
// including predecessor positions; no fixed array extent is declared.
// Counter reset before output temporaries keeps its register live; post-byte
// index reload preserves aliasing and gives the independently witnessed EBP.
void __cdecl Rva009AC390(Rva009AC240State *state, unsigned int, unsigned int probability)
{
    unsigned int count = (unsigned int)state->m_words[3];
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
            int i = (int)((unsigned int)state->m_words[4] - 1U);
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
            count = -8;
            unsigned char *buffer = (unsigned char *)state->m_pointer;
            int index = state->m_words[4];
            buffer[index] = (unsigned char)(code >> 24);
            unsigned int next_index = (unsigned int)state->m_words[4];
            ++next_index;
            state->m_words[4] = next_index;
            code &= 0xffffff;
        }
    }
    state->m_words[1] = (int)range;
    state->m_words[0] = (int)code;
    state->m_words[3] = count;
}
