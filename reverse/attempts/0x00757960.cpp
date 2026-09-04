// ??0Rva007579F0Object@@QAE@XZ
// partial score=0.96 date=2026-09-02
// 0x00757960 -- constructor of Rva007579F0Object, whose destructor is already
// landed at 0x007579F0. Derived vftable first, then defaults in retail store
// order. Barriers stop MSVC grouping the shared-register stores.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Q3EhBaseOne
{
public:
	virtual void slot();
	int m_word;
};

class Q3EhMember000658A0
{
public:
	~Q3EhMember000658A0();

	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	unsigned int m_40;
	float m_44;
	unsigned int m_48;
	float m_4C;
	float m_50;
	float m_54;
	unsigned int m_58;
	unsigned int m_5C;
	unsigned int m_60;
	unsigned int m_64;
	int m_68;
	int m_6C;
	unsigned int m_70;
};

class Rva007579F0Object
{
public:
	Rva007579F0Object(void);
	virtual ~Rva007579F0Object(void);
	virtual void slot();

private:
	int m_word;
	int m_08;
	int m_0C;
	void *m_10;
	float m_14;
	unsigned int m_18;
	unsigned char m_1C;
	unsigned char m_pad1D[3];
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	Q3EhMember000658A0 m_sub;
};

// ??0Rva007579F0Object@@QAE@XZ
Rva007579F0Object::Rva007579F0Object(void)
{
	int zero = 0;
	int neg = -1;
	int one = -neg;
	float oneFloat = 1.0f;

	m_08 = neg;
	m_0C = neg;
	m_sub.m_2C = zero;
	m_sub.m_30 = zero;
	m_sub.m_34 = zero;
	m_sub.m_68 = neg;
	m_sub.m_6C = neg;
	m_sub.m_58 = zero;
	m_sub.m_70 = zero;
	_ReadWriteBarrier();
	m_sub.m_4C = oneFloat;
	m_sub.m_50 = oneFloat;
	m_sub.m_54 = oneFloat;
	m_sub.m_5C = one;
	m_sub.m_60 = one;
	m_sub.m_64 = one;
	m_14 = oneFloat;
	m_sub.m_44 = oneFloat;
	m_10 = (void *)zero;
	m_20 = one;
	m_24 = zero;
	m_28 = zero;
	m_18 = zero;
	m_1C = (unsigned char)zero;
	m_sub.m_38 = one;
	m_sub.m_3C = zero;
	m_sub.m_40 = zero;
	m_sub.m_48 = zero;
	_ReadWriteBarrier();
	m_sub.m_58 = zero;
	m_sub.m_70 = zero;
}
