// cl: /DNDEBUG /MD /EHsc

class Rva0020FAA0
{
public:
	int mark();

private:
	unsigned char m_unmodelled_000[0x38];
	int m_value;
	unsigned char m_unmodelled_03c[0x5a];
	unsigned char m_marked;
};

int Rva0020FAA0::mark()
{
	if (m_marked != 0)
		return 0;
	m_marked = 1;
	return m_value;
}
