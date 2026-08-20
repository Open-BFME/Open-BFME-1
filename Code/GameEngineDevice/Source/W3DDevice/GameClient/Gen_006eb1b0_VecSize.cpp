// cl: /DNDEBUG /MD /EHsc

// Retail 0x006EB1B0. return (m_end - m_begin) >> 2.

class Gen_006eb1b0
{
public:
	int size(void) const;

private:
	unsigned char m_pad[0x14];
	int *m_begin;
	int *m_end;
};

// ?size@Gen_006eb1b0@@QBEHXZ
int Gen_006eb1b0::size(void) const
{
	return m_end - m_begin;
}
