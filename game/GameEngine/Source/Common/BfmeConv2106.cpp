void __cdecl operator delete[](void *p);

class BfmeOverride1137
{
public:
	virtual void bfmeDeleteZB(int flag) = 0;

	BfmeOverride1137 *bfmeFinalZB();

	BfmeOverride1137 *m_bfme04ZB;
};

extern BfmeOverride1137 *g_bfmeGlo012F15F8;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void bfmeS1ZB() = 0;
};

static __forceinline BfmeOverride1137 *bfmeWalkZB(BfmeOverride1137 *p)
{
	if (p->m_bfme04ZB == 0)
		return p;

	return p->m_bfme04ZB->bfmeFinalZB();
}

class BfmeHostZB : public SubsystemInterface
{
public:
	virtual ~BfmeHostZB();

	unsigned char m_bfme04ZB[4];
	char *m_bfme08ZB;
};

BfmeHostZB::~BfmeHostZB()
{
	operator delete[](m_bfme08ZB);

	m_bfme08ZB = 0;

	BfmeOverride1137 *g = g_bfmeGlo012F15F8;

	if (g != 0)
	{
		BfmeOverride1137 *n = g->m_bfme04ZB;

		if ((n != 0 ? n->bfmeFinalZB() : g) != 0)
		{
			BfmeOverride1137 *ov = (n != 0 ? n->bfmeFinalZB() : g);

			if (ov != 0)
				ov->bfmeDeleteZB(1);

			g_bfmeGlo012F15F8 = 0;
		}
	}
}
