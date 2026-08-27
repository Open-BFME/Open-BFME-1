// Open-BFME: global-offset setter reconstructed from retail RVA 0x001B4980.

class Rva001B4980Global
{
public:
	char m_pad0[0x3C];
	int m_value;
};

class Rva001B4980Object
{
public:
	void set(int first, int second);

private:
	char m_pad0[0x58];
	int m_first;
	int m_second;
};

extern Rva001B4980Global *g_Rva001B4980Global;

void Rva001B4980Object::set(int first, int second)
{
	m_first = first;
	m_second = g_Rva001B4980Global->m_value + second;
}
