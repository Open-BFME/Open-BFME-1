// cl: /DNDEBUG /MD /EHsc

struct Rva006BA130MaxField
{
	unsigned char m_unmodelled_000[0x3c];
	int m_limit;

	void update(int value);
};

void Rva006BA130MaxField::update(int value)
{
	if (value > m_limit)
		m_limit = value;
}
