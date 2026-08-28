// cl: /DNDEBUG /MD /EHsc

// Two string members and an inlined base destructor, under the C++ EH frame the
// two destructible members require.
//
// The members are destroyed at +0x58 then +0x44 -- reverse declaration order, as
// destructors do -- and both calls resolve to the same address, so they are the
// same type. That address is the folded releaseBuffer body, which is what
// BFMERetailAsciiString's inline destructor leaves behind at a call site: the
// destructor itself inlines away and the private out-of-line call remains.
//
// The vptr store at the end is not this class's. A destructor installs its own
// vptr first, and here nothing observes it -- the only calls are non-virtual
// ones on members -- so MSVC drops it. What is left is the inlined base
// destructor running last, and 0x01073744 is Snapshot's table: ??0Snapshot and
// ??1Snapshot both install it.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

// The two strings sit in different classes. Destruction runs +0x58 then +0x44,
// which is a derived member going before an inlined base's rather than two
// members of one class in reverse order -- those would run +0x58 then +0x44 too,
// but with the unwind states counting down. Retail counts up, 0 then 1.
//
// novtable on both is what suppresses their own vptr stores; the only one that
// survives is Snapshot's, from the base destructor inlined last.
class __declspec(novtable) CrateCollideModuleData : public Snapshot
{
public:
	virtual ~CrateCollideModuleData() {}

private:
	unsigned char m_head[0x40];
	BFMERetailAsciiString m_first;
};

class __declspec(novtable) UnitCrateCollideModuleData : public CrateCollideModuleData
{
public:
	virtual ~UnitCrateCollideModuleData();

private:
	unsigned char m_middle[0x10];
	BFMERetailAsciiString m_second;
};

// ??1UnitCrateCollideModuleData@@UAE@XZ
UnitCrateCollideModuleData::~UnitCrateCollideModuleData()
{
}
