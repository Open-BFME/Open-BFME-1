// cl: /DNDEBUG /MD /EHsc

struct Rva00216AD0CompareField
{
	unsigned char m_unmodelled_000[0x3F8];
	unsigned int m_value;

	bool compare(unsigned int value);
};

bool Rva00216AD0CompareField::compare(unsigned int value)
{
	return m_value == value;
}
