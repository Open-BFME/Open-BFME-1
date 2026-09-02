// ??0Rva004E9FD0@@QAE@ABV0@@Z
// partial score=0.82 date=2026-09-02
// cl: /O2 /Ob0 /EHsc
//
// Retail 0x004E9FD0: copy ctor of the 0x1C object whose assign is
// Rva004E9B70.  Dword, three StringBase<char> members, dword, two
// StringBase<wchar> members, with per-member unwind cookies.

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str();

private:
	void *m_item;
};

class Rva00630D00UStr
{
public:
	Rva00630D00UStr(const Rva00630D00UStr &other);
	~Rva00630D00UStr();

private:
	void *m_item;
};

class Rva004E9FD0
{
	int m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	int m_10;
	Rva00630D00UStr m_14;
	Rva00630D00UStr m_18;

public:
	Rva004E9FD0(const Rva004E9FD0 &other);
};

// ??0Rva004E9FD0@@QAE@ABV0@@Z
Rva004E9FD0::Rva004E9FD0(const Rva004E9FD0 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0C(other.m_0C)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_18(other.m_18)
{
}
