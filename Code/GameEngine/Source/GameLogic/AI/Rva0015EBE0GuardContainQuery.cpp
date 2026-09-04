// cl: /DNDEBUG /MD /EHsc
// Retail 0x0015EBE0, 72 bytes. Same-dump leftover as lookForInnerTarget.
// State+0x44 object-id, machine at +0x1C, owner at machine+0x10, contain at
// Object+0x1FC, then contain virt +0x68 (getHordeContainInterface) and
// that interface's virt +0x48 with (0, ownerPos, 0).

typedef int ObjectID;

struct Coord3D
{
	float x, y, z;
};

class Object;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;				// 0x012F0898

class HordeContainInterface
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
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual int queryAt48(int a, Coord3D *pos, int b) = 0;	// +0x48
};

class ContainModuleInterface
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
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;	// +0x68
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_pos;								// +0x38
	unsigned char m_pad44[0x1FC - 0x44];
	ContainModuleInterface *m_contain;			// +0x1FC
};

class StateMachine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;							// +0x10
};

class Rva0015EBE0State
{
public:
	int queryGuardContain();

	unsigned char m_pad00[0x1C];
	StateMachine *m_machine;					// +0x1C
	unsigned char m_pad20[0x44 - 0x20];
	ObjectID m_targetId;						// +0x44
};

int Rva0015EBE0State::queryGuardContain()
{
	ObjectID id = m_targetId;
	if (id)
	{
		Object *obj = TheGameLogic->findObjectByID(id);
		if (obj)
		{
			Object *owner = m_machine->m_owner;
			ContainModuleInterface *contain = obj->m_contain;
			if (contain)
			{
				HordeContainInterface *horde = contain->getHordeContainInterface();
				if (horde)
				{
					owner = (Object *)((unsigned)owner + 0x38);
					return horde->queryAt48(0, (Coord3D *)owner, 0);
				}
			}
		}
	}
	return 0;
}
