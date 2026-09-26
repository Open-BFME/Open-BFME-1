// cl: /DNDEBUG /MD /EHsc

// Open-BFME: carved body at retail 0x002D55F0 (269 B). Sole caller is an ILT
// thunk, so identity remains address-derived; the receiver ('this') is an
// interior pointer whose sibling fields sit at NEGATIVE offsets (-0x8, -0xC,
// -0x10), so those are read with raw pointer arithmetic rather than modelled
// as real members. Callees are pinned/landed: BfmeBaseZJ::bfmeClearZJ,
// BfmePathCL::bfmeDropOneCL, BfmeBBP::bfmeListBP, BfmeObjF9::setFlag
// (landed, Rva0087F9C0Flag.cpp), addObjectToPathfindMap (landed,
// BFMEPathfinderMapShim), and BfmeHostCL::bfmeResetCL (landed,
// BfmeConv1924.cpp).

class BfmeHostCL;

class BfmeBaseZJ
{
public:
	void bfmeClearZJ();
};

class BfmePathCL
{
public:
	void bfmeDropOneCL(BfmeHostCL *o);
};

class AI
{
public:
	unsigned char m_bfmeHeadCL[0xc];
	BfmePathCL *m_bfmePathCL;
};

extern AI *TheAI;

class Object;

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *object);
};

class BfmeItemBP
{
public:
#define RVA002D55F0_SLOT(N) virtual void slot##N() = 0
	RVA002D55F0_SLOT(00); RVA002D55F0_SLOT(01); RVA002D55F0_SLOT(02); RVA002D55F0_SLOT(03);
	RVA002D55F0_SLOT(04); RVA002D55F0_SLOT(05); RVA002D55F0_SLOT(06); RVA002D55F0_SLOT(07);
	RVA002D55F0_SLOT(08); RVA002D55F0_SLOT(09); RVA002D55F0_SLOT(10); RVA002D55F0_SLOT(11);
	RVA002D55F0_SLOT(12); RVA002D55F0_SLOT(13); RVA002D55F0_SLOT(14); RVA002D55F0_SLOT(15);
	RVA002D55F0_SLOT(16); RVA002D55F0_SLOT(17); RVA002D55F0_SLOT(18); RVA002D55F0_SLOT(19);
	RVA002D55F0_SLOT(20); RVA002D55F0_SLOT(21); RVA002D55F0_SLOT(22); RVA002D55F0_SLOT(23);
	RVA002D55F0_SLOT(24); RVA002D55F0_SLOT(25); RVA002D55F0_SLOT(26); RVA002D55F0_SLOT(27);
	RVA002D55F0_SLOT(28); RVA002D55F0_SLOT(29); RVA002D55F0_SLOT(30); RVA002D55F0_SLOT(31);
	RVA002D55F0_SLOT(32); RVA002D55F0_SLOT(33); RVA002D55F0_SLOT(34); RVA002D55F0_SLOT(35);
	RVA002D55F0_SLOT(36); RVA002D55F0_SLOT(37); RVA002D55F0_SLOT(38); RVA002D55F0_SLOT(39);
	RVA002D55F0_SLOT(40); RVA002D55F0_SLOT(41); RVA002D55F0_SLOT(42); RVA002D55F0_SLOT(43);
	RVA002D55F0_SLOT(44); RVA002D55F0_SLOT(45); RVA002D55F0_SLOT(46); RVA002D55F0_SLOT(47);
	virtual void bfmeItem48(int a) = 0;
	virtual void bfmeItem49(int a, int b) = 0;
#undef RVA002D55F0_SLOT
};

class BfmeBBP
{
public:
	BfmeItemBP **bfmeListBP();
};

class BfmeHostCL
{
public:
#define RVA002D55F0_HOST_SLOT(N) virtual void slot##N() = 0
	RVA002D55F0_HOST_SLOT(00); RVA002D55F0_HOST_SLOT(01); RVA002D55F0_HOST_SLOT(02);
	RVA002D55F0_HOST_SLOT(03); RVA002D55F0_HOST_SLOT(04); RVA002D55F0_HOST_SLOT(05);
	RVA002D55F0_HOST_SLOT(06); RVA002D55F0_HOST_SLOT(07); RVA002D55F0_HOST_SLOT(08);
	RVA002D55F0_HOST_SLOT(09);
	virtual BfmeBBP *bfmeGetBBP() = 0;
#undef RVA002D55F0_HOST_SLOT

	void bfmeResetCL(char full);
};

struct BfmeAsciiDataF9
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

class BfmeStrF9
{
public:
	int getLength() const { return m_data ? m_data->m_len : 0; }
	BfmeAsciiDataF9 *m_data;
};

class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &name, char flag);
};

class BfmeOwnerVtbl
{
public:
	virtual bool canTeardown() = 0;
#define RVA002D55F0_OWN_SLOT(N) virtual void slot##N() = 0
	RVA002D55F0_OWN_SLOT(01); RVA002D55F0_OWN_SLOT(02); RVA002D55F0_OWN_SLOT(03);
	RVA002D55F0_OWN_SLOT(04); RVA002D55F0_OWN_SLOT(05); RVA002D55F0_OWN_SLOT(06);
	RVA002D55F0_OWN_SLOT(07);
#undef RVA002D55F0_OWN_SLOT
	virtual void bfmeVfunc8(int a) = 0;
};

class Rva002D55F0Inner
{
public:
	unsigned char m_pad70[0x70];
	BfmeStrF9 *m_start2;
	BfmeStrF9 *m_finish2;
	unsigned char m_pad78[4];
	BfmeStrF9 *m_start1;
	BfmeStrF9 *m_finish1;
};

class Rva002D55F0Owner : public BfmeOwnerVtbl
{
public:
	void bfmeTeardown002D55F0();

	unsigned char m_pad04[8];
	BfmeStrF9 m_inlineName;
};

void Rva002D55F0Owner::bfmeTeardown002D55F0()
{
	if (!canTeardown())
		return;

	((BfmeBaseZJ *)((char *)this - 0x10))->bfmeClearZJ();
	BfmeHostCL *host = *(BfmeHostCL **)((char *)this - 8);
	TheAI->m_bfmePathCL->bfmeDropOneCL(host);

	BfmeItemBP **list = host->bfmeGetBBP()->bfmeListBP();
	for (BfmeItemBP *item = list[0]; item != 0; item = list[1], ++list)
	{
		item->bfmeItem48(0);
		list[0]->bfmeItem49(0, 0);
		list[0]->bfmeItem49(0, 1);
	}

	Rva002D55F0Inner *inner = *(Rva002D55F0Inner **)((char *)this - 0xc);
	BfmeObjF9 *flags = (BfmeObjF9 *)((char *)host + 0xac);
	for (BfmeStrF9 *s = inner->m_start1; s != inner->m_finish1; ++s)
		flags->setFlag(*s, 0);
	for (BfmeStrF9 *s = inner->m_start2; s != inner->m_finish2; ++s)
		flags->setFlag(*s, 0);

	BfmeAsciiDataF9 *data = m_inlineName.m_data;
	if (data != 0 && data->m_len != 0)
		flags->setFlag(m_inlineName, 1);

	((BFMEPathfinderMapShim *)TheAI->m_bfmePathCL)->addObjectToPathfindMap((Object *)host);
	host->bfmeResetCL(0);
	bfmeVfunc8(0);
}
