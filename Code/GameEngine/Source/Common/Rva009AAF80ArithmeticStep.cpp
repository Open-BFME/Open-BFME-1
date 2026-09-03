// Open-BFME5 conversion of the arithmetic decoder normalization step.

struct Rva009AAF80State
{
	unsigned char m_pad0[4];
	unsigned m_range;
	unsigned m_code;
	int m_bitsRemaining;
	unsigned m_inputCursor;
	const unsigned char *m_inputBase;

	int step(void);
};

int Rva009AAF80State::step(void)
{
	unsigned code = m_code;
	int bitsRemaining = m_bitsRemaining;
	unsigned range = m_range;
	unsigned half = (range + 1) >> 1;
	unsigned threshold = half << 24;
	int bit;

	bit = (code >= threshold);
	range = bit ? range - half : half;
	code = bit ? code - threshold : code;
	range += range;
	code += code;

	if (--bitsRemaining == 0) {
		bitsRemaining = 8;
		code |= m_inputBase[m_inputCursor];
		++m_inputCursor;
	}

	m_range = range;
	m_bitsRemaining = bitsRemaining;
	m_code = code;
	return bit;
}
