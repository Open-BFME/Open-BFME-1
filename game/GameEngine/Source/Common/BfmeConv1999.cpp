class BfmeSubEVI;

class BfmeThingEVI
{
public:
	int m_bfmeHeadAEVI;
	BfmeSubEVI *m_bfmeSubEVI;
	unsigned char m_bfmePadEVI[0x414];
	int m_bfmeDeltaEVI;
};

class BfmeArgEVI
{
public:
	int m_bfmeHeadEVI;
	BfmeThingEVI *m_bfmeThingEVI;
};

class BfmeSinkEVI
{
public:
	void bfmeNotifyEVI(bool flag);
};

BfmeThingEVI *__fastcall bfmeResolveEVI(BfmeSubEVI *sub);

class BfmeHostEVI
{
public:
	void bfmeAdvanceEVI(BfmeArgEVI *arg);

	int m_bfmeHeadEVI;
	int m_bfmeValueEVI;
	int m_bfmeLimitEVI;
	BfmeSinkEVI *m_bfmeSinkEVI;
};

void BfmeHostEVI::bfmeAdvanceEVI(BfmeArgEVI *arg)
{
	if (arg == 0)
		return;

	BfmeThingEVI *thing = arg->m_bfmeThingEVI;

	if (thing != 0 && thing->m_bfmeSubEVI != 0)
		thing = bfmeResolveEVI(thing->m_bfmeSubEVI);

	m_bfmeValueEVI = m_bfmeValueEVI - thing->m_bfmeDeltaEVI;

	if (m_bfmeSinkEVI != 0)
		m_bfmeSinkEVI->bfmeNotifyEVI(m_bfmeValueEVI < m_bfmeLimitEVI);
}
