// cl: /DNDEBUG /MD /EHsc

// Retail 0x000EC8C0 is an unnamed field helper: subtract the dword at +0x1D0
// from the dword at +0x1C8 and store the result back at +0x1C8.  The owner is
// intentionally left address-derived because the bytes provide no identity.
struct Rva000EC8C0SubtractField
{
	unsigned char m_unmodelled_000[0x1C8];
	int m_value;
	unsigned char m_unmodelled_1CC[4];
	int m_subtrahend;

	void subtractField();
};

void Rva000EC8C0SubtractField::subtractField()
{
	m_value -= m_subtrahend;
}
