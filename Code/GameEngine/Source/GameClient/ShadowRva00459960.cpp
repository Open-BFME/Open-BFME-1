// Retail 0x00459960. The DynamicDecal caller 0x00429080 passes the same
// unadjusted receiver to Shadow::setOpacity and this method. The virtual
// GameClient call is getFrame (slot +0x68), so these are frame-relative values,
// not geometric bounds. The original method and field spellings are unknown.
// This view ends at +0x58 and does not describe Shadow's complete extent.

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
	virtual unsigned int getFrame();
};

extern ClientFrameSubsystem *TheGameClientClientUpdate;

class Shadow
{
public:
	char m_pad00[0x38];
	int m_value38;
	int m_value3C;
	int m_value40;
	int m_value44;
	int m_value48;
	int m_value4C;
	int m_value50;
	int m_value54;

	void rva00459960( int offset38, int offset3C, int value40, int offset44, int value48, int offset4C, int offset50, int value54 );
};

void Shadow::rva00459960( int offset38, int offset3C, int value40, int offset44, int value48, int offset4C, int offset50, int value54 )
{
	int currentFrame = TheGameClientClientUpdate->getFrame();
	m_value38 = currentFrame + offset38;
	if( offset3C == -1 )
		m_value3C = offset3C;
	else
		m_value3C = currentFrame + offset3C;
	m_value40 = value40;
	m_value44 = m_value38 + offset44;
	m_value48 = value48;
	if( offset4C == -1 )
	{
		m_value4C = -1;
		m_value50 = offset50;
		m_value54 = value54;
	}
	else
	{
		m_value4C = m_value44 + offset4C;
		m_value50 = m_value4C + offset50;
		m_value54 = value54;
	}
}
