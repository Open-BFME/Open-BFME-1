class BfmeThingHT
{
public:
	~BfmeThingHT();
};

class BfmeOwnerHT
{
public:
	void bfmeSetHT(BfmeThingHT *value);

	unsigned char m_bfmeHeadHT[0x12024];
	BfmeThingHT *m_bfmeThingHT;
};

void BfmeOwnerHT::bfmeSetHT(BfmeThingHT *value)
{
	if (m_bfmeThingHT != 0)
	{
		delete m_bfmeThingHT;
		m_bfmeThingHT = 0;
	}

	m_bfmeThingHT = value;
}
