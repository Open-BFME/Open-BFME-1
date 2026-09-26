// Open-BFME5: clean C++ conversion of the retail three-field reset at
// 0x003500A0.

class Rva003500A0
{
public:
	Rva003500A0();

private:
	int m_first;
	int m_second;
	int m_third;
};

Rva003500A0::Rva003500A0()
{
	m_first = 0;
	m_second = -1;
	m_third = 0;
}
