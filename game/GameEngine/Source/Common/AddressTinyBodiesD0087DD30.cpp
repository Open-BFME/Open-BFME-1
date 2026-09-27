// cl: /O2 /DNDEBUG /MD /EHsc
// Address-derived owners for small bodies formerly in gen_asm d_0087dd30.asm.
// No caller, vtable or string names them; members describe only the bytes.

struct Rva0087DD80Triple
{
	int m_a;
	int m_b;
	int m_c;
};

// 0x0087DD30: byte +1 greater than the argument
class Rva0087DD30Body
{
public:
	bool body(int value) const;

private:
	unsigned char m_byte0;
	unsigned char m_byte1;
};

// ?body@Rva0087DD30Body@@QBE_NH@Z
bool Rva0087DD30Body::body(int value) const
{
	return m_byte1 > value;
}

// 0x0087DD80 / 0x0087DDA0: copy a three-dword value into +0x44 / +0x50
class Rva0087DD80Body
{
public:
	void setAt44(const Rva0087DD80Triple &v);
	void setAt50(const Rva0087DD80Triple &v);

private:
	char m_pad[0x44];
	Rva0087DD80Triple m_at44;
	Rva0087DD80Triple m_at50;
};

// ?setAt44@Rva0087DD80Body@@QAEXABURva0087DD80Triple@@@Z
void Rva0087DD80Body::setAt44(const Rva0087DD80Triple &v)
{
	m_at44 = v;
}

// ?setAt50@Rva0087DD80Body@@QAEXABURva0087DD80Triple@@@Z
void Rva0087DD80Body::setAt50(const Rva0087DD80Triple &v)
{
	m_at50 = v;
}

// 0x0087EB80: default ctor; 0, three 1.0f, four zeros, flag 1
class Rva0087EB80Record
{
public:
	Rva0087EB80Record();

	int m_zero0;
	float m_one4;
	float m_one8;
	float m_oneC;
	int m_zero10;
	int m_zero14;
	int m_zero18;
	int m_zero1C;
	bool m_flag20;
};

// ??0Rva0087EB80Record@@QAE@XZ
Rva0087EB80Record::Rva0087EB80Record()
	: m_zero0(0), m_one4(1.0f), m_one8(1.0f), m_oneC(1.0f),
	  m_zero10(0), m_zero14(0), m_zero18(0), m_zero1C(0), m_flag20(true)
{
}
