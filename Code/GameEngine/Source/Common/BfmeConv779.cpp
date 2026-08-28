struct BfmeThingDTI
{
	float bfmeGoDTI();
	void bfmeUpdDTI();
	unsigned char m_bfmeHead[0xc];
	float m_bfmeVal;
	char m_bfmeFlag;
};

float BfmeThingDTI::bfmeGoDTI()
{
	if (m_bfmeFlag)
		bfmeUpdDTI();
	return m_bfmeVal;
}

struct BfmeThingDTJ
{
	float bfmeGoDTJ();
	void bfmeUpdDTJ();
	unsigned char m_bfmeHead[0x2c];
	float m_bfmeVal;
	char m_bfmeFlag;
};

float BfmeThingDTJ::bfmeGoDTJ()
{
	if (m_bfmeFlag)
		bfmeUpdDTJ();
	return m_bfmeVal;
}
