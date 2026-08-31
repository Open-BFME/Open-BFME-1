// ?apply@Rva008F9720MaskedRange@@QAE_NPAVRva008F9720Record@@0H@Z
// partial score=0.82 date=2026-08-31
// cl: /DNDEBUG /MD /EHsc

class Rva008F9720Record;

class Rva008F9720Target
{
public:
	void normalizeRange(
		Rva008F9720Record **firstOut,
		Rva008F9720Record **lastOut,
		Rva008F9720Record *first,
		Rva008F9720Record *last,
		int parameter);
};

class Rva008F9720Record
{
public:
	void applyMaskBit(Rva008F9720Target *target, int bit);

private:
	char m_data[0x68];
};

class Rva008F9720MaskedRange
{
public:
	bool apply(
		Rva008F9720Record *first,
		Rva008F9720Record *last,
		int parameter);

private:
	Rva008F9720Target *m_target;
	unsigned m_mask;
};

bool Rva008F9720MaskedRange::apply(
	Rva008F9720Record *first,
	Rva008F9720Record *last,
	int parameter)
{
	m_target->normalizeRange(&first, &last, first, last, parameter);

	unsigned mask = m_mask;
	for (int bit = 0; mask != 0; ++bit, mask >>= 1)
	{
		if ((mask & 1) != 0)
		{
			for (Rva008F9720Record *record = first; record != last; ++record)
				record->applyMaskBit(m_target, bit);
		}
	}
	return true;
}
