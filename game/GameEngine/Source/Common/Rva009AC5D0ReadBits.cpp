// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009AC5D0State
{
	const unsigned char *m_data;
	unsigned int m_value;
	unsigned int m_bits;
	unsigned int m_bytes;
};

unsigned int Rva009AC5D0ReadBits(
	Rva009AC5D0State *state, unsigned int count)
{
	unsigned int bytes = state->m_bytes;
	const unsigned char *input = state->m_data;
	unsigned int bits = state->m_bits;
	unsigned int value = state->m_value;
	input += bytes;
	unsigned int result = 0;

	if (bits < count)
	{
		result = value >> (32 - bits);
		count -= bits;
		result <<= count;
		value = input[0];
		value = (value << 8) + input[1];
		value = (value << 8) + input[2];
		value = (value << 8) + input[3];
		bytes += 4;
		bits = 32;
	}

	state->m_value = value << count;
	state->m_bits = bits - count;
	state->m_bytes = bytes;
	return (value >> (32 - count)) | result;
}
