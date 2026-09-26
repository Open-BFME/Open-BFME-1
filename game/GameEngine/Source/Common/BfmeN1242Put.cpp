// cl: /O2 /DNDEBUG /MD

class BfmeE1242
{
public:
	virtual void prepare() = 0;
	virtual void consume() = 0;
	virtual void unused08() = 0;
	virtual void unused0C() = 0;
	virtual void unused10() = 0;
	virtual unsigned char isTagged() = 0;
};

class BfmeN1242
{
public:
	void bfmePut1242(int i, BfmeE1242 *e);
	unsigned bfmeIsTagged(int i) const;
	BfmeE1242 *bfmeGetUntagged(int i) const;
	char m_bfmePad00[0x20];
	BfmeE1242 **m_bfme20;
};

void BfmeN1242::bfmePut1242(int i, BfmeE1242 *e)
{
	BfmeE1242 *old = reinterpret_cast<BfmeE1242 *>(
		reinterpret_cast<unsigned int>(m_bfme20[i]) & ~1u);

	e->prepare();
	if (old != 0)
		old->consume();
	if (e->isTagged() == 1)
		m_bfme20[i] = reinterpret_cast<BfmeE1242 *>(
			reinterpret_cast<unsigned int>(e) | 1u);
	else
		m_bfme20[i] = e;
}

// ?bfmeIsTagged@BfmeN1242@@QBEIH@Z
unsigned BfmeN1242::bfmeIsTagged(int i) const
{
	return reinterpret_cast<unsigned>(m_bfme20[i]) & 1u;
}

// ?bfmeGetUntagged@BfmeN1242@@QBEPAVBfmeE1242@@H@Z
BfmeE1242 *BfmeN1242::bfmeGetUntagged(int i) const
{
	return reinterpret_cast<BfmeE1242 *>(
		reinterpret_cast<unsigned>(m_bfme20[i]) & ~1u);
}
