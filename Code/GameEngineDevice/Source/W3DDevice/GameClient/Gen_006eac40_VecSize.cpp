// cl: /DNDEBUG /MD /EHsc

// Retail 0x006EAC40. return (m_end - m_begin) for 56-byte elements.

struct Gen_006eac40_Elem
{
	unsigned char m[56];
};

class Gen_006eac40
{
public:
	int size(void) const;

private:
	Gen_006eac40_Elem *m_begin;
	Gen_006eac40_Elem *m_end;
};

// ?size@Gen_006eac40@@QBEHXZ
int Gen_006eac40::size(void) const
{
	return m_end - m_begin;
}
