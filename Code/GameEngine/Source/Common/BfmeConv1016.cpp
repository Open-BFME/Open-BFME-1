// Open-BFME5 conversions.

class BfmeSrc1016
{
public:
	virtual void bfmeVS01016();
	virtual void bfmeVS11016();
	virtual void bfmeVS21016();
	virtual void bfmeVS31016();
	virtual void bfmeVS41016();
	virtual void bfmeVS51016();
	virtual void bfmeVS61016();
	virtual void bfmeVS71016();
	virtual void bfmeVS81016();
	virtual void bfmeVS91016();
	virtual void bfmeVS101016();
	virtual void bfmeVS111016();
	virtual void bfmeVS121016();
	virtual void bfmeVS131016();
	virtual void bfmeVS141016();
	virtual void bfmeVS151016();
	virtual void bfmeVS161016();
	virtual void bfmeVS171016();
	virtual void bfmeVS181016();
	virtual void bfmeVS191016();
	virtual void bfmeVS201016();
	virtual void bfmeVS211016();
	virtual void bfmeVS221016();
	virtual void bfmeVS231016();
	virtual void bfmeVS241016();
	virtual void bfmeVS251016();
	virtual void bfmeVS261016();
	virtual void bfmeVS271016();
	virtual void bfmeVS281016();
	virtual void bfmeVS291016();
	virtual void bfmeVS301016();
	virtual void bfmeVS311016();
	virtual void bfmeVS321016();
	virtual void bfmeVS331016();
	virtual void bfmeVS341016();
	virtual void bfmeVS351016();
	virtual void bfmeVS361016();
	virtual void bfmeVS371016();
	virtual void bfmeVS381016();
	virtual void bfmeVS391016();
	virtual void bfmeVS401016();
	virtual void bfmeVS411016();
	virtual void bfmeVS421016();
	virtual void bfmeVS431016();
	virtual void bfmeVS441016();
	virtual void bfmeVS451016();
	virtual void bfmeVS461016();
	virtual void bfmeVS471016();
	virtual void bfmeVS481016();
	virtual void bfmeVS491016();
	virtual void bfmeVS501016();
	virtual void bfmeVS511016();
	virtual void bfmeVS521016();
	virtual void bfmeVS531016();
	virtual void bfmeVS541016();
	virtual void bfmeVS551016();
	virtual void bfmeVS561016();
	virtual int bfmeGet1016();
};

class BfmeDst1016
{
public:
	void bfmeSet1016(int a, int b, int r);
};

class BfmeQ1016
{
public:
	void bfmeGo1016Q(int a, int b);

	char m_bfmePad[0x84];
	BfmeSrc1016 *m_bfmeSrc;
	char m_bfmePad2[0x40];
	BfmeDst1016 *m_bfmeDst;
};

void BfmeQ1016::bfmeGo1016Q(int a, int b)
{
	int r = m_bfmeSrc != 0 ? m_bfmeSrc->bfmeGet1016() : 0;

	m_bfmeDst->bfmeSet1016(a, b, r);
}

class BfmeIter1016
{
public:
	unsigned short bfmeNext1016(int a);
};

class BfmeR1016
{
public:
	BfmeR1016 &bfmeGo1016R(int a);

	BfmeIter1016 *m_bfmeIt;
	char m_bfmeOk;
};

BfmeR1016 &BfmeR1016::bfmeGo1016R(int a)
{
	int ok;

	if (m_bfmeOk != 0 && m_bfmeIt->bfmeNext1016(a) != 0xffff)
		ok = 1;
	else
		ok = 0;

	m_bfmeOk = (char)ok;
	return *this;
}

struct BfmeNode1016
{
	char m_bfmePad[4];
	int m_bfmeCount;
	BfmeNode1016 *m_bfmeNext;
	BfmeNode1016 *m_bfmePrev;
};

class BfmeList1016
{
public:
	void bfmeErase1016(int n);

	BfmeNode1016 *m_bfmeHead;
	int m_bfmeSize;
};

extern BfmeList1016 g_bfmeList1016;

void bfmeGo1016T(void)
{
	if (g_bfmeList1016.m_bfmeSize != 0) {
		g_bfmeList1016.bfmeErase1016(g_bfmeList1016.m_bfmeHead->m_bfmeCount);
		g_bfmeList1016.m_bfmeHead->m_bfmeNext = g_bfmeList1016.m_bfmeHead;
		g_bfmeList1016.m_bfmeHead->m_bfmeCount = 0;
		g_bfmeList1016.m_bfmeHead->m_bfmePrev = g_bfmeList1016.m_bfmeHead;
		g_bfmeList1016.m_bfmeSize = 0;
	}
}
