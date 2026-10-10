// cl: /DNDEBUG /MD /EHsc

// GeometryUpgrade::removeUpgrade, retail 0x002D55F0 (269 B): slot 7 of the
// UpgradeMux table 0x010CCC48, which GeometryUpgrade's registered constructor
// 0x002D5790 stores at +0x10; the only route is ILT 0x00028B69, whose VA
// appears once in the image. Slot 7 is
// EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot), which undoes slot 9
// (GeometryUpgrade::upgradeImplementation, 0x002D5980). Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md and
// targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md
// The receiver ('this') is the UpgradeMux sub-object, an
// interior pointer whose sibling fields sit at NEGATIVE offsets (-0x8, -0xC,
// -0x10), so those are read with raw pointer arithmetic rather than modelled
// as real members. ILT41970 reaches the opaque thiscall/RET0 body002D9F90;
// ILT06D7F reaches Pathfinder::removeObjectFromPathfindMap at003D5810;
// ILT21472 reaches Gen_00411580::m, an int-returning pointer-sized getter.
// The other callees are landed: BfmeObjF9::setFlag
// (landed, Rva0087F9C0Flag.cpp), Pathfinder::addObjectToPathfindMap (landed,
// PathfindMapObjectWrappers.cpp), and BfmeHostCL::bfmeResetCL (landed,
// BfmeConv1924.cpp).

class BfmeHostCL;

class BfmeBaseZJ
{
};

extern "C" void __cdecl __identifier("?d_002d9f90@@YAXXZ")();

class BfmePathCL
{
};

class AI
{
public:
	unsigned char m_bfmeHeadCL[0xc];
	BfmePathCL *m_bfmePathCL;
};

extern AI *TheAI;

class Object;

// Declared here only to spell the callee under its real defining name;
// the definition is landed in PathfindMapObjectWrappers.cpp.
class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
	void removeObjectFromPathfindMap(Object *object);
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
};

struct Gen_00411580
{
	int m();
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

class GeometryUpgrade : public BfmeOwnerVtbl
{
public:
	virtual void removeUpgrade();

public:

	unsigned char m_pad04[8];
	BfmeStrF9 m_inlineName;
};

void GeometryUpgrade::removeUpgrade()
{
	if (!canTeardown())
		return;

	union
	{
		void (__cdecl *symbol)();
		void (BfmeBaseZJ::*member)();
	} clear;
	clear.symbol = &__identifier("?d_002d9f90@@YAXXZ");
	(((BfmeBaseZJ *)((char *)this - 0x10))->*clear.member)();
	BfmeHostCL *host = *(BfmeHostCL **)((char *)this - 8);
	((Pathfinder *)TheAI->m_bfmePathCL)->removeObjectFromPathfindMap((Object *)host);

	BfmeItemBP **list = (BfmeItemBP **)((Gen_00411580 *)host->bfmeGetBBP())->m();
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

	((Pathfinder *)TheAI->m_bfmePathCL)->addObjectToPathfindMap((Object *)host);
	host->bfmeResetCL(0);
	bfmeVfunc8(0);
}
