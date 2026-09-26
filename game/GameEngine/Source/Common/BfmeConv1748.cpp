class BfmeSinkAY
{
public:
	void bfmeAddAY(int *slot, int flag);
};

class BfmeRangeAY
{
public:
	unsigned char m_bfmeHeadAY[0x14];
	int *m_bfmeBeginAY;
	int *m_bfmeEndAY;
};

class BfmeOwnAY
{
public:
	void bfmeFeedAY(BfmeSinkAY *sink);

	unsigned char m_bfmeHeadAY[4];
	BfmeRangeAY *m_bfmeRangeAY;
};

void BfmeOwnAY::bfmeFeedAY(BfmeSinkAY *sink)
{
	if (sink == 0)
		return;

	BfmeRangeAY *range = m_bfmeRangeAY;

	for (int *slot = range->m_bfmeBeginAY; slot != range->m_bfmeEndAY; ++slot)
		sink->bfmeAddAY(slot, -1);
}
