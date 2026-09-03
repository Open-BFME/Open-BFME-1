// ??0GenBase002DF2B0@@QAE@XZ
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GenBase002DF2B0 constructor, retail 0x002DF2B0, 138 bytes.
// Zeros the 19 dwords from +4 through +0x4C, constructs the 4-byte string
// member at +0x50, and clears the flag at +0x54.

class RS_Member
{
public:
	RS_Member();
	~RS_Member();

private:
	void *m_data;
};

class Guard4
{
public:
	Guard4() { m = 0; }
	~Guard4();
	int m;
};

class GenBase002DF2B0
{
public:
	GenBase002DF2B0();
	virtual void slot();

private:
	Guard4 m_04;
	int m_08, m_0c, m_10, m_14, m_18;
	int m_1c, m_20, m_24, m_28, m_2c, m_30;
	int m_34, m_38, m_3c, m_40, m_44, m_48, m_4c;
	RS_Member m_50;
	char m_54;
};

// ??0GenBase002DF2B0@@QAE@XZ
GenBase002DF2B0::GenBase002DF2B0()
	: m_08(0), m_0c(0), m_10(0), m_14(0), m_18(0)
	, m_1c(0), m_20(0), m_24(0), m_28(0), m_2c(0), m_30(0)
	, m_34(0), m_38(0), m_3c(0), m_40(0), m_44(0), m_48(0), m_4c(0)
{
	m_54 = 0;
}
