// VP6 arithmetic bit decoder called directly by the verified motion-vector
// decoder at 0x009B5200. Full retail boundary [0x009B4600,0x009B4672).
// This copy updates the bit count only after renormalization; the separate
// 0x009B4800 implementation has a different assignment/scheduling shape.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva009B4600State
{
	unsigned char m_pad0[4];
	unsigned m_range;
	unsigned m_code;
	int m_bitsRemaining;
	unsigned m_inputCursor;
	const unsigned char *m_inputBase;
};

int Rva009B4600DecodeBool(void *rawState, int probability)
{
	Rva009B4600State *state = (Rva009B4600State *)rawState;
	unsigned oldRange = state->m_range;
	unsigned range = ((oldRange - 1) * probability) >> 8;
	int bitsRemaining = state->m_bitsRemaining;
	unsigned code = state->m_code;
	int bit = 0;
	++range;
	unsigned threshold = range << 24;
	if (code >= threshold) {
		range = oldRange - range;
		code -= threshold;
		bit = 1;
	}
	if (range < 0x80) {
		do {
			range += range;
			code += code;
			if (--bitsRemaining == 0) {
				code |= state->m_inputBase[state->m_inputCursor];
				bitsRemaining = 8;
				++state->m_inputCursor;
			}
		} while (range < 0x80);
		state->m_bitsRemaining = bitsRemaining;
	}
	state->m_code = code;
	state->m_range = range;
	return bit;
}
