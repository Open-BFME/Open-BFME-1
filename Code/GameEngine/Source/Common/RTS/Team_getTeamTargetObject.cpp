// cl: /DNDEBUG /MD /EHsc
//
// Team::getTeamTargetObject. Zero Hour's body: resolve the stored id, drop
// stealthed/dead/contained targets, and clear the id when the target is gone.
// BFME asks isStealthedAndUndetected with the controlling player as viewer,
// tests a flag at Object+0x344, and treats Object+0x214 as getContainedBy.

class Object;
class Player;

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheBfmeGameLogic;				// retail [0x012F0898]

class TeamPrototype
{
public:
	char m_pad[8];
	Player *m_owningPlayer;					// +8
};

class Object
{
public:
	bool isStealthedAndUndetected(const Object *viewer) const;

	char m_pad0[0x214];
	void *m_containedBy;					// +0x214
	char m_pad1[0x12C];					// 0x344 - 0x218
	unsigned char m_flag344;				// +0x344
};

class Team
{
public:
	Object *getTeamTargetObject();

private:
	char m_pad0[4];
	TeamPrototype *m_proto;					// +4
	char m_pad1[0xE0];					// 0xE8 - 8
	int m_commonAttackTarget;				// +0xE8
};

Object *Team::getTeamTargetObject()
{
	if (m_commonAttackTarget == 0)
		return 0;

	Object *target = TheBfmeGameLogic->findObjectByID(m_commonAttackTarget);
	if (target)
	{
		TeamPrototype *proto = m_proto;
		if (proto)
			proto = (TeamPrototype *)proto->m_owningPlayer;
		if (target->isStealthedAndUndetected((const Object *)proto))
			target = 0;
		else if (target->m_flag344 & 1)
			target = 0;
		else if (target->m_containedBy)
			target = 0;
		else
			return target;
	}
	m_commonAttackTarget = 0;
	return target;
}
