// cl: /DNDEBUG /MD /EHsc

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	XferVersion(UnsignedByte version, UnsignedByte currentVersion) :
		m_version(version), m_currentVersion(currentVersion)
	{
	}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isLightCRC();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void slot07();
	virtual void slot08(void *machine, int block);
	virtual void xferUser(void *data, int size);
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(void *snapshot);
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
	virtual void xferCoord3D(Coord3D *value);
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
	virtual void xferBool(Bool *value);
};

class StateMachine
{
public:
	char m_stateMachineFields[0x10];
	Object *m_owner;
};

class AttackStateMachine
{
};

class AIAttackState
{
protected:
	virtual void xfer(Xfer *xfer);

	char m_stateFieldsPrefix[0x18];
	StateMachine *m_machine;
	char m_stateFieldsSuffix[0x08];
	AttackStateMachine *m_attackMachine;
	char m_attackStateFields[0x08];
	Coord3D m_originalVictimPos;
	char m_lockedWeaponOnEnter[0x08];
	ObjectID m_bfmeAttackState48;
	Bool m_bfmeAttackState4C;
	Bool m_bfmeAttackState4D;
	char m_bfmeAttackState4E[2];
	UnsignedInt m_attackMachineType;

	void createAttackMachine(Object *owner);
};

extern void friend_xferObjectID(Xfer *xfer, ObjectID *id);

#pragma comment(linker, "/alternatename:?createAttackMachine@AIAttackState@@IAEXPAVObject@@@Z=?j_0004121d@@YAXXZ")

// ?xfer@AIAttackState@@MAEXPAVXfer@@@Z
void AIAttackState::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferVersion version(1, 3);
	xfer->xferVersion(&version);

	Bool hasMachine = m_attackMachine != 0;
	xfer->xferBool(&hasMachine);
	xfer->xferCoord3D(&m_originalVictimPos);
	xfer->xferUser(&m_attackMachineType, sizeof(m_attackMachineType));

	if (hasMachine && m_attackMachine == 0)
	{
		Object *owner = m_machine->m_owner;
		createAttackMachine(owner);
	}

	if (hasMachine)
	{
		if (version.m_currentVersion >= 3)
		{
			if (xfer->isSaving())
			{
				xfer->beginBlock("AIAttackState_attackMachine");
				xfer->xferSnapshot(m_attackMachine);
				xfer->endBlock();
			}
			else
			{
				int block;
				try
				{
					block = xfer->beginBlock("AIAttackState_attackMachine");
					xfer->xferSnapshot(m_attackMachine);
					xfer->endBlock();
				}
				catch (...)
				{
					xfer->slot08(m_attackMachine, block);
					m_attackMachine = 0;
					Object *owner = m_machine->m_owner;
					createAttackMachine(owner);
				}
			}
		}
		else
		{
			xfer->xferSnapshot(m_attackMachine);
		}
	}

	friend_xferObjectID(xfer, &m_bfmeAttackState48);
	xfer->xferBool(&m_bfmeAttackState4C);
	if (version.m_currentVersion > 1)
		xfer->xferBool(&m_bfmeAttackState4D);
}
