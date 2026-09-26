struct BfmeSlotBTE
{
	void **bfmeMakeBTE(void *what);
	unsigned char m_bfmeHead[12];
};

class BfmeThingBTE
{
public:
	void bfmeGoBTE(int at, void *what, void *out);
	unsigned char m_bfmeHead[0x170e0];
	BfmeSlotBTE m_bfmeSlots[1];
};

void BfmeThingBTE::bfmeGoBTE(int at, void *what, void *out)
{
	void **got = m_bfmeSlots[at].bfmeMakeBTE(what);
	*got = out;
}
