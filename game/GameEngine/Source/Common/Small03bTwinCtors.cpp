// Retail 0x00933860 and 0x00933940 are byte-identical 20-byte default
// constructors: three members zeroed and the fourth set to 0x10.  The
// owning class is not identified (neighbours are Render2D raw-array
// growth and vtable-pointer free wrappers), so both names keep their
// address token.
class Rva00933860Box
{
public:
	Rva00933860Box();
	int m_0;
	int m_4;
	int m_8;
	int m_c;
};
Rva00933860Box::Rva00933860Box() : m_0(0), m_4(0), m_8(0), m_c(0x10) {}
class Rva00933940Box
{
public:
	Rva00933940Box();
	int m_0;
	int m_4;
	int m_8;
	int m_c;
};
Rva00933940Box::Rva00933940Box() : m_0(0), m_4(0), m_8(0), m_c(0x10) {}
