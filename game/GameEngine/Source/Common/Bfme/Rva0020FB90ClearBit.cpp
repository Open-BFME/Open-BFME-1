// cl: /DNDEBUG /MD /EHsc

class Rva0020FB90
{
public:
	void clear(unsigned bit);

private:
	unsigned char m_unmodelled_000[0xc0];
	unsigned m_flags;
};

void Rva0020FB90::clear(unsigned bit)
{
	m_flags &= ~(1u << (bit & 31));
}
