// ?bfmeFinishANB@BfmeThingANB@@QAEXPAVBfmeSinkANB@@PAX@Z
// partial score=0.82 date=2026-09-10
class INIException
{
public:
	INIException(int argCount, const char *format, ...);
};

extern "C" unsigned char bfmeEmptyANB[];
extern "C" unsigned char bfmeTagANB[];

extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object,
	void *throwInfo);
extern int g_lightPointThrowInfo;

class BfmeSubDST
{
public:
	void *bfmeFindANB(void *key);
};

class BfmeEntryANB
{
public:
	unsigned char m_bfmeHead[8];
	BfmeSubDST m_bfmeSub;
};

class BfmeThingDST
{
public:
	BfmeEntryANB *bfmeFindANB();
	void bfmeResetANB(void *owner, void *entry);
	void bfmeGoDST(void *entry, void *value);
	void *m_bfmeHead;
	void *m_bfmeNext;
	int m_bfmeType;
	unsigned char m_bfmePad[0x14];
	void *m_bfmeValue;
};

class BfmeOwnerERA
{
public:
	void *bfmeLookupANB(void *key);
};

extern BfmeOwnerERA *g_bfmeOwnerERA;

class BfmeSlotANB
{
public:
	void bfmeSetANB(void *text, int flag);
	void *m_bfmeData;
};

class INI
{
public:
	static int scanIndexList(const char *text, const char *const *names);
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

void BfmeThingANB::bfmeFinishANB(BfmeSinkANB *, void *what)
{
	BfmeThingANB *self = this;
	BfmeEntryANB *entry = static_cast<BfmeThingDST *>(what)->bfmeFindANB();
	if (entry == 0)
	{
		const char *name = static_cast<BfmeThingDST *>(what)->m_bfmeValue != 0
			? static_cast<const char *>(static_cast<BfmeThingDST *>(what)->m_bfmeValue) + 8
			: reinterpret_cast<const char *>(0x0107388B);
		INIException error(3, reinterpret_cast<const char *>(0x0109DFD0), name);
		_CxxThrowException(&error, &g_lightPointThrowInfo);
	}

	const char *text = self->m_bfmeB.m_bfmeData != 0
		? static_cast<const char *>(self->m_bfmeB.m_bfmeData) + 8
		: reinterpret_cast<const char *>(0x0107388B);
	int index = INI::scanIndexList(text,
		reinterpret_cast<const char *const *>(0x012B1220));
	struct BfmeFindKeyANB
	{
		int unused;
		int index;
	} key;
	key.index = index;
	void *owner = g_bfmeOwnerERA->bfmeLookupANB(&self->m_bfmeA);
	void **bounds = static_cast<void **>(entry->m_bfmeSub.bfmeFindANB(&key));
	if (bounds[0] != bounds[1]
		&& static_cast<BfmeThingDST *>(what)->m_bfmeType != 2
		&& static_cast<BfmeThingDST *>(what)->m_bfmeType != 4)
	{
		INIException error(3, reinterpret_cast<const char *>(0x0109DF90));
		_CxxThrowException(&error, &g_lightPointThrowInfo);
	}

	static_cast<BfmeThingDST *>(what)->bfmeResetANB(owner,
		reinterpret_cast<void *>(index));
	static_cast<BfmeThingDST *>(what)->bfmeGoDST(reinterpret_cast<void *>(index),
		reinterpret_cast<unsigned char *>(self) + 0x20);
}

void BfmeThingANB::bfmeInitANB(BfmeSinkANB *sink, void *what)
{
	m_bfmeA.bfmeSetANB(bfmeEmptyANB, 0);
	m_bfmeB.bfmeSetANB(bfmeEmptyANB, 0);
	m_bfmeFlag = 0;
	sink->bfmeAddANB(this, bfmeTagANB);
	bfmeFinishANB(sink, what);
}
