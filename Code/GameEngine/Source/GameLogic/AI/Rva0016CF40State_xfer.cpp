// cl: /DNDEBUG /MD /EHsc
// Rva0016CF40State::xfer, retail 0x0016CF40 (218B). Near twin of
// AIGuardRetaliateState::xfer (AIGuardRetaliateState_xfer.cpp) and of
// AIDockState::xfer (AIDockState_xfer.cpp, 0x0016CCA0) -- identical shape,
// but the machine object is 0x44 bytes and its constructor
// (RVA 0x0015FE90, ghidra FUN_0055fe90) is still an unconverted dump, so it
// is called only through the existing gen-thunk ILT (j_0003fe4f).

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

class Rva0016CF40Machine : public Snapshot
{
public:
	Rva0016CF40Machine(Object *owner);

	unsigned char m_machineFields0c[0x40];
};

#pragma comment(linker, "/alternatename:??0Rva0016CF40Machine@@QAE@PAVObject@@@Z=?j_0003fe4f@@YAXXZ")

class Rva0016CF40State
{
protected:
	virtual void xfer(Xfer *xfer);

	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	Rva0016CF40Machine *m_stateMachine0016CF40;
	bool m_afterMachine;
};

// ?xfer@Rva0016CF40State@@MAEXPAVXfer@@@Z
void Rva0016CF40State::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferVersion version(1, 1);
	xfer->xferVersion(version);

	bool hasMachine = m_stateMachine0016CF40 != 0;
	xfer->xferBool(hasMachine);

	if (hasMachine && m_stateMachine0016CF40 == 0)
		m_stateMachine0016CF40 = new Rva0016CF40Machine(m_machine->getOwner());

	if (hasMachine)
		xfer->xferSnapshot(*m_stateMachine0016CF40);

	xfer->xferBool(m_afterMachine);
}
