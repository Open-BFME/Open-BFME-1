// cl: /DNDEBUG /MD
//
// Retail 0x00741830: thiscall constructor that zeroes the lead dword, copy-
// constructs a StringBase<char> at +4, copies a 12-byte record from the second
// argument, then stores six more dword arguments and a trailing zero byte.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	unsigned x;
	unsigned y;
	unsigned z;
};

class Rva00741830
{
public:
	Rva00741830(
		const AsciiString &name,
		const Coord3D &pos,
		unsigned a,
		unsigned b,
		unsigned c,
		unsigned e,
		unsigned f,
		unsigned d);

private:
	unsigned m_zero;
	AsciiString m_name;
	Coord3D m_pos;
	unsigned m_a;
	unsigned m_b;
	unsigned m_c;
	unsigned m_d;
	unsigned m_e;
	unsigned m_f;
	unsigned char m_flag;
};

Rva00741830::Rva00741830(
	const AsciiString &name,
	const Coord3D &pos,
	unsigned a,
	unsigned b,
	unsigned c,
	unsigned e,
	unsigned f,
	unsigned d)
	: m_zero(0), m_name(name)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_pos.z = pos.z;
	m_a = a;
	m_b = b;
	m_c = c;
	m_d = d;
	m_e = e;
	m_f = f;
	m_flag = 0;
}
