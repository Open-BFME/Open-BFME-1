// cl: /DNDEBUG /MD /EHsc
// AIGuardRetaliateState::xfer, retail 0x0016D820 (204B).

typedef unsigned char UnsignedByte;

struct XferVersion
{
	XferVersion(UnsignedByte version, UnsignedByte currentVersion) :
		m_version(version), m_currentVersion(currentVersion)
	{
	}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Snapshot
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual bool isLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion &version);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot &snapshot);
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
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(bool &value);
};

class Object;

class StateMachine
{
public:
	Object *getOwner() { return m_owner; }

	virtual void slot00();
	unsigned char m_machineFields04[0x0c];
	Object *m_owner;
};

class AIGuardRetaliateMachine : public Snapshot
{
public:
	AIGuardRetaliateMachine(Object *owner);

	unsigned char m_machineFields0c[0x50];
};

#pragma comment(linker, "/alternatename:??0AIGuardRetaliateMachine@@QAE@PAVObject@@@Z=?j_0003e8d3@@YAXXZ")

class AIGuardRetaliateState
{
protected:
	virtual void xfer(Xfer *xfer);

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	AIGuardRetaliateMachine *m_guardRetaliateMachine;
};

// ?xfer@AIGuardRetaliateState@@MAEXPAVXfer@@@Z
void AIGuardRetaliateState::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferVersion version(1, 1);
	xfer->xferVersion(version);

	bool hasMachine = m_guardRetaliateMachine != 0;
	xfer->xferBool(hasMachine);

	if (hasMachine && m_guardRetaliateMachine == 0)
		m_guardRetaliateMachine = new AIGuardRetaliateMachine(m_machine->getOwner());

	if (hasMachine)
		xfer->xferSnapshot(*m_guardRetaliateMachine);
}
