// cl: /DNDEBUG /MD /EHsc

// BFME's base here is not Zero Hour's Snapshot: retail's base destructor call
// goes to the 14-byte body at 0x009A1A40 (the one ??1SubsystemInterface@@UAE@XZ
// folds onto), while Snapshot's own body at 0x0006B180/0x009A1A40 is claimed by
// a different name.  Address-derived local name so the call has one of its own.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class BfmeModuleDataSnapshotBase
{
public:
	virtual void anchor();
	~BfmeModuleDataSnapshotBase();
};

class Gen_dtor_009eb9e0
{
public:
	~Gen_dtor_009eb9e0();
};

class Rva009EB960 : public BfmeModuleDataSnapshotBase
{
public:
	virtual ~Rva009EB960();

private:
	void *m_debugName;
	Gen_dtor_009eb9e0 *m_renderObject;
};

Rva009EB960::~Rva009EB960()
{
	delete m_renderObject;
}
