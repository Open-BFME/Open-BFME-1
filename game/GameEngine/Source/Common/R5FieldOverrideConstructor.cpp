// Constructor used by the 0x0059CB30 INI parse helper.  The base layout is
// established by the matched constructor at 0x00489210; this derived object
// overrides four of those defaults and adds the sentinel at +0x20.

class Rva00489210
{
public:
	Rva00489210();
	int *m_00;
	int m_04;
	char m_08, m_09, m_0A;
	int m_0C;
};

class Rva0059CAC0 : public Rva00489210
{
public:
	Rva0059CAC0();
	int m_10, m_14, m_18, m_1C, m_20;
};

Rva0059CAC0::Rva0059CAC0()
{
	m_00 = reinterpret_cast<int *>( 0x0110C744 );
	m_04 = 8;
	m_0C = 0;
	m_20 = -1;
	m_09 = 1;
}
