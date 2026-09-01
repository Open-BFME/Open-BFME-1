// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B4680State
{
	unsigned char m_pad0[4];
	unsigned m_range;
	unsigned m_code;
	int m_bitsRemaining;
	unsigned m_inputCursor;
	const unsigned char *m_inputBase;
};

int Rva009B4680Normalize(Rva009B4680State *state)
{
	unsigned range = state->m_range;
	unsigned code = state->m_code;
	int bitsRemaining = state->m_bitsRemaining;
	unsigned half = (range + 1) >> 1;
	unsigned threshold = half << 24;
	int bit;

	if (code >= threshold) {
		range -= half;
		code -= threshold;
		range <<= 1;
		code <<= 1;
		bit = 1;
	} else {
		range = half << 1;
		code <<= 1;
		bit = 0;
	}

	if (--bitsRemaining == 0) {
		bitsRemaining = 8;
		code |= state->m_inputBase[state->m_inputCursor];
		++state->m_inputCursor;
	}

	state->m_range = range;
	state->m_bitsRemaining = bitsRemaining;
	state->m_code = code;
	return bit;
}
