// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class Object;
class Player;

// The reference names this callback. Its BFME implementation is the empty
// ret-4 body at RVA 0x000EA900. Use the existing neutral ILT binding with the
// proven thiscall ABI; no new canonical identity pin is introduced here.
extern void j_00008d9b();
class ScoreKeeper
{
public:
	void addObjectCaptured(const Object *object)
	{
		union
		{
			void *address;
			void (ScoreKeeper::*call)(const Object *);
		} route;
		route.address = (void *)j_00008d9b;
		(this->*route.call)(object);
	}
};

class Player
{
public:
	ScoreKeeper *getScoreKeeper()
	{
		return &m_scoreKeeper;
	}

	Bool isLocalPlayer() const;

private:
	unsigned char m_unmodelled000[0x348];
	ScoreKeeper m_scoreKeeper;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	RETAIL_COMMAND_SOURCE_2 = 2
};

// The interface is declaration-only: retail calls the nonvirtual helper through
// the embedded command interface at AIUpdateInterface+0x20.
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class AIUpdateInterface
{
private:
	unsigned char m_unmodelled000[0x20];

public:
	AICommandInterface m_commandInterface;
};

// ObjectModule::onCapture is the tenth slot of the primary module table, at
// +0x24.  No object is instantiated in this TU, so this declaration emits no
// vtable; the complete used slot prefix is retained to document the ABI.
class BehaviorModule
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void onCapture(Player *oldOwner, Player *newOwner) = 0;
};

class PartitionData
{
public:
	void makeDirty();
};

class Rva009A2350
{
public:
	void init();
};

class Rva009F2BA0
{
public:
	void init();
};

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_UNSELLABLE = 4
};

class Object
{
public:
	void onCapture(Player *oldOwner, Player *newOwner);
	void setScriptStatus(ObjectScriptStatusBit bit, Bool set);
	void clearScriptStatus(ObjectScriptStatusBit bit);
};

class ControlBar
{
public:
	unsigned char m_unmodelled000[0x24];
	Bool m_UIDirty;
};

extern ControlBar *TheControlBar;

// The BFME Object fields touched by this body.  The neighbouring Object TUs
// independently establish the +0x3B0/+0x3B4/+0x3B8 maintenance fields; this
// view additionally records the BFME AI and behavior-array offsets read here.
class BfmeObjectOnCaptureFields
{
public:
	unsigned char m_unmodelled000[0x1F0];
	BehaviorModule **m_behaviors;
	unsigned char m_unmodelled1F4[0x10];
	AIUpdateInterface *m_ai;
	unsigned char m_unmodelled208[0x1A8];
	PartitionData *m_partitionData;
	Rva009F2BA0 *m_helper3B4;
	Rva009A2350 *m_helper3B8;
};

// ?onCapture@Object@@QAEXPAVPlayer@@0@Z
void Object::onCapture(Player *oldOwner, Player *newOwner)
{
	BfmeObjectOnCaptureFields *fields =
		reinterpret_cast<BfmeObjectOnCaptureFields *>(this);

	if (fields->m_ai != 0 && oldOwner != newOwner)
		fields->m_ai->m_commandInterface.aiIdle(RETAIL_COMMAND_SOURCE_2);

	newOwner->getScoreKeeper()->addObjectCaptured(this);

	for (BehaviorModule **module = fields->m_behaviors; *module; ++module)
		(*module)->onCapture(oldOwner, newOwner);

	if (fields->m_partitionData)
		fields->m_partitionData->makeDirty();

	if (fields->m_helper3B8)
		fields->m_helper3B8->init();

	if (fields->m_helper3B4)
		fields->m_helper3B4->init();

	setScriptStatus(OBJECT_STATUS_SCRIPT_UNSELLABLE, false);

	if (oldOwner->isLocalPlayer() || newOwner->isLocalPlayer())
		TheControlBar->m_UIDirty = true;
}

// The prior unmatched onCapture body was the only Object.cpp use that emitted
// this inline helper. Keep its existing 15-byte retail body here explicitly.
// ?clearScriptStatus@Object@@QAEXW4ObjectScriptStatusBit@@@Z
void Object::clearScriptStatus(ObjectScriptStatusBit bit)
{
	setScriptStatus(bit, false);
}
