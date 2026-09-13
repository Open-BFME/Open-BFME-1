// ?bfmeGetEME@BfmeObjEME@@QAEPAXPAX@Z
// partial score=0.8 date=2026-09-13
// ?bfmeGetEME@BfmeObjEME@@QAEPAXPAX@Z
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/namekeygenerator /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"

struct BfmeLockTEA;
extern "C" __declspec(dllimport) void __stdcall bfmeEnterTEA(BfmeLockTEA *lock);
extern "C" __declspec(dllimport) void __stdcall bfmeLeaveTEA(BfmeLockTEA *lock);

struct BfmeObjEMENode
{
	BfmeObjEMENode *m_next;
	NameKeyType m_key;
};

class BfmeObjEME
{
public:
	bool bfmeAskEME(void *a);
	void *bfmeGetEME(void *a);

private:
	unsigned char m_pad_000[0x2c];
	unsigned char m_lock[0x18];
	unsigned char m_pad_044[4];
	BfmeObjEMENode **m_bucketStart;
	BfmeObjEMENode **m_bucketFinish;
	unsigned char m_pad_050[0x1f0 - 0x50];
	NameKeyGenerator *m_hashContext;
};

class BfmeObjEMELockGuard
{
public:
	explicit BfmeObjEMELockGuard(BfmeLockTEA *lock) : m_lock(lock)
	{
		bfmeEnterTEA(lock);
	}
	~BfmeObjEMELockGuard()
	{
		bfmeLeaveTEA(m_lock);
	}

	BfmeLockTEA *m_lock;
};

void *BfmeObjEME::bfmeGetEME(void *a)
{
	BfmeObjEMELockGuard lock((BfmeLockTEA *)((unsigned char *)this + 0x2c));

	NameKeyType key = m_hashContext->nameToLowercaseKey((const char *)a);
	if (key == NAMEKEY_INVALID)
		return 0;

	unsigned int bucketCount = (unsigned int)(m_bucketFinish - m_bucketStart);
	unsigned int bucket = (unsigned int)key % bucketCount;
	BfmeObjEMENode *node = m_bucketStart[bucket];
	if (node == 0)
		return 0;

	while (node->m_key != key)
	{
		node = node->m_next;
		if (node == 0)
			return 0;
	}

	return (void *)key;
}
