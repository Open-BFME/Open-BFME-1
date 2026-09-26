class BfmeSubEVH;

class BfmeThingEVH
{
public:
	int m_bfmeHeadAEVH;
	BfmeSubEVH *m_bfmeSubEVH;
	unsigned char m_bfmePadEVH[0x414];
	int m_bfmeDeltaEVH;
};

class BfmeArgEVH
{
public:
	int m_bfmeHeadEVH;
	BfmeThingEVH *m_bfmeThingEVH;
};

class BfmeSinkEVH
{
public:
	void bfmeNotifyEVH(bool flag);
};

BfmeThingEVH *__fastcall bfmeResolveEVH(BfmeSubEVH *sub);

class BfmeHostEVH
{
public:
	void bfmeAdvanceEVH(BfmeArgEVH *arg);

	int m_bfmeHeadEVH;
	int m_bfmeValueEVH;
	int m_bfmeLimitEVH;
	BfmeSinkEVH *m_bfmeSinkEVH;
};

void BfmeHostEVH::bfmeAdvanceEVH(BfmeArgEVH *arg)
{
	if (arg == 0)
		return;

	BfmeThingEVH *thing = arg->m_bfmeThingEVH;

	if (thing != 0 && thing->m_bfmeSubEVH != 0)
		thing = bfmeResolveEVH(thing->m_bfmeSubEVH);

	m_bfmeValueEVH = m_bfmeValueEVH + thing->m_bfmeDeltaEVH;

	if (m_bfmeSinkEVH != 0)
		m_bfmeSinkEVH->bfmeNotifyEVH(m_bfmeValueEVH < m_bfmeLimitEVH);
}
