// cl: /DNDEBUG /MD /EHsc
// WorkerAIUpdate::xfer, retail RVA 0x002C87B0.  The semantic identity is
// established by the Worker field sequence and the landed Worker neighbours;
// this TU keeps the address in its class name until the generated claim is
// replaced by the proven body.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;
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

class Gen_002B3190
{
private:
	void bfmeAccept(BfmeSeedTarget *);
	friend void invokeWorkerBaseXfer(Gen_002B3190 *, BfmeSeedTarget *);
};

static void invokeWorkerBaseXfer(Gen_002B3190 *base, BfmeSeedTarget *xfer)
{
	base->bfmeAccept(xfer);
}

struct BfmeFormattedText
{
	char *m_text;
	int m_tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern void __cdecl bfmeCalcTGC(void *, int *);

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
		BfmeFormattedText error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	UnsignedInt *taskOrderFrame = &m_task[0].m_taskOrderFrame;
	for (int i = 0; i < 3; ++i)
	{
		bfmeCalcTGC(xfer, reinterpret_cast<int *>(taskOrderFrame - 1));
		xfer->xferUnsignedInt(taskOrderFrame);
		taskOrderFrame += 2;
	}

	xfer->xferSnapshot(m_dozerMachine);
	xfer->xferUser(&m_currentTask, sizeof(m_currentTask));

	int dockPoints = 3;
	xfer->xferInt(&dockPoints);
	if (dockPoints != 3)
	{
		BfmeFormattedText error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
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
	bfmeCalcTGC(xfer, reinterpret_cast<int *>(&m_preferredDock));
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
