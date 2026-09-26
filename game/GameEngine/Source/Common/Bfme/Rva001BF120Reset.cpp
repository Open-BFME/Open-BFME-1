// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001BF120 (18 bytes).

class Rva001BF120
{
public:
	void reset();

private:
	unsigned char m_unmodelled_000[0x3A8];
	unsigned char m_flag;
	unsigned m_value;
};

void Rva001BF120::reset()
{
	m_flag = 0;
	m_value = static_cast<unsigned>(-1);
}
