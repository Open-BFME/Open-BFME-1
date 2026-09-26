// cl: /O2 /Ob0

class Rva008F9340
{
	unsigned short m_words[1];

public:
	unsigned get(unsigned row, unsigned column) const;
};

unsigned Rva008F9340::get(unsigned row, unsigned column) const
{
	return m_words[3 * (row + 1) + column];
}
