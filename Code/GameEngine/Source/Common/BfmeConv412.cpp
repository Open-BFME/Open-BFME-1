extern "C" unsigned char bfmeEmptyANB[];
extern "C" unsigned char bfmeTagANB[];

class BfmeSlotANB
{
public:
	void bfmeSetANB(void *text, int flag);
	unsigned char m_bfmeHead[4];
};

class BfmeThingANB;

class BfmeSinkANB
{
public:
	void bfmeAddANB(BfmeThingANB *who, void *tag);
};

class BfmeThingANB
{
public:
	void bfmeFinishANB(BfmeSinkANB *sink, void *what);
	void bfmeInitANB(BfmeSinkANB *sink, void *what);
	unsigned char m_bfmeHead[0x18];
	BfmeSlotANB m_bfmeA;
	BfmeSlotANB m_bfmeB;
	int m_bfmeFlag;
};

void BfmeThingANB::bfmeInitANB(BfmeSinkANB *sink, void *what)
{
	m_bfmeA.bfmeSetANB(bfmeEmptyANB, 0);
	m_bfmeB.bfmeSetANB(bfmeEmptyANB, 0);
	m_bfmeFlag = 0;
	sink->bfmeAddANB(this, bfmeTagANB);
	bfmeFinishANB(sink, what);
}
