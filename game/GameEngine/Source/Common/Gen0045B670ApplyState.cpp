struct Gen0045B670Triple
{
	int m_first;
	int m_second;
	int m_third;
};

struct Gen0045B670Input
{
	bool m_enabled;
	char m_pad01[3];
	Gen0045B670Triple m_triple;
	int m_value10;
	int m_value14;
	int m_value18;
	int m_value1C;
};

class Gen0045B670
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
	GEN_SLOT(F0) GEN_SLOT(F4)
	#undef GEN_SLOT
	virtual void set10( int );
	virtual void slotFC();
	virtual void set14( int );
	virtual void slot104();
	virtual void set1C( int );
	virtual void slot10C(); virtual void slot110();
	virtual void slot114(); virtual void slot118(); virtual void slot11C(); virtual void slot120();
	virtual void set18( int );

	char m_pad04[8];
	Gen0045B670Triple m_triple;

	void apply( Gen0045B670Input *input );
};

void Gen0045B670::apply( Gen0045B670Input *input )
{
	if( input->m_enabled )
	{
		m_triple = input->m_triple;
		set10( input->m_value10 );
		set14( input->m_value14 );
		set1C( input->m_value1C );
		set18( input->m_value18 );
		slot50();
	}
}
