// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x00422380 (31 bytes).

class Rva00422380
{
public:
	int stateAllows();

private:
	unsigned char m_unmodelled_000[0x38];
	unsigned char m_flags;
	unsigned char m_unmodelled_039[0x4B];
	unsigned m_state;
};

int Rva00422380::stateAllows()
{
	if (m_state != 3)
	{
		if (m_state != 2)
			return 0;
		if (!(m_flags & 2))
			return 0;
	}
	return 1;
}
