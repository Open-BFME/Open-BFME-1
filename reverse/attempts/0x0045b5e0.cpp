// ?read@Gen0045B5E0@@QAEXPAX@Z
// partial score=0.72 date=2026-09-02
struct Gen0045B5E0Output
{
	bool m_valid;
	char m_pad01[3];
	int m_value04;
	float m_value08;
	float m_value0C;
	float m_value10;
	float m_value14;
	float m_value18;
	float m_value1C;
};

class Gen0045B5E0
{
public:
	#define GEN_SLOT(n) virtual void slot##n();
	GEN_SLOT(00) GEN_SLOT(04) GEN_SLOT(08) GEN_SLOT(0C)
	GEN_SLOT(10) GEN_SLOT(14) GEN_SLOT(18) GEN_SLOT(1C)
	GEN_SLOT(20) GEN_SLOT(24) GEN_SLOT(28) GEN_SLOT(2C)
	GEN_SLOT(30) GEN_SLOT(34) GEN_SLOT(38) GEN_SLOT(3C)
	GEN_SLOT(40) GEN_SLOT(44) GEN_SLOT(48) GEN_SLOT(4C)
	GEN_SLOT(50) GEN_SLOT(54) GEN_SLOT(58) GEN_SLOT(5C)
	GEN_SLOT(60) GEN_SLOT(64) GEN_SLOT(68) GEN_SLOT(6C)
	GEN_SLOT(70) GEN_SLOT(74) GEN_SLOT(78) GEN_SLOT(7C)
	GEN_SLOT(80) GEN_SLOT(84) GEN_SLOT(88) GEN_SLOT(8C)
	GEN_SLOT(90) GEN_SLOT(94) GEN_SLOT(98) GEN_SLOT(9C)
	GEN_SLOT(A0) GEN_SLOT(A4) GEN_SLOT(A8) GEN_SLOT(AC)
	GEN_SLOT(B0) GEN_SLOT(B4) GEN_SLOT(B8) GEN_SLOT(BC)
	GEN_SLOT(C0) GEN_SLOT(C4) GEN_SLOT(C8) GEN_SLOT(CC)
	GEN_SLOT(D0) GEN_SLOT(D4) GEN_SLOT(D8) GEN_SLOT(DC)
	GEN_SLOT(E0) GEN_SLOT(E4) GEN_SLOT(E8) GEN_SLOT(EC)
	GEN_SLOT(F0) GEN_SLOT(F4) GEN_SLOT(F8)
	#undef GEN_SLOT
	virtual float getFC();
	virtual void slot100();
	virtual float get104();
	virtual void slot108();
	virtual float get10C();
	virtual void slot110(); virtual void slot114(); virtual void slot118(); virtual void slot11C();
	virtual float get120();

	int m_value04;
	int m_value08;
	int m_value0C;
	float m_value10;
	float m_value14;

	void read( void *output );
};

void Gen0045B5E0::read( void *output )
{
	unsigned char *raw = (unsigned char *)output;
	float a = get10C();
	float b = get120();
	float c = get104();
	float d = getFC();
	*(float *)( raw + 0x08 ) = m_value10;
	*(int *)( raw + 0x04 ) = m_value0C;
	*(float *)( raw + 0x0C ) = m_value14;
	*(float *)( raw + 0x14 ) = c;
	*(float *)( raw + 0x10 ) = d;
	*(float *)( raw + 0x18 ) = b;
	*(float *)( raw + 0x1C ) = a;
	*raw = true;
}
