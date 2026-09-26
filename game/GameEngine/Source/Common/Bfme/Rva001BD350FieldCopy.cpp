// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001BD350 (10 bytes).

class Rva001BD350
{
public:
	void copy();

private:
	unsigned char m_unmodelled_000[0x3C];
	unsigned m_source;
	unsigned char m_unmodelled_040[0x12C];
	unsigned m_destination;
};

void Rva001BD350::copy()
{
	m_destination = m_source;
}
