// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// AIMoveOntoWallState::xfer, retail 0x00181C10 (210B).

#include "StringInline.h"

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

class Xfer;
class Object;

class StateMachine
{
public:
	virtual void slot00();

	Object *getOwner()
	{
		return m_owner;
	}

private:
	unsigned char m_machineFields04[0x0c];
	Object *m_owner;
	unsigned char m_machineFields14[0x10];
	unsigned char m_goalPosition[0x0c];
	unsigned char m_machineTail[0x14];
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion &version);
	virtual void slot11();
	virtual void xferSnapshot(StateMachine &snapshot);
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

// The retail call site reaches the 0x001F654 incremental-link thunk, whose
// body is the MoveOntoWallStateMachine constructor also called by the matched onEnter at
// 0x001819F0. Keep that proven call target instead of substituting the
// similarly shaped AIAttackThenIdleStateMachine constructor at 0x00184A40.
class MoveOntoWallStateMachine : public StateMachine
{
public:
	MoveOntoWallStateMachine(Object *owner, AsciiString name);
};

class AIMoveOntoWallState
{
protected:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void xfer(Xfer *xfer);

	// The constructor at 0x00171D50 installs the AIMoveOntoWallState vtable;
	// its +0x0c slot is this body and its +0x10 slot is the matched onEnter
	// body at 0x00181D20. The xfer ABI stores the machine at +0x24.
	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateTail[4];
	MoveOntoWallStateMachine *m_moveMachine;

	Object *getMachineOwner()
	{
		return m_machine->getOwner();
	}
};

typedef char MoveMachineSize[(sizeof(MoveOntoWallStateMachine) == 0x44) ? 1 : -1];
typedef char WallVersionSize[(sizeof(XferVersion) == 2) ? 1 : -1];
typedef char WallStringSize[(sizeof(AsciiString) == 4) ? 1 : -1];

void AIMoveOntoWallState::xfer(Xfer *xfer)
{
	XferVersion version(1, 1);
	xfer->xferVersion(version);

	bool hasMachine = m_moveMachine != 0;
	xfer->xferBool(hasMachine);

	if (hasMachine && m_moveMachine == 0)
		m_moveMachine = new MoveOntoWallStateMachine(
			getMachineOwner(), AsciiString("AIAttackMachine"));

	if (hasMachine)
		xfer->xferSnapshot(*m_moveMachine);
}
