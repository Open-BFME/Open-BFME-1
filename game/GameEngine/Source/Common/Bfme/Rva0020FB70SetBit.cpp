// cl: /DNDEBUG /MD /EHsc

class Rva0020FB70
{
public:
	void set(unsigned bit);

private:
	unsigned char m_unmodelled_000[0xc0];
	unsigned m_flags;
};

void Rva0020FB70::set(unsigned bit)
{
	m_flags |= 1u << (bit & 31);
}
