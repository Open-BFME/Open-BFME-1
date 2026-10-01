// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x009AC2F0: 145-byte scalar/byte loop, address-derived state view.
// Independent physical ABI: cdecl three stack words; result unused; RET.
// INT3 ends at 0x009AC2EF; final RET is 0x009AC380; INT3 starts 0x009AC381.
// The state slots at +0/+4/+C/+10/+14 are directly witnessed. Historical
// field labels are local descriptions; native owner, names and declared types
// remain unproven. No codec identity, constructor, base or lifetime is claimed.
// Unsigned words model the observed wrapping arithmetic and shifts. The
// signed backward index follows VC7.1's 32-bit signed conversion; the borrowed
// byte pointer must permit the predecessor positions the carry loop touches.
// Resetting the local accumulator before the byte store keeps its register
// live. Reloading the index after that store preserves possible byte aliasing
// with the state; these two operations recover retail's EBP allocation.
struct Rva009AC2F0State
{
    unsigned int m_value;
    unsigned int m_count;
    int m_unused;
    unsigned int m_bit_accumulator;
    unsigned int m_buffer_index;
    unsigned char *m_buffer;
};

void Rva009AC2F0PackBits(Rva009AC2F0State *state, int backwards, int amount)
{
    unsigned int value = state->m_value;
    unsigned int count = state->m_count;
    unsigned int accumulator = state->m_bit_accumulator;
    unsigned int shift = (unsigned int)((count - 1U) * (unsigned int)amount);
    shift >>= 8;
    ++shift;
    if (backwards != 0) {
        value += shift;
        count -= shift;
        shift = count;
    }
    while (shift < 128) {
        shift <<= 1;
        if (((unsigned int)value & 0x80000000U) != 0) {
            int index = (int)(state->m_buffer_index - 1U);
            while (index >= 0 && state->m_buffer[index] == 0xff) {
                state->m_buffer[index] = 0;
                --index;
            }
            ++state->m_buffer[index];
        }
        value <<= 1;
        if (++accumulator == 0) {
            accumulator = -8;
            unsigned char *buffer = state->m_buffer;
            unsigned int buffer_index = state->m_buffer_index;
            buffer[buffer_index] = (unsigned char)((unsigned int)value >> 24);
            unsigned int next_index = state->m_buffer_index;
            ++next_index;
            state->m_buffer_index = next_index;
            value &= 0x00ffffff;
        }
    }
    state->m_value = value;
    state->m_count = shift;
    state->m_bit_accumulator = accumulator;
}
