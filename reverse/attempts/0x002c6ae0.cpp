// ??0SupplyTruckAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.88 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: readable SupplyTruckAIUpdate constructor.  The BFME object keeps
// the AIUpdateInterface five-way base layout used by the exact WorkerAIUpdate
// constructor, then appends a SupplyTruckAIInterface subobject at +0x340.
// The extra bytes at +0x358..+0x363 are retained as observed BFME fields; the
// semantic names belong to the full class source, not to this ABI view.

class Object;
class Thing;
class ModuleData;
class AsciiString;

typedef int Int;
typedef unsigned int ObjectID;
typedef int Bool;

class __declspec(novtable) AIUpdateCore
{
public:
	virtual ~AIUpdateCore();

	const ModuleData *m_moduleData;
	Thing *m_object;
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

#pragma comment(linker, "/alternatename:??0AIUpdateInterface@@QAE@PAVThing@@PBVModuleData@@@Z=?j_000292a3@@YAXXZ")

class SupplyTruckAIInterface
{
public:
	virtual Int getNumberBoxes() const = 0;
	virtual Bool loseOneBox() = 0;
	virtual Bool gainOneBox(Int) = 0;
	virtual Bool isAvailableForSupplying() const = 0;
	virtual Bool isCurrentlyFerryingSupplies() const = 0;
	virtual float getWarehouseScanDistance() const = 0;
	virtual void setForceWantingState(Bool) = 0;
	virtual Bool isForcedIntoWantingState() const = 0;
	virtual void setForceBusyState(Bool) = 0;
	virtual Bool isForcedIntoBusyState() const = 0;
	virtual ObjectID getPreferredDockID() const = 0;
	virtual unsigned int getActionDelayForDock(Object *) = 0;
	virtual Int getUpgradedSupplyBoost() const = 0;
};

class AudioEventRTS
{
public:
	// This is the BFME two-argument default route at ILT 0x00025306.
	AudioEventRTS(void *allocator = (void *)0x01336e50, int zero = 0);
	virtual ~AudioEventRTS();
	AudioEventRTS &operator=(const AudioEventRTS &right);

private:
	unsigned char m_data[0x6c];
};

class SupplyTruckStateMachine
{
public:
	SupplyTruckStateMachine(Object *owner);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void initDefaultState();

private:
	// The retail allocation is push 0x44.  The first four bytes are the vptr.
	unsigned char m_data[0x40];
};

class SupplyTruckAIUpdate : public AIUpdateInterface, public SupplyTruckAIInterface
{
public:
	SupplyTruckAIUpdate(Thing *, const ModuleData *);
	Object *getObject() const
	{
		return reinterpret_cast<Object *>(m_object);
	}

private:
	SupplyTruckStateMachine *m_supplyTruckStateMachine;
	ObjectID m_preferredDock;
	Int m_numberBoxes;
	Bool m_forcePending;
	Bool m_forcedBusyPending;
	unsigned char m_bfme358;
	unsigned char m_bfme359_35b[3];
	unsigned int m_bfme35c;
	unsigned char m_bfme360;
	unsigned char m_bfme361;
	unsigned char m_bfme362_363[2];
	AudioEventRTS m_suppliesDepletedVoice;
};

// ??0SupplyTruckAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SupplyTruckAIUpdate::SupplyTruckAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData)
{
	m_supplyTruckStateMachine = 0;
	m_preferredDock = 0;
	m_numberBoxes = 0;
	m_forcePending = 0;
	m_forcedBusyPending = 0;
	m_bfme358 = 0;
	m_bfme35c = 0;
	m_bfme360 = 0;
	m_bfme361 = 0;
	m_supplyTruckStateMachine = new SupplyTruckStateMachine(getObject());
	m_supplyTruckStateMachine->initDefaultState();
	m_suppliesDepletedVoice = *reinterpret_cast<const AudioEventRTS *>(
		reinterpret_cast<const unsigned char *>(m_moduleData) + 0x84);
}
