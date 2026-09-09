// cl: /DNDEBUG /MD /EHs-c-
// BFME retail 0x00161B50: TeamInQueue::xfer(Xfer *)
// Preserve the paired transfer version bytes and eight-byte XferException.
//
// The BFME Xfer interface is not layout-compatible with the reference ZH
// header.  This local view preserves the observed virtual slots: the light
// CRC query at +0x10, IsStoring at +0x08, version at +0x28, snapshots at +0x30,
// unsigned-int/int transfers at +0x74/+0x78, unsigned-short at +0x7c, and
// bool transfers at +0x8c.  TeamInQueue's two intrusive-list links occupy
// the inherited +0x04..+0x10 area, so its work-order and state fields start
// at the retail +0x14.

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef UnsignedInt TeamID;

enum ObjectID
{
	BFME_OBJECT_ID_INVALID = 0
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

struct XferException
{
	char *text;
	int tag;
};

struct TeamInQueueXferLocal
{
	union
	{
		XferVersion version;
		XferException error;
	};
	TeamID teamID;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, Int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

class Snapshot;

class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual void slot03();
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void xferUnsignedShort(UnsignedShort *value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

// Retail WorkOrder's installed BFME snapshot table at 0x01096964 is
// destructor/post-load/name/transfer; this TU stores that existing vptr and emits no table.
class WorkOrder
{
public:
	WorkOrder()
		: m_vptr((void *)0x01096964), m_thing(0), m_factoryID(0), m_next(0),
		  m_numCompleted(0), m_numRequired(1), m_isResourceGatherer(false)
	{
	}

	void *m_vptr;
	void *m_thing;
	UnsignedInt m_factoryID;
	WorkOrder *m_next;
	Int m_numCompleted;
	Int m_numRequired;
	Bool m_required;
	Bool m_isResourceGatherer;
};

class Team
{
public:
	TeamID getID() const
	{
		return *(const TeamID *)((const char *)this + 8);
	}
};

class TeamFactory
{
public:
	Team *findTeamByID(TeamID teamID);
};

extern TeamFactory *TheTeamFactory;

// Existing retail owner for the BFME ObjectID transfer ILT at 0x0000C9B4.
extern void friend_xferObjectID(Xfer *xfer, ObjectID *objectID);

class TeamInQueueBase
{
public:
	virtual ~TeamInQueueBase() {}
	void *m_buildNext;
	void *m_buildPrevious;
	void *m_readyNext;
	void *m_readyPrevious;
};

class TeamInQueue : public TeamInQueueBase
{
protected:
	// BFME's installed table is destructor/post-load/name/transfer; the retail name slot
	// returns the adjacent TeamInQueue literal at 0x01096954.
	virtual void loadPostProcess();
	virtual const char *getSnapshotName() const;
	virtual void xfer(Xfer *xfer);

public:
	WorkOrder *m_workOrders;
	Bool m_priorityBuild;
	unsigned char m_pad19[3];
	Team *m_team;
	TeamInQueue *m_nextTeamInQueue;
	Int m_frameStarted;
	Bool m_sentToStartLocation;
	Bool m_stopQueueing;
	Bool m_reinforcement;
	unsigned char m_pad2b;
	ObjectID m_reinforcementID;
};

// ?xfer@TeamInQueue@@MAEXPAVXfer@@@Z
void TeamInQueue::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	TeamInQueueXferLocal local;
	local.version.m_version = 1;
	local.version.m_currentVersion = 1;
	xfer->xferVersion(&local.version);

	UnsignedShort workOrderCount = 0;
	WorkOrder *workOrder;
	for (workOrder = m_workOrders; workOrder; workOrder = workOrder->m_next)
		++workOrderCount;
	xfer->xferUnsignedShort(&workOrderCount);

	if (xfer->IsStoring())
	{
		for (workOrder = m_workOrders; workOrder; workOrder = workOrder->m_next)
			xfer->xferSnapshot((Snapshot *)workOrder);
	}
	else
	{
		if (m_workOrders != 0)
		{
			bfmeFormatText(&local.error, 5, 0);
			_CxxThrowException(&local.error, (void *)0x011DFE5C);
		}

		for (UnsignedShort i = 0; i < workOrderCount; ++i)
		{
			workOrder = new WorkOrder;

			workOrder->m_next = 0;
			if (m_workOrders == 0)
				m_workOrders = workOrder;
			else
			{
				WorkOrder *last = m_workOrders;
				while (last->m_next != 0)
					last = last->m_next;
				last->m_next = workOrder;
			}

			xfer->xferSnapshot((Snapshot *)workOrder);
		}
	}

	xfer->xferBool(&m_priorityBuild);
	local.teamID = m_team ? m_team->getID() : 0;
	xfer->xferUnsignedInt(&local.teamID);
	if (xfer->IsLoading())
		m_team = TheTeamFactory->findTeamByID(local.teamID);
	xfer->xferInt(&m_frameStarted);
	xfer->xferBool(&m_sentToStartLocation);
	xfer->xferBool(&m_stopQueueing);
	xfer->xferBool(&m_reinforcement);
	friend_xferObjectID(xfer, &m_reinforcementID);
}
