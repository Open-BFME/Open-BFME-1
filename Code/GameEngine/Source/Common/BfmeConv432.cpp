extern "C" unsigned char bfmeTextOneAZB[];
extern "C" unsigned char bfmeTextTwoAZB[];

void bfmeStopAZB(int what);
void bfmeSendAZB(int what, void *one, void *two);

class BfmeThingAZB
{
public:
	void bfmeGoAZB(void *what);
	unsigned char m_bfmeHead[8];
	void *m_bfmeWhat;
	bool m_bfmeReady;
	bool m_bfmeOn;
};

void BfmeThingAZB::bfmeGoAZB(void *what)
{
	if (m_bfmeWhat != 0 && m_bfmeOn)
	{
		bfmeStopAZB(0);
		bfmeSendAZB(0, bfmeTextOneAZB, bfmeTextTwoAZB);
		m_bfmeWhat = 0;
		m_bfmeReady = false;
		m_bfmeOn = false;
	}
}
