// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva007B8100Set
{
public:
	void set(unsigned int value);

	int m_00;
	int m_04;
	unsigned int m_08;
	int m_0c;
	unsigned int m_10;
};

void Rva007B8100Set::set(unsigned int value)
{
	m_08 = value;
	m_10 = 0;
}
