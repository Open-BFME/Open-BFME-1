// cl: /DNDEBUG /MD /EHsc
// AIDockState::xfer, retail 0x0016CCA0 (218B). Near twin of
// AIGuardRetaliateState::xfer (AIGuardRetaliateState_xfer.cpp); isolated
// sibling of AIDockState_onEnter.cpp / AIDockState_onExit.cpp. Differs from
// the AIGuardRetaliateState twin by one extra bool member (m_afterDockMachine)
// xferred unconditionally after the dock-machine snapshot.

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

// Real ctor already landed as AIDockMachineCtorThunk.cpp
// (object-symbol ??0AIDockMachine@@QAE@PAVObject@@@Z); this TU only needs a
// Snapshot-compatible view of it for xferSnapshot and its true field size
// (0x44) for the operator new call.
class AIDockMachine : public Snapshot
{
public:
	AIDockMachine(Object *owner);

	unsigned char m_machineFields0c[0x44];
};

class AIDockState
{
protected:
	virtual void xfer(Xfer *xfer);

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	AIDockMachine *m_dockMachine;
	bool m_afterDockMachine;
};

// ?xfer@AIDockState@@MAEXPAVXfer@@@Z
void AIDockState::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferVersion version(1, 1);
	xfer->xferVersion(version);

	bool hasMachine = m_dockMachine != 0;
	xfer->xferBool(hasMachine);

	if (hasMachine && m_dockMachine == 0)
		m_dockMachine = new AIDockMachine(m_machine->getOwner());

	if (hasMachine)
		xfer->xferSnapshot(*m_dockMachine);

	xfer->xferBool(m_afterDockMachine);
}
