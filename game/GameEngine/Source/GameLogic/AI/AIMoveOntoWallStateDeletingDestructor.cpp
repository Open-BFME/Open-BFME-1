// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIMoveOntoWallState.
// Vtable 0x00C98540 slots name this class (?xfer@AIMoveOntoWallState@@MAEXPAVXfer@@@Z); its slot zero routes
// through ILT 0x0003125A to this 30-byte wrapper, whose complete destructor
// route ILT 0x00010C4E reaches cleanup body 0x00171DB0.

// Complete destructor 0x00171DB0: re-seats ??_7AIMoveOntoWallState@@6B@, shuts
// down and deletes the owned object at +0x24 through its vtable (slot 15, then
// the deleting destructor), then calls the base ~State through ILT 0x00016725.
class AIMoveOntoWallStateOwned
{
public:
	virtual ~AIMoveOntoWallStateOwned();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void shutdown();
};

// The base destructor 0x000A1B30 is ledgered as ??1Rva000A1B30Holder@@QAE@XZ;
// reach it the way Q4OwnedPtrDtors.cpp does, without a base vptr store.
class Rva000A1B30Holder { public: ~Rva000A1B30Holder(); };

class __declspec(novtable) OwnedPtrBase000A1B30
{
public:
	virtual ~OwnedPtrBase000A1B30() { reinterpret_cast<Rva000A1B30Holder *>(this)->Rva000A1B30Holder::~Rva000A1B30Holder(); }
};

class AIMoveOntoWallState : public OwnedPtrBase000A1B30
{
protected:
	virtual ~AIMoveOntoWallState();

private:
	char m_gap[0x24 - 4];
	AIMoveOntoWallStateOwned *m_owned;

	friend void forceAIMoveOntoWallStateDeletingDestructor();
};

AIMoveOntoWallState::~AIMoveOntoWallState()
{
	if (m_owned)
	{
		m_owned->shutdown();
		delete m_owned;
		m_owned = 0;
	}
}

void forceAIMoveOntoWallStateDeletingDestructor()
{
	AIMoveOntoWallState value;
}
