// ?Rva009AC2F0PackBits@@YAXPAURva009AC2F0State@@HH@Z
// partial score=0.68 date=2026-09-04
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Open-BFME5 conversion of the VP6 packed-byte output loop.

struct Rva009AC2F0State
{
	int m_value;
	int m_count;
	int m_unused;
	int m_bit_accumulator;
	int m_buffer_index;
	unsigned char *m_buffer;
};

void Rva009AC2F0PackBits(Rva009AC2F0State *state, int backwards, int amount)
{
    int value = state->m_value;
    int count = state->m_count;
    int accumulator = state->m_bit_accumulator;
    unsigned int shift = (unsigned int)((count - 1) * amount);
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
            int index = state->m_buffer_index - 1;
			while (index >= 0 && state->m_buffer[index] == 0xff) {
				state->m_buffer[index] = 0;
				--index;
			}
			++state->m_buffer[index];
        }
        value <<= 1;
        if (++accumulator == 0) {
            unsigned char *buffer = state->m_buffer;
            int buffer_index = state->m_buffer_index;
            int next_index = state->m_buffer_index;
            buffer[buffer_index] =
                (unsigned char)((unsigned int)value >> 24);
            ++next_index;
            state->m_buffer_index = next_index;
            accumulator = -8;
            value &= 0x00ffffff;
		}
	}
	state->m_value = value;
	state->m_count = shift;
	state->m_bit_accumulator = accumulator;
}
