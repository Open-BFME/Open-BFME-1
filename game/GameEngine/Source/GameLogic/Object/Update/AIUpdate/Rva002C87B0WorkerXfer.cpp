// cl: /DNDEBUG /MD /EHsc
// WorkerAIUpdate::xfer, retail RVA 0x002C87B0.  The semantic identity is
// established by the Worker field sequence and the landed Worker neighbours;
// this TU keeps the address in its class name until the generated claim is
// replaced by the proven body.

#include "../../../../../Include/Common/ScalarTypes.h"


typedef int ObjectID;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *, int);
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void xferSnapshot(void *);
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
	virtual void xferCoord3D(float *);
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *);
	virtual void xferInt(int *);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(UnsignedInt *);
};

class BfmeSeedTarget;

// The call at 0x2C87BC reaches the incremental-link thunk at retail 0x00043441,
// the ledger's 5-byte row ?j_00043441@@YAXXZ (game/gen_small/thunks_032.cpp), as
// tools/callees.py 0x2c87b0 499 prints for the callee.  Nothing defines a member
// named bfmeAccept here, so the call names the thunk the ledger owns; the bridge
// sits at the call site, and Gen_002B3190 stays only the receiver view so this
// object emits no body under the pinned placeholder name.
void j_00043441();

class Gen_002B3190 {};

static void invokeWorkerBaseXfer(Gen_002B3190 *base, BfmeSeedTarget *xfer)
{
	union
	{
		void (*raw)(void);
		void (Gen_002B3190::*typed)(BfmeSeedTarget *);
	} accept;
	accept.raw = &j_00043441;
	(base->*accept.typed)(xfer);
}

struct BfmeFormattedText
{
	char *m_text;
	int m_tag;
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};
class Xfer; class MidVirtualSlot90Receiver;
extern Xfer & __cdecl Rva0010C3C0(MidVirtualSlot90Receiver *, void *);

class BfmeSubAccept_0002C41C
{
public:
	void bfmeAccept(BfmeSeedTarget *);
};

class Rva002C87B0Worker
{
public:
	void xfer(Xfer *xfer);

private:
	struct Task
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	};

	struct DockPoint
	{
		UnsignedInt m_valid;
		float m_location[3];
	};

	char m_pad00[0x34c];
	Task m_task[3];
	UnsignedInt m_currentTask;
	DockPoint m_dockPoint[3][3];
	UnsignedInt m_buildSubTask;
	UnsignedInt m_isRebuild;
	ObjectID m_preferredDock;
	float m_preferredDockLocation[3];
	unsigned char m_forcePending;
	char m_pad411[3];
	UnsignedInt m_unknown414;
	unsigned char m_forcedBusyPending;
	unsigned char m_unknown419;
	unsigned char m_unknown41a;
	char m_pad41b;
	void *m_workerMachine;
	void *m_dozerMachine;
	void *m_supplyTruckStateMachine;
	char m_buildingSound[0x70];
	char m_suppliesDepletedVoice[0x70];
};

void Rva002C87B0Worker::xfer(Xfer *xfer)
{
	invokeWorkerBaseXfer(reinterpret_cast<Gen_002B3190 *>(this),
		reinterpret_cast<BfmeSeedTarget *>(xfer));

	if (xfer->isLightCRC())
		return;

	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	xfer->xferVersion(&version);

	int numTasks = 3;
	xfer->xferInt(&numTasks);
	if (numTasks != 3)
	{
		throw XferException(5, 0);
	}

	UnsignedInt *taskOrderFrame = &m_task[0].m_taskOrderFrame;
	for (int i = 0; i < 3; ++i)
	{
		Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, reinterpret_cast<int *>(taskOrderFrame - 1));
		xfer->xferUnsignedInt(taskOrderFrame);
		taskOrderFrame += 2;
	}

	xfer->xferSnapshot(m_dozerMachine);
	xfer->xferUser(&m_currentTask, sizeof(m_currentTask));

	int dockPoints = 3;
	xfer->xferInt(&dockPoints);
	if (dockPoints != 3)
	{
		throw XferException(5, 0);
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			xfer->xferBool(reinterpret_cast<UnsignedInt *>(
				&m_dockPoint[i][j].m_valid));
			xfer->xferCoord3D(m_dockPoint[i][j].m_location);
		}
	}

	xfer->xferUser(&m_buildSubTask, sizeof(m_buildSubTask));
	xfer->xferSnapshot(m_supplyTruckStateMachine);
	Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, reinterpret_cast<int *>(&m_preferredDock));
	xfer->xferCoord3D(m_preferredDockLocation);
	xfer->xferBool(reinterpret_cast<UnsignedInt *>(&m_forcePending));
	xfer->xferInt(reinterpret_cast<int *>(&m_isRebuild));
	xfer->xferBool(reinterpret_cast<UnsignedInt *>(&m_forcedBusyPending));
	xfer->xferBool(reinterpret_cast<UnsignedInt *>(&m_unknown41a));
	xfer->xferBool(reinterpret_cast<UnsignedInt *>(&m_unknown419));
	xfer->xferSnapshot(m_workerMachine);

	reinterpret_cast<BfmeSubAccept_0002C41C *>(m_suppliesDepletedVoice)->bfmeAccept(
		reinterpret_cast<BfmeSeedTarget *>(xfer));
	reinterpret_cast<BfmeSubAccept_0002C41C *>(m_buildingSound)->bfmeAccept(
		reinterpret_cast<BfmeSeedTarget *>(xfer));
	xfer->xferUnsignedInt(&m_unknown414);
}
