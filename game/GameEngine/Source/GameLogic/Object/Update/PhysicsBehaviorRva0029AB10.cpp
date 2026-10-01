// cl: /DNDEBUG /MD /EHsc
// Address-labelled PhysicsBehavior force and wake transition.
struct Rva0029AB10Coord3D
{
	float x, y, z;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class Rva0029AB10FlagOwner
{
public:
	virtual void reset();
};

class Object
{
public:
	void bfmeRecordTransform(unsigned int frame);
	char m_pad00[0x38];
	Rva0029AB10Coord3D m_position;
	char m_pad44[0x214 - 0x44];
	Object *m_containedBy;
};

class UpdateModule
{
public:
	void setWakeFrame(Object *object, int when);
};

class Rva0029AB10GameLogic
{
public:
	char m_pad00[0x3c];
	unsigned int m_frame;
};
// Retail [0x012F0898] is EA's GameLogic *TheGameLogic (see
// game/GameEngine/Source/GameLogic/System/GameLogic.cpp); the canonical
// declaration is what links. Only the +0x3c frame slot is recovered here, so
// the view is cast at the use.
class GameLogic;
extern GameLogic *TheGameLogic;

class PhysicsBehavior : public UpdateModule
{
public:
	unsigned char rva0029A150(int option, float strength);
	void rva0029AB10(const Rva0029AB10Coord3D *where, float strength, unsigned int when);
	char m_pad00[8];
	Object *m_object;
	char m_pad0c[0x10-0x0c];
	Rva0029AB10FlagOwner m_flag;
	char m_pad14[0x2c-0x14];
	Rva0029AB10Coord3D m_originalPosition;
	Rva0029AB10Coord3D m_targetPosition;
	unsigned int m_when;
	char m_pad48[0x50-0x48];
	unsigned int m_wakeFlag;
};

void PhysicsBehavior::rva0029AB10(const Rva0029AB10Coord3D *where,
	float strength, unsigned int when)
{
	Object *object = m_object;
	Object *containedBy = object->m_containedBy;
	if (containedBy)
	{
		char *templateValue = *(char **)((char *)containedBy + 4);
		if (templateValue)
		{
			const Overridable *override = *(Overridable **)(templateValue + 4);
			if (override)
				templateValue = (char *)override->getFinalOverride();
		}
		if ((*(unsigned int *)(templateValue + 0xd4) & 0x1000) == 0)
		{
			setWakeFrame(object, 0x3fffffff);
			return;
		}
	}
	m_targetPosition = *where;
	m_originalPosition = object->m_position;
	m_when = when;
	if (rva0029A150(1, strength))
	{
		m_wakeFlag = 0;
		m_flag.reset();
		m_object->bfmeRecordTransform(((Rva0029AB10GameLogic *)TheGameLogic)->m_frame);
		m_flag.reset();
		setWakeFrame(m_object, 1);
	}
}
