// cl: /O2

class Thing;
class ModuleData;
class AsciiString;

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int Bool;
typedef int ObjectID;
typedef float Real;

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

class __declspec(novtable) AIUpdateCore
{
public:
	virtual ~AIUpdateCore();

	const ModuleData *m_moduleData;
	unsigned char m_pad[4];
};

class __declspec(novtable) AIUpdateTail0
{
public:
	virtual void marker();
};

class __declspec(novtable) AIUpdateTail1
{
public:
	virtual void marker();

private:
	unsigned char m_pad[0x0c];
};

class __declspec(novtable) AIUpdateTail2
{
public:
	virtual void marker();
};

class __declspec(novtable) AIUpdateTail3
{
public:
	virtual void marker();

private:
	unsigned char m_pad[0x318];
};

class BfmeWorkerInterfaceTail0
{
public:
	virtual void marker() = 0;
};

class BfmeWorkerInterfaceTail1
{
public:
	virtual void marker() = 0;
};

class BfmeWorkerInterfaceTail2
{
public:
	virtual void marker() = 0;
};

class AIUpdateInterface
	: public AIUpdateCore,
	  public AIUpdateTail0,
	  public AIUpdateTail1,
	  public AIUpdateTail2,
	  public AIUpdateTail3
{
public:
	AIUpdateInterface(Thing *, const ModuleData *);
	virtual ~AIUpdateInterface();
};

class WorkerStateMachine;
class DozerPrimaryStateMachine;
class SupplyTruckStateMachine;

class BfmeWorkerDockPoint
{
public:
	BfmeWorkerDockPoint();
	~BfmeWorkerDockPoint();

	unsigned char valid;
	Coord3D location;
};

class AudioEventRTS
{
public:
	AudioEventRTS(void *allocator = (void *)0x01336e50, int zero = 0);
	virtual ~AudioEventRTS();
	AudioEventRTS &operator=(const AudioEventRTS &right);

private:
	unsigned char m_data[0x6c];
};

#pragma comment(linker, "/alternatename:??0BfmeWorkerDockPoint@@QAE@XZ=?j_0000fd6c@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeWorkerDockPoint@@QAE@XZ=?j_000211ca@@YAXXZ")

class WorkerAIUpdate
	: public AIUpdateInterface,
	  public BfmeWorkerInterfaceTail0,
	  public BfmeWorkerInterfaceTail1,
	  public BfmeWorkerInterfaceTail2
{
public:
	WorkerAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~WorkerAIUpdate();

private:
	void createMachines();

	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	} m_task[3];

	Int m_currentTask;
	BfmeWorkerDockPoint m_dockPoint[3][3];
	Int m_buildSubTask;
	Int m_numberBoxes;
	ObjectID m_preferredDock;
	Bool m_forcePending;
	Bool m_isRebuild;
	Bool m_forcedBusyPending;
	unsigned char m_bfme410;
	unsigned char m_bfme411_413[3];
	unsigned int m_bfme414;
	unsigned char m_bfme418;
	unsigned char m_bfme419;
	unsigned char m_bfme41a;
	unsigned char m_bfme41b;
	WorkerStateMachine *m_workerMachine;
	DozerPrimaryStateMachine *m_dozerMachine;
	SupplyTruckStateMachine *m_supplyTruckStateMachine;
	AudioEventRTS m_buildingSound;
	AudioEventRTS m_suppliesDepletedVoice;
};

// ??0WorkerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
WorkerAIUpdate::WorkerAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData), m_bfme414(0)
{
	m_bfme419 = 0;
	m_dozerMachine = 0;
	for (Int i = 0; i < 3; i++)
	{
		m_task[i].m_targetObjectID = 0;
		m_task[i].m_taskOrderFrame = 0;
		for (Int j = 0; j < 3; j++)
		{
			m_dockPoint[i][j].valid = 0;
			m_dockPoint[i][j].location.zero();
		}
	}
	m_currentTask = -1;
	m_buildSubTask = 0;

	m_supplyTruckStateMachine = 0;
	m_preferredDock = 0;
	m_forcePending = 0;
	m_isRebuild = 0;
	m_forcedBusyPending = 0;
	_ReadWriteBarrier();
	const AudioEventRTS *suppliesDepletedVoice = reinterpret_cast<const AudioEventRTS *>(
		reinterpret_cast<const char *>(m_moduleData) + 0x90);
	m_bfme410 = 0;
	m_numberBoxes = 0;
	m_bfme418 = 0;
	m_bfme41a = 0;
	m_workerMachine = 0;
	m_suppliesDepletedVoice = *suppliesDepletedVoice;
	createMachines();
}
