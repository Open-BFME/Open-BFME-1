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
