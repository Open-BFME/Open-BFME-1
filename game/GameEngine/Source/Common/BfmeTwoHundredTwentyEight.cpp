// Two errands: a newcomer written into the next free record and told to go
// before its six words are copied in beside it, and a pair of counts stepped
// down with the sub-part let go of when the second runs out.

struct BfmeDataLI
{
	int m_bfmeWords[6];			// 0x00
};

class BfmeItemLI
{
public:
	virtual void bfmeDoLI(void) = 0;
};

struct BfmeRecLI
{
	BfmeItemLI *m_bfmeItem;			// 0x00
	BfmeDataLI m_bfmeData;			// 0x04
};

class BfmeThingLI
{
public:
	void bfmeAddLI(BfmeItemLI *item, const BfmeDataLI *data);

private:
	unsigned char m_bfmeHead[0x818];	// 0x000
	int m_bfmeCount;			// 0x818
	BfmeRecLI *m_bfmeRecs;			// 0x81c
};

void BfmeThingLI::bfmeAddLI(BfmeItemLI *item, const BfmeDataLI *data)
{
	m_bfmeRecs[m_bfmeCount].m_bfmeItem = item;

	item->bfmeDoLI();

	m_bfmeRecs[m_bfmeCount].m_bfmeData = *data;

	++m_bfmeCount;
}


