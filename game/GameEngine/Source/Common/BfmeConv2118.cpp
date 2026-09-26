int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadAAI[0x3c];
	int m_bfme3CAAI;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

struct BfmeAIDataAAI
{
	unsigned char m_bfmeHeadDAAI[0x40];
	int m_bfme40AAI;
};

class AI
{
public:
	unsigned char m_bfmeHeadAAAI[0x14];
	BfmeAIDataAAI *m_bfme14AAI;
};

extern AI *TheAI;

class BfmeRes920D
{
public:
	virtual void bfmeSlot0AAI();
	virtual void bfmeSlot1AAI();
	virtual void bfmeSlot2AAI();
	virtual void bfmeSlot3AAI();
	virtual void bfmeSlot4AAI();
	virtual void bfmeSlot5AAI();
	virtual void bfmeSlot6AAI();
	virtual void bfmeSlot7AAI();
	virtual void bfmeSlot8AAI();
	virtual void bfmeSlot9AAI();
	virtual void bfmeSlot10AAI();
	virtual void bfmeSlot11AAI();
	virtual void bfmeSlot12AAI();
	virtual void bfmeSlot13AAI();
	virtual void bfmeSlot14AAI();
	virtual void bfmeSlot15AAI();
	virtual void bfmeSlot16AAI();
	virtual void bfmeSlot17AAI();
	virtual void bfmeSlot18AAI();
	virtual void bfmeSlot19AAI();
	virtual void bfmeSlot20AAI();
	virtual void bfmeSlot21AAI();
	virtual void bfmeSlot22AAI();
	virtual void bfmeSlot23AAI();
	virtual void bfmeSlot24AAI();
	virtual void bfmeSlot25AAI();
	virtual void bfmeSlot26AAI();
	virtual void bfmeSlot27AAI();
	virtual void bfmeSlot28AAI();
	virtual void bfmeSlot29AAI();
	virtual void bfmeSlot30AAI();
	virtual void bfmeSlot31AAI();
	virtual void bfmeSlot32AAI();
	virtual void bfmeSlot33AAI();
	virtual void bfmeSlot34AAI();
	virtual void bfmeSlot35AAI();
	virtual void bfmeSlot36AAI();
	virtual void bfmeSlot37AAI();
	virtual void bfmeSlot38AAI();
	virtual void bfmeSlot39AAI();
	virtual void bfmeSlot40AAI();
	virtual void bfmeSlot41AAI();
	virtual void bfmeSlot42AAI();
	virtual void bfmeSlot43AAI();
	virtual void bfmeSlot44AAI();
	virtual void bfmeSlot45AAI();
	virtual void bfmeSlot46AAI();
	virtual void bfmeSlot47AAI();
	virtual void bfmeSlot48AAI();
	virtual void bfmeSlot49AAI();
	virtual void bfmeSlot50AAI();
	virtual void bfmeSlot51AAI();
	virtual void bfmeSlot52AAI();
	virtual void bfmeSlot53AAI();
	virtual void bfmeSlot54AAI();
	virtual void bfmeSlot55AAI();
	virtual void bfmeSlot56AAI();
	virtual void bfmeSlot57AAI();
	virtual void bfmeSlot58AAI();
	virtual void bfmeSlot59AAI();
	virtual void bfmeSlot60AAI();
	virtual void bfmeSlot61AAI();
	virtual void bfmeSlot62AAI();
	virtual void bfmeSlot63AAI();
	virtual void bfmeSlot64AAI();
	virtual void bfmeSlot65AAI();
	virtual void bfmeSlot66AAI();
	virtual void bfmeSlot67AAI();
	virtual void bfmeSlot68AAI();
	virtual void bfmeSlot69AAI();
	virtual void bfmeSlot70AAI();
	virtual void bfmeSlot71AAI();
	virtual void bfmeSlot72AAI();
	virtual void bfmeSlot73AAI();
	virtual void bfmeSlot74AAI();
	virtual void bfmeSlot75AAI();
	virtual void bfmeSlot76AAI();
	virtual void bfmeSlot77AAI();
	virtual void bfmeSlot78AAI();
	virtual void bfmeSlot79AAI();
	virtual void bfmeSlot80AAI();
	virtual void bfmeSlot81AAI();
	virtual void bfmeSlot82AAI();
	virtual void bfmeSlot83AAI();
	virtual void bfmeSlot84AAI();
	virtual void bfmeSlot85AAI();
	virtual void bfmeSlot86AAI();
	virtual void bfmeSlot87AAI();
	virtual void bfmeSlot88AAI();
	virtual void bfmeSlot89AAI();
	virtual void bfmeSlot90AAI();
	virtual void bfmeSlot91AAI();
	virtual void bfmeSlot92AAI();
	virtual void bfmeSlot93AAI();
	virtual void bfmeSlot94AAI();
	virtual void bfmeSlot95AAI();
	virtual void bfmeSlot96AAI();
	virtual void bfmeSlot97AAI();
	virtual void bfmeSlot98AAI();
	virtual void bfmeSlot99AAI();
	virtual void bfmeSlot100AAI();
	virtual void bfmeSlot101AAI();
	virtual void bfmeSlot102AAI();
	virtual void bfmeSlot103AAI();
	virtual void bfmeSlot104AAI();
	virtual void bfmeSlot105AAI();
	virtual void bfmeSlot106AAI();
	virtual void bfmeSlot107AAI();
	virtual void bfmeSlot108AAI();
	virtual void bfmeSlot109AAI();
	virtual void bfmeSlot110AAI();
	virtual void bfmeSlot111AAI();
	virtual void bfmeSlot112AAI();
	virtual void bfmeSlot113AAI();
	virtual void bfmeSlot114AAI();
	virtual void bfmeSlot115AAI();
	virtual void bfmeSlot116AAI();
	virtual void bfmeSlot117AAI();
	virtual void bfmeActAAI();
};

class BfmeX920D
{
public:
	BfmeRes920D *bfmeGet920D();
};

struct BfmeOwnerAAI
{
	unsigned char m_bfmeHeadOAAI[0x10];
	BfmeX920D *m_bfme10AAI;
};

class BfmeGuardAAI
{
public:
	int bfmeUpdateAAI();

	unsigned char m_bfmeHeadGAAI[0x1c];
	BfmeOwnerAAI *m_bfme1CAAI;
	unsigned char m_bfmeGapAAI[4];
	int m_bfme24AAI;
};

int BfmeGuardAAI::bfmeUpdateAAI()
{
	int frame = TheBfmeGameLogic->m_bfme3CAAI;
	BfmeAIDataAAI *d = TheAI->m_bfme14AAI;

	m_bfme24AAI = frame
		+ GetGameLogicRandomValue(0, d->m_bfme40AAI,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIGuard.cpp", 1012);

	BfmeX920D *h = m_bfme1CAAI->m_bfme10AAI;

	if (h != 0)
	{
		BfmeRes920D *r = h->bfmeGet920D();

		if (r != 0)
			r->bfmeActAAI();
	}

	return 0;
}
