// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x000C90F0 (47 bytes).

class Rva000C90F0
{
public:
	void invertFields();

private:
	unsigned m_first;
	unsigned m_second;
	unsigned m_third;
	unsigned m_fourth;
	unsigned m_fifth;
	unsigned m_sixth;
};

void Rva000C90F0::invertFields()
{
	m_first = ~m_first;
	m_second = ~m_second;
	m_third = ~m_third;
	m_fourth = ~m_fourth;
	m_fifth = ~m_fifth;
	m_sixth = ~m_sixth;
}
