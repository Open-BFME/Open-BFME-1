// cl: /Od
// A byte put at a place: appended when the place is the end, otherwise handed
// to the inserter. Built without optimisation; the frame holds more than this
// body names. Both callees are pinned by address.

class BfmeThingQI
{
public:
	char *bfmeSetQI(char *at, unsigned char one);

	void bfmePushQI(unsigned char one);

	char *bfmeInsertQI(char *at, unsigned char one);

	unsigned char m_bfmeHead[4];		// 0x0
	char *m_bfmeEnd;			// 0x4
};

char *BfmeThingQI::bfmeSetQI(char *at, unsigned char one)
{
	unsigned char spare[0x14];

	char *end = m_bfmeEnd;

	if (at == end)
	{
		bfmePushQI(one);

		return m_bfmeEnd - 1;
	}

	return bfmeInsertQI(at, one);
}
