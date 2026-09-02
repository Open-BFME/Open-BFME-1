class ClientFrameSubsystem
{
public:
	#define GEN_SLOT(n) virtual void slot##n();
	GEN_SLOT(00) GEN_SLOT(04) GEN_SLOT(08) GEN_SLOT(0C)
	GEN_SLOT(10) GEN_SLOT(14) GEN_SLOT(18) GEN_SLOT(1C)
	GEN_SLOT(20) GEN_SLOT(24) GEN_SLOT(28) GEN_SLOT(2C)
	GEN_SLOT(30) GEN_SLOT(34) GEN_SLOT(38) GEN_SLOT(3C)
	GEN_SLOT(40) GEN_SLOT(44) GEN_SLOT(48) GEN_SLOT(4C)
	GEN_SLOT(50) GEN_SLOT(54) GEN_SLOT(58) GEN_SLOT(5C)
	GEN_SLOT(60) GEN_SLOT(64)
	#undef GEN_SLOT
	virtual int getBase();
};

extern ClientFrameSubsystem *TheGameClientClientUpdate;

class Gen00459960
{
public:
	char m_pad00[0x38];
	int m_left;
	int m_right;
	int m_top;
	int m_bottom;
	int m_value48;
	int m_value4C;
	int m_value50;
	int m_value54;

	void setBounds( int a, int b, int c, int d, int e, int f, int g, int h );
};

void Gen00459960::setBounds( int a, int b, int c, int d, int e, int f, int g, int h )
{
	int base = TheGameClientClientUpdate->getBase();
	m_left = base + a;
	if( b == -1 )
		m_right = b;
	else
		m_right = base + b;
	m_top = c;
	m_bottom = m_left + d;
	m_value48 = e;
	if( f == -1 )
	{
		m_value4C = -1;
		m_value50 = g;
		m_value54 = h;
	}
	else
	{
		m_value4C = m_bottom + f;
		m_value50 = m_value4C + g;
		m_value54 = h;
	}
}
