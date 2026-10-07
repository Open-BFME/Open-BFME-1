// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <deque>
#include <windows.h>

// Open-BFME5 conversions.

// Retail 0x012F0898 is EA's GameLogic *TheGameLogic, defined once in
// game/GameEngine/Source/GameLogic/System/GameLogic.cpp.  BfmeStore1024 is a
// TU-local view of that object, reached here through the canonical global.
class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeV1024;

class BfmeM1024
{
public:
	BfmeV1024 *bfmeFind1024(int h);
};

class ImageCollection;
extern ImageCollection *TheMappedImageCollection;

class BfmeSlots1024
{
public:
	BfmeV1024 **bfmeSlot1024(int k);
};

class BfmeA1024
{
public:
	void bfmeGo1024A(int k, int h);

	char m_bfmePad[0x6c];
	BfmeSlots1024 m_bfmeMap;
};

void BfmeA1024::bfmeGo1024A(int k, int h)
{
	BfmeV1024 *v = reinterpret_cast<BfmeM1024 *>(TheMappedImageCollection)->bfmeFind1024(h);

	if (v != 0)
		*m_bfmeMap.bfmeSlot1024(k) = v;
}

class BfmeN1024
{
public:
	__declspec(noinline) void bfmeDrop1024(int id);
};

extern BfmeN1024 *g_bfmeN1024;

enum ParticleSystemID { RvaParticleSystemIDInvalid = 0 };

class ParticleSystemManager
{
public:
	void destroyParticleSystemByID(ParticleSystemID id);
};

void BfmeN1024::bfmeDrop1024(int id)
{
	((ParticleSystemManager *)this)->destroyParticleSystemByID(
		(ParticleSystemID)id);
}

class BfmeList1024
{
public:
	void bfmeClear1024(void);

	void *m_bfmeHead;
	char m_bfmePad[8];
};

class BfmeB1024
{
public:
	void bfmeGo1024B(void);

	char m_bfmePad[0x14];
	BfmeList1024 m_bfmeList;
	int m_bfmeId;
};

void BfmeB1024::bfmeGo1024B(void)
{
	if (m_bfmeList.m_bfmeHead != 0) {
		g_bfmeN1024->bfmeDrop1024(m_bfmeId);
		m_bfmeList.bfmeClear1024();
		m_bfmeId = 0;
	}
}

class BfmeTab1024
{
public:
	int bfmeFind1024(int k);
	void bfmeAdd1024(int k, int v);
};

struct BfmeMap1024
{
	char m_bfmePad[8];
	BfmeTab1024 m_bfmeTab;
};

extern BfmeMap1024 *g_bfmeMap1024;

class BfmeD1024
{
public:
	char bfmeGo1024D(int unused, int k, int v);

	char m_bfmePad[8];
	BfmeTab1024 m_bfmeOwn;
};

char BfmeD1024::bfmeGo1024D(int unused, int k, int v)
{
	if (g_bfmeMap1024->m_bfmeTab.bfmeFind1024(k) == 0)
		m_bfmeOwn.bfmeAdd1024(k, v);

	return 1;
}

class BfmeE1024;

class AssetManagerImpl
{
public:
	void UnloadAsset(BfmeE1024 *asset);

	char m_unmodelled_000[0x20];
	int m_bfmeCount;
	char m_unmodelled_024[0x3c];
	CRITICAL_SECTION m_bfmeLock;
	_STL::deque<int> m_bfmeQueues[7];
};

class AssetManagerImpl;
class AssetRegistry;
extern AssetRegistry *g_theAssetRegistry;

class BfmeE1024
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual unsigned int slot38();
	void bfmeGo1024E(void);

	union { unsigned int m_bfmeFlags; volatile unsigned int m_bfmeFlagsShared; };
	void *m_bfmeEntry;
};

void BfmeE1024::bfmeGo1024E(void)
{
	if ((m_bfmeFlags & 0xff0000) == 0x70000)
		return;

	if (g_theAssetRegistry == 0)
		return;

	((AssetManagerImpl *)g_theAssetRegistry)->UnloadAsset(this);
}

void AssetManagerImpl::UnloadAsset(BfmeE1024 *item)
{
	if (!item->m_bfmeEntry || (item->m_bfmeFlagsShared & 0xff0000) == 0x70000)
		return;

	EnterCriticalSection(&m_bfmeLock);
	while (((item->m_bfmeFlagsShared & 0xff0000) == 0x10000 ||
		(item->m_bfmeFlagsShared & 0xff0000) == 0x50000) &&
		m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].front() == (int)item)
	{
		LeaveCriticalSection(&m_bfmeLock);
		Sleep(1);
		EnterCriticalSection(&m_bfmeLock);
	}
	while ((item->m_bfmeFlagsShared & 0xff0000) == 0x80000)
	{
		LeaveCriticalSection(&m_bfmeLock);
		Sleep(1);
		EnterCriticalSection(&m_bfmeLock);
	}

	unsigned int i = 0;
	for (; i < m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].size(); ++i)
	{
		if (m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].begin()[i] == (int)item)
			break;
	}
	m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].begin()[i] =
		m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].begin()[
			m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].size() - 1];
	m_bfmeQueues[(item->m_bfmeFlagsShared >> 16) & 0xff].pop_back();
	LeaveCriticalSection(&m_bfmeLock);

	item->m_bfmeFlags &= 0xfdffffff;
	if ((item->m_bfmeFlagsShared & 0xff0000) == 0x30000)
	{
		m_bfmeCount -= item->slot38();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff04ffff) | 0x40000;
		if (m_bfmeCount < 0)
			m_bfmeCount = 0;
	}

	switch ((item->m_bfmeFlagsShared >> 16) & 0xff)
	{
	case 0:
		item->slot04();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff01ffff) | 0x10000;
	case 1:
		item->slot08();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff02ffff) | 0x20000;
		m_bfmeCount += item->slot38();
	case 2:
		item->slot0C();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff04ffff) | 0x40000;
		m_bfmeCount -= item->slot38();
		if (m_bfmeCount < 0)
			m_bfmeCount = 0;
	case 4:
		item->slot14();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff05ffff) | 0x50000;
	case 5:
		item->slot18();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff06ffff) | 0x60000;
	case 6:
		item->slot1C();
		item->m_bfmeFlags = (item->m_bfmeFlagsShared & 0xff07ffff) | 0x70000;
	}
}


struct BfmeRec1024
{
	char m_bfmePad[0x344];
	char m_bfmeFlags;
};

class BfmeStore1024
{
public:
	BfmeRec1024 *bfmeFind1024S(int id);
};

static inline BfmeStore1024 *bfmeStore1024(void)
{
	return (BfmeStore1024 *)TheGameLogic;
}

class BfmeF1024
{
public:
	char bfmeGo1024F(void);

	char m_bfmePad[0x20];
	int m_bfmeId;
};

char BfmeF1024::bfmeGo1024F(void)
{
	int id = m_bfmeId;

	if (id == 0)
		return 0;

	BfmeRec1024 *r = bfmeStore1024()->bfmeFind1024S(id);

	if (r == 0)
		return 1;

	char f = r->m_bfmeFlags;

	f &= 1;
	return f;
}
