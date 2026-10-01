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

// retail resolves the sub-object's final override through the ILT thunk at
// 0x000022BB, which targets Overridable::getFinalOverride (matching row
// 0x00087A80).  Spelled with its defining class and signature so the call
// links; the view classes below stay unrelated to it, the pointer crosses as
// void so no code is emitted.
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

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
		thing = (BfmeThingEVI *)(const void *)((const Overridable *)thing->m_bfmeSubEVI)->getFinalOverride();

	m_bfmeValueEVI = m_bfmeValueEVI - thing->m_bfmeDeltaEVI;

	if (m_bfmeSinkEVI != 0)
		m_bfmeSinkEVI->bfmeNotifyEVI(m_bfmeValueEVI < m_bfmeLimitEVI);
}
