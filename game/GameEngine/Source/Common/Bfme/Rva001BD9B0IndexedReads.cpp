// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery for identical 0x001BD9B0 and 0x001BD9C0 reads.

class Rva001BD9B0
{
public:
	unsigned value() const;

private:
	unsigned char m_unmodelled_000[0x08];
	unsigned m_values[4];
	unsigned m_index;
};

class Rva001BD9C0
{
public:
	unsigned value() const;

private:
	unsigned char m_unmodelled_000[0x08];
	unsigned m_values[4];
	unsigned m_index;
};

unsigned Rva001BD9B0::value() const
{
	return m_values[m_index];
}

unsigned Rva001BD9C0::value() const
{
	return m_values[m_index];
}
