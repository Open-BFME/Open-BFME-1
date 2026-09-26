// cl: /O2 /Ob0

class Rva00647920String
{
public:
	Rva00647920String(const Rva00647920String &other);

private:
	char m_pad[0x0C];
};

class Rva00770220
{
	int m_00;
	Rva00647920String m_04;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;

public:
	Rva00770220(const Rva00770220 &other);
};

Rva00770220::Rva00770220(const Rva00770220 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_18(other.m_18)
	, m_1C(other.m_1C)
{
}
