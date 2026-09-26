// cl: /O2 /Ob0

class Rva000D0110
{
	unsigned m_bits[1];

public:
	void clear(unsigned bit);
};

void Rva000D0110::clear(unsigned bit)
{
	m_bits[bit >> 5] &= ~(1u << (bit & 31));
}
