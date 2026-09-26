// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x009A2960 (29 bytes).

class Rva009A2960
{
public:
	void markState();

private:
	unsigned char m_unmodelled_000[0xC068];
	unsigned m_state;
	unsigned char m_flag;
};

void Rva009A2960::markState()
{
	if (m_state != 2)
	{
		m_state = 2;
		m_flag = 1;
	}
}
