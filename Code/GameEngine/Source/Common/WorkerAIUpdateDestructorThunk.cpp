// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: convert WorkerAIUpdate::~WorkerAIUpdate to clean C++.
//
// The retail BFME object has the module's eight polymorphic subobjects at
// 0x00, 0x0c, 0x10, 0x20, 0x24, 0x340, 0x344 and 0x348.  These small local
// base views preserve those boundaries while leaving the ZH header untouched.
// The first base is the out-of-line BFME destructor at 0x0001c774; the other
// interface tails are empty in this destructor and only contribute their
// vptr stores.

class Rva0001C774FlatBase
{
public:
	virtual ~Rva0001C774FlatBase();

private:
	unsigned char m_pad[0x08];
};

class BfmeWorkerInterfaceTail0
{
public:
	virtual void marker();
};

class BfmeWorkerInterfaceTail1
{
public:
	virtual void marker();

private:
	unsigned char m_pad[0x0c];
};

class BfmeWorkerInterfaceTail2
{
public:
	virtual void marker();
};

class BfmeWorkerInterfaceTail3
{
public:
	virtual void marker();

private:
	unsigned char m_pad[0x318];
};

class BfmeWorkerInterfaceTail4
{
public:
	virtual void marker();
};

class BfmeWorkerInterfaceTail5
{
public:
	virtual void marker();
};

class BfmeWorkerInterfaceTail6
{
public:
	virtual void marker();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WorkerAIUpdate.h
class WorkerStateMachine
{
public:
	virtual ~WorkerStateMachine();
	void deleteInstance() { delete this; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h
class DozerPrimaryStateMachine
{
public:
	virtual ~DozerPrimaryStateMachine();
	void deleteInstance() { delete this; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h
class SupplyTruckStateMachine
{
public:
	virtual ~SupplyTruckStateMachine();
	void deleteInstance() { delete this; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();

private:
	unsigned char m_data[0x6c];
};

class BfmeWorkerDockPoint
{
public:
	~BfmeWorkerDockPoint();

private:
	unsigned char m_data[0x10];
};

class WorkerAIUpdate
	: public Rva0001C774FlatBase,
	  public BfmeWorkerInterfaceTail0,
	  public BfmeWorkerInterfaceTail1,
	  public BfmeWorkerInterfaceTail2,
	  public BfmeWorkerInterfaceTail3,
	  public BfmeWorkerInterfaceTail4,
	  public BfmeWorkerInterfaceTail5,
	  public BfmeWorkerInterfaceTail6
{
public:
	virtual ~WorkerAIUpdate();

private:
	unsigned char m_beforeDockPoints[0x1c];
	BfmeWorkerDockPoint m_dockPoint[9];
	unsigned char m_betweenDockPointsAndMachines[0x24];
	WorkerStateMachine *m_workerMachine;
	DozerPrimaryStateMachine *m_dozerMachine;
	SupplyTruckStateMachine *m_supplyTruckStateMachine;
	AudioEventRTS m_buildingSound;
	AudioEventRTS m_suppliesDepletedVoice;
};

// ??1WorkerAIUpdate@@UAE@XZ
WorkerAIUpdate::~WorkerAIUpdate()
{
	if (m_dozerMachine)
		m_dozerMachine->deleteInstance();
	m_dozerMachine = 0;

	if (m_supplyTruckStateMachine)
		m_supplyTruckStateMachine->deleteInstance();
	m_supplyTruckStateMachine = 0;

	if (m_workerMachine)
		m_workerMachine->deleteInstance();
	m_workerMachine = 0;
}
