// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <hash_map>
#include <vector>

class BfmeBaseR_009D83D0
{
public:
	virtual ~BfmeBaseR_009D83D0(void) {}
};

struct Gen_t_009d80b0_p12cd
{
	int words[3];
	Gen_t_009d80b0_p12cd(void);
	Gen_t_009d80b0_p12cd(const Gen_t_009d80b0_p12cd &);
	~Gen_t_009d80b0_p12cd(void);
	Gen_t_009d80b0_p12cd &operator=(const Gen_t_009d80b0_p12cd &);
};

struct Gen_t_009d8120_p12cd
{
	int words[3];
	Gen_t_009d8120_p12cd(void);
	Gen_t_009d8120_p12cd(const Gen_t_009d8120_p12cd &);
	~Gen_t_009d8120_p12cd(void);
	Gen_t_009d8120_p12cd &operator=(const Gen_t_009d8120_p12cd &);
};

typedef _STL::pair<const int, Gen_t_009d80b0_p12cd> BfmeHashPairA009D83D0;
typedef _STL::hash_map<int, Gen_t_009d80b0_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<BfmeHashPairA009D83D0> >
	BfmeHashMapA009D83D0;
typedef _STL::pair<const int, Gen_t_009d8120_p12cd> BfmeHashPairB009D83D0;
typedef _STL::hash_map<int, Gen_t_009d8120_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<BfmeHashPairB009D83D0> >
	BfmeHashMapB009D83D0;

class Gen_009D83D0 : public BfmeBaseR_009D83D0
{
public:
	Gen_009D83D0(void);
	virtual ~Gen_009D83D0(void) {}

private:
	int m_bfmePad;
	unsigned char m_bfmeFlag;
	unsigned char m_bfmePadTail[3];
	_STL::vector<int> m_bfmeVector;
	BfmeHashMapA009D83D0 m_bfmeB;
	BfmeHashMapB009D83D0 m_bfmeC;
};

Gen_009D83D0::Gen_009D83D0(void)
	: m_bfmePad(0), m_bfmeFlag(false), m_bfmeVector()
{
}

extern "C" unsigned char bfmeVftEOA[];

struct BfmeThingEOA
{
	BfmeThingEOA *bfmeCtorEOA(char flag);
	void bfmeBaseEOA();
	void *volatile m_bfmeVft;
	unsigned char m_bfmeHead[0x3c];
	char volatile m_bfmeFlag;
	unsigned char m_bfmePad[3];
	int volatile m_bfmeK;
};

BfmeThingEOA *BfmeThingEOA::bfmeCtorEOA(char flag)
{
	bfmeBaseEOA();
	m_bfmeFlag = flag;
	m_bfmeVft = bfmeVftEOA;
	m_bfmeK = 0;
	return this;
}

float __cdecl bfmeCalcEOC(void *a);

class BfmeRetBWF
{
};

class BfmeCalcBWF
{
public:
	bool bfmeCalcBWF(BfmeRetBWF *one, float value, BfmeRetBWF *two);
};

struct BfmeOwnerBWF
{
	unsigned char m_bfmeHead[0x60];
	BfmeCalcBWF m_bfmeSub;
};

class ClientSubsystem
{
public:
#define BFME_CLIENT_SLOT(n) virtual void slot##n();
	BFME_CLIENT_SLOT(00) BFME_CLIENT_SLOT(01) BFME_CLIENT_SLOT(02)
	BFME_CLIENT_SLOT(03) BFME_CLIENT_SLOT(04) BFME_CLIENT_SLOT(05)
	BFME_CLIENT_SLOT(06) BFME_CLIENT_SLOT(07) BFME_CLIENT_SLOT(08)
	BFME_CLIENT_SLOT(09) BFME_CLIENT_SLOT(10) BFME_CLIENT_SLOT(11)
	BFME_CLIENT_SLOT(12) BFME_CLIENT_SLOT(13) BFME_CLIENT_SLOT(14)
	BFME_CLIENT_SLOT(15) BFME_CLIENT_SLOT(16) BFME_CLIENT_SLOT(17)
	BFME_CLIENT_SLOT(18) BFME_CLIENT_SLOT(19) BFME_CLIENT_SLOT(20)
	BFME_CLIENT_SLOT(21) BFME_CLIENT_SLOT(22) BFME_CLIENT_SLOT(23)
	BFME_CLIENT_SLOT(24) BFME_CLIENT_SLOT(25) BFME_CLIENT_SLOT(26)
	BFME_CLIENT_SLOT(27) BFME_CLIENT_SLOT(28) BFME_CLIENT_SLOT(29)
	BFME_CLIENT_SLOT(30) BFME_CLIENT_SLOT(31) BFME_CLIENT_SLOT(32)
	BFME_CLIENT_SLOT(33) BFME_CLIENT_SLOT(34) BFME_CLIENT_SLOT(35)
	BFME_CLIENT_SLOT(36) BFME_CLIENT_SLOT(37) BFME_CLIENT_SLOT(38)
	BFME_CLIENT_SLOT(39) BFME_CLIENT_SLOT(40) BFME_CLIENT_SLOT(41)
	BFME_CLIENT_SLOT(42) BFME_CLIENT_SLOT(43) BFME_CLIENT_SLOT(44)
	virtual void updateAudioEvent(unsigned int handle, BfmeRetBWF *event);
#undef BFME_CLIENT_SLOT
};

extern ClientSubsystem *TheAudioClientUpdate;

class BfmeThingCEF
{
public:
	void bfmeOneCEF();
};

struct BfmeThingEOC
{
	void bfmeGoEOC(void *a);
	void bfmeAfterEOC();
	unsigned char m_bfmeHead[8];
	BfmeRetBWF m_bfmeOne;
	unsigned char m_bfmeGap[0xf];
	BfmeOwnerBWF *m_bfmeOwner;
	union
	{
		float m_bfmeF;
		int m_bfmeArg;
	};
	unsigned char m_bfmeGap2[0x28];
	BfmeRetBWF m_bfmeTwo;
	unsigned char m_bfmeGap3[0xb];
	unsigned int m_bfmeHandleA;
	unsigned int m_bfmeHandleB;
};

void BfmeThingEOC::bfmeGoEOC(void *a)
{
	m_bfmeF = bfmeCalcEOC(a);
	bfmeAfterEOC();
}

void BfmeThingEOC::bfmeAfterEOC()
{
	BfmeThingEOC *self = this;
	if (TheAudioClientUpdate == 0)
	{
		return;
	}

	if (self->m_bfmeHandleA < 5)
	{
		if (self->m_bfmeHandleB < 5)
		{
			return;
		}
	}

	BfmeRetBWF *event;
	if (self->m_bfmeOwner != 0)
	{
		event = &self->m_bfmeTwo;
		self->m_bfmeOwner->m_bfmeSub.bfmeCalcBWF(&self->m_bfmeOne, self->m_bfmeF, event);
	}
	else
	{
		event = &self->m_bfmeOne;
	}
	if (event != 0)
	{
		TheAudioClientUpdate->updateAudioEvent(self->m_bfmeHandleA, event);
		TheAudioClientUpdate->updateAudioEvent(self->m_bfmeHandleB, event);
	}
	else
		reinterpret_cast<BfmeThingCEF *>(self)->bfmeOneCEF();
}

struct BfmeThingEOD
{
	BfmeThingEOD *bfmeGoEOD(void *a, void *b);
	void bfmeCallEOD(void *a);
	unsigned char m_bfmeHead[4];
	void *m_bfmeP;
};

BfmeThingEOD *BfmeThingEOD::bfmeGoEOD(void *a, void *b)
{
	bfmeCallEOD(a);
	m_bfmeP = b;
	return this;
}

extern "C" void bfmeCbEOEa();
extern "C" void bfmeCbEOEb();

struct BfmeThingEOE
{
	BfmeThingEOE *bfmeCtorEOE();
};

void __stdcall bfmeInitEOE(BfmeThingEOE *o, int a, int b, void (*ca)(), void (*cb)());

BfmeThingEOE *BfmeThingEOE::bfmeCtorEOE()
{
	bfmeInitEOE(this, 0x14, 8, bfmeCbEOEa, bfmeCbEOEb);
	return this;
}

struct BfmeQueueEOF
{
	unsigned char m_bfmeHead[4];
	void **m_bfmeEnd;
	unsigned char m_bfmePad[4];
	void **volatile m_bfmeCur;
};

struct BfmeThingEOF
{
	void *bfmeGoEOF();
	BfmeQueueEOF *m_bfmeQ;
};

void *BfmeThingEOF::bfmeGoEOF()
{
	BfmeQueueEOF *q = m_bfmeQ;
	if (q->m_bfmeCur == q->m_bfmeEnd)
		return 0;
	void **cur = q->m_bfmeCur;
	void *v = *cur;
	q->m_bfmeCur = cur + 2;
	return v;
}

struct BfmeNodeEOG
{
	BfmeNodeEOG *bfmeUpdEOG();
	unsigned char m_bfmeHead[4];
	BfmeNodeEOG *m_bfmeQ;
	unsigned char m_bfmePad[0x108];
	float m_bfmeF;
};

struct BfmeThingEOG
{
	float bfmeGoEOG();
	unsigned char m_bfmeHead[4];
	BfmeNodeEOG *m_bfmeP;
	unsigned char m_bfmePad[0x108];
	float m_bfmeF;
};

float BfmeThingEOG::bfmeGoEOG()
{
	BfmeNodeEOG *p = m_bfmeP;
	if (p)
	{
		BfmeNodeEOG *q = p->m_bfmeQ;
		if (q)
			p = q->bfmeUpdEOG();
		return p->m_bfmeF;
	}
	return m_bfmeF;
}
