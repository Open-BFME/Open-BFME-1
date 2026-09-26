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
