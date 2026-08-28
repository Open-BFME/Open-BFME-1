struct BfmeOwnerRK
{
	unsigned char m_bfmeHead[0xc4];
	bool m_bfmeForce;
};

class BfmeThingRK
{
public:
	void bfmeFirstRK();
	void bfmeSecondRK();
	void bfmeGoRK();
	unsigned char m_bfmeHead[4];
	BfmeOwnerRK *m_bfmeOwner;
	unsigned char m_bfmeGap[0x34];
	bool m_bfmeWant;
	bool m_bfmeDone;
};

void BfmeThingRK::bfmeGoRK()
{
	bfmeFirstRK();
	if (m_bfmeDone)
		return;
	if (m_bfmeOwner->m_bfmeForce || m_bfmeWant)
		bfmeSecondRK();
}
