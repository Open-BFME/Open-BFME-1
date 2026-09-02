// ?d_007409a0@@YAXXZ
// partial score=0.97 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x007409A0: copy-assignment. On this != other, take a by-value string
// from the source via a getter, StringBase::set it onto the member at +0xC,
// destroy the temp, then copy four POD dwords at +0/+4/+8/+0x10.

class StringBase
{
public:
	StringBase(const StringBase &other);
	~StringBase();
	void set(const StringBase &other);

private:
	void *m_data;
};

class Rva007409A0
{
public:
	Rva007409A0 &operator=(const Rva007409A0 &other);
	StringBase getName() const;

private:
	unsigned m_0;
	unsigned m_4;
	unsigned m_8;
	StringBase m_name;
	unsigned m_10;
};

Rva007409A0 &Rva007409A0::operator=(const Rva007409A0 &other)
{
	if (this != &other)
	{
		m_name.set(other.getName());
		m_0 = other.m_0;
		m_4 = other.m_4;
		m_8 = other.m_8;
		m_10 = other.m_10;
	}
	return *this;
}
