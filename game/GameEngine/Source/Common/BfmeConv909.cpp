// Open-BFME5 conversions.

class BfmeSrcSG
{
public:
	int bfmeQuerySG();
};

class BfmeThingSG
{
public:
	void bfmeGoSG();
	BfmeSrcSG *m_bfmeSrc;
	char m_bfmeA;
	char m_bfmeB;
	char m_bfmeDone;
};

void BfmeThingSG::bfmeGoSG()
{
	if (m_bfmeDone)
		return;
	int r = m_bfmeSrc->bfmeQuerySG();
	m_bfmeA = (char)r;
	m_bfmeB = (r == -1);
	m_bfmeDone = 1;
}

class Gen_00832090
{
public:
	void m();
};

extern char g_bfmeVftTA[];
void bfmeFreeTA(void *p);

class BfmeThingTA
{
public:
	void bfmeGoTA();
	char *m_bfmeVft;
	char m_bfmePad[8];
	void *m_bfmeP;
	char m_bfmeFlag;
};

void BfmeThingTA::bfmeGoTA()
{
	m_bfmeVft = g_bfmeVftTA;
	if (m_bfmeFlag)
		bfmeFreeTA(m_bfmeP);
	((Gen_00832090 *)this)->m();
}

extern int g_bfmeCountTB;
namespace _STL
{
class _Locale_impl;
extern _Locale_impl *_Bfme_classic_locale;
}
void bfmeOneTB(void);
void *bfmeTwoTB(void);

class BfmeThingTB
{
public:
	BfmeThingTB *bfmeGoTB();
};

BfmeThingTB *BfmeThingTB::bfmeGoTB()
{
	if (!g_bfmeCountTB) {
		bfmeOneTB();
		_STL::_Bfme_classic_locale = (_STL::_Locale_impl *)bfmeTwoTB();
		++g_bfmeCountTB;
	}
	return this;
}

