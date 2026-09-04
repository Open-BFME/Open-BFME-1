// cl: /DNDEBUG /MD /EHsc
// W3DSmudgeManager::ReleaseResources, retail 0x00722190, 90 bytes.
//
// The lock and unlock at either end are a guard object, not two bare calls:
// that is what gives the body its SEH frame and the two unwind writes, which
// bracket exactly the region between the constructor and the destructor. Both
// halves are free functions the ledger already names.
//
// Between them one reference-counted handle at +0x34 is released -- the count
// at +0x04 of the target dropped in place, slot 0 of its table entered with no
// argument when it reaches zero -- and the pointer cleared.

typedef int Int;

void W3DRadarResetLock(void);					// retail 0x00903090
void W3DRadarResetUnlock(void);					// retail 0x00905B10

class BfmeRadarResetLock
{
public:
	BfmeRadarResetLock() { W3DRadarResetLock(); }
	~BfmeRadarResetLock() { W3DRadarResetUnlock(); }
};

class IndexBufferRef
{
public:
	virtual void destroy(void);					// slot 0

	Int m_refCount;							// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameFont.h
class SmudgeManager
{
public:
	virtual ~SmudgeManager();

private:
	char m_body[0x20];
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	virtual void ReleaseResources(void);

private:
	void *m_smudgeGroup;
	void *m_posBuffer;
	void *m_RGBABuffer;
	void *m_sizeBuffer;
	IndexBufferRef *m_indexBuffer;
};

// ?ReleaseResources@W3DSmudgeManager@@UAEXXZ
void W3DSmudgeManager::ReleaseResources(void)
{
	BfmeRadarResetLock lock;

	// The handle goes into a local: read through the member the compiler
	// cannot use the decrement's own flags and reloads the count to test it.
	IndexBufferRef *indexBuffer = m_indexBuffer;

	if (indexBuffer)
	{
		if (--indexBuffer->m_refCount == 0)
			indexBuffer->destroy();

		m_indexBuffer = 0;
	}
}
