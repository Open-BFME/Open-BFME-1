// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B4800State
{
	unsigned char m_pad0[4];
	unsigned m_range;
	unsigned m_code;
	int m_bitsRemaining;
	unsigned m_inputCursor;
	const unsigned char *m_inputBase;
};

int Rva009B4800DecodeBool(Rva009B4800State *state, int probability)
{
	int bitsRemaining = state->m_bitsRemaining;
	unsigned code = state->m_code;
	unsigned range = state->m_range;
	int bit = 0;
	unsigned split = (((range - 1) * probability) >> 8) + 1;
	unsigned threshold = split << 24;

	if (code >= threshold) {
		range -= split;
		code -= threshold;
		bit = 1;
	} else {
		range = split;
	}

	while (range < 0x80) {
		range += range;
		code += code;
		if (--bitsRemaining == 0) {
			code |= state->m_inputBase[state->m_inputCursor];
			bitsRemaining = 8;
			++state->m_inputCursor;
		}
	}

	state->m_range = range;
	state->m_code = code;
	state->m_bitsRemaining = bitsRemaining;
	return bit;
}
