// ?lookForInnerTarget@AITNGuardMachine@@QAE_NXZ
// partial score=0.45 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc
// stlport
// BFME layout reconstruction of AITNGuardMachine::lookForInnerTarget at
// retail RVA 0x0018A240.  The ZH twin is the source of the scan logic;
// these views carry only the BFME offsets witnessed by the retail body.

#include <list>

typedef int ObjectID;
typedef unsigned int UnsignedInt;

enum Relationship
{
	ENEMIES = 0
};

enum AbleToAttackType
{
	ATTACK_TUNNEL_NETWORK_GUARD = 4
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum CanAttackResult
{
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

class Object;
class Team;
class TeamPrototype;
class Player;
class TunnelTracker;
class StateMachine;
class AIUpdateInterface;
class BodyModuleInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	unsigned char m_input[8];
	ObjectID m_sourceID;
	unsigned char m_between[0x58 - 0x0c];
	unsigned char m_noEffect;
};

// The BFME BodyModuleInterface keeps these two scan methods at vtable
// offsets +0x3c and +0x40.
class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual const DamageInfo *getLastDamageInfo() const = 0;
	virtual UnsignedInt getLastDamageTimestamp() const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual ~StateMachine();

	Object *getOwner()
	{
		return *(Object **)((unsigned char *)this + 0x10);
	}

	Object *getOwner() const
	{
		return *(Object **)((const unsigned char *)this + 0x10);
	}

	Object *getGoalObject();

private:
	unsigned char m_layout[0x40];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	Object *getGoalObject()
	{
		return m_stateMachine->getGoalObject();
	}

private:
	unsigned char m_beforeStateMachine[0x30];
	StateMachine *m_stateMachine;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Team *getTeam() const
	{
		return m_team;
	}

	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object *that) const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType type,
		const Object *target, CommandSourceType source) const;

	ObjectID getID() const
	{
		return m_id;
	}

	BodyModuleInterface *getBodyModule() const
	{
		return m_body;
	}

	AIUpdateInterface *getAI()
	{
		return m_ai;
	}

private:
	unsigned char m_beforeID[0x74];
	ObjectID m_id;
	unsigned char m_beforeBody[0x200 - 0x78];
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
	unsigned char m_beforeTeam[0x23c - 0x208];
	Team *m_team;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	unsigned char m_beforeTemplateInfo[0x1c2];
	unsigned char m_attackCommonTarget;

	TeamPrototype *getTemplateInfo()
	{
		return this;
	}
};

class Team
{
public:
	TeamPrototype *getPrototype()
	{
		return m_proto;
	}

	Object *getTeamTargetObject();
	void setTeamTargetObject(const Object *target);

private:
	unsigned char m_beforeProto[4];
	TeamPrototype *m_proto;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	TunnelTracker *getTunnelSystem()
	{
		return m_tunnelSystem;
	}

private:
	unsigned char m_beforeTunnelSystem[0x22c];
	TunnelTracker *m_tunnelSystem;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	Object *getCurNemesis();
	void updateNemesis(const Object *target);

	const std::list<ObjectID> *getContainerList() const
	{
		return &m_tunnelIDs;
	}

private:
	void *m_snapshotVtable;
	std::list<ObjectID> m_tunnelIDs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	UnsignedInt getFrame() const
	{
		return m_frame;
	}

private:
	unsigned char m_beforeFrame[0x3c];
	UnsignedInt m_frame;
};

class AIData
{
public:
	unsigned char m_beforeGuardEnemyScanRate[0x40];
	UnsignedInt m_guardEnemyScanRate;
};

class AI
{
public:
	AIData *getAiData()
	{
		return m_aiData;
	}

private:
	unsigned char m_beforeAiData[0x14];
	AIData *m_aiData;
};

extern GameLogic *TheGameLogic;
extern AI *TheAI;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva0018A240AITNGuardMachine : public StateMachine
{
public:
	void setNemesisID(ObjectID id)
	{
		m_nemesisToAttack = id;
	}

	// ?lookForInnerTarget@AITNGuardMachine@@QAE_NXZ
	bool lookForInnerTarget();

private:
	Coord3D m_positionToGuard;
	volatile ObjectID m_nemesisToAttack;
	volatile unsigned int m_guardMode;
};

// ?lookForInnerTarget@AITNGuardMachine@@QAE_NXZ
bool Rva0018A240AITNGuardMachine::lookForInnerTarget()
{
	Object *owner = getOwner();

	Object *teamVictim = 0;
	if (owner->getTeam()->getPrototype()->getTemplateInfo()->m_attackCommonTarget)
	{
		teamVictim = owner->getTeam()->getTeamTargetObject();
		if (teamVictim)
		{
			setNemesisID(teamVictim->getID());
			return true;
		}
	}

	Player *ownerPlayer = getOwner()->getControllingPlayer();
	if (!ownerPlayer)
		return false;

	TunnelTracker *tunnels = ownerPlayer->getTunnelSystem();
	if (tunnels == 0)
		return false;

	if (tunnels->getCurNemesis())
	{
		setNemesisID(tunnels->getCurNemesis()->getID());
		return true;
	}

	const std::list<ObjectID> *allTunnels = tunnels->getContainerList();
	for (std::list<ObjectID>::const_iterator iter = allTunnels->begin();
		iter != allTunnels->end(); iter++)
	{
			Object *currentTunnel = TheGameLogic->findObjectByID(*iter);
			if (currentTunnel)
			{
				if (currentTunnel->getAI())
				{
					Object *victim = currentTunnel->getAI()->getGoalObject();
					if (owner->getRelationship(victim) == ENEMIES)
					{
						setNemesisID(victim->getID());
						return true;
					}
				}

				BodyModuleInterface *body = currentTunnel->getBodyModule();
				if (body)
				{
					const DamageInfo *info = body->getLastDamageInfo();
					if (info)
					{
						if (info->m_noEffect)
							continue;

						if (body->getLastDamageTimestamp()
							+ TheAI->getAiData()->m_guardEnemyScanRate
							> TheGameLogic->getFrame())
						{
							ObjectID attackerID = info->m_sourceID;
							Object *attacker = TheGameLogic->findObjectByID(attackerID);
							if (attacker)
							{
								if (owner->getRelationship(attacker) != ENEMIES)
									continue;

								CanAttackResult result = getOwner()->getAbleToAttackSpecificObject(
									ATTACK_TUNNEL_NETWORK_GUARD, attacker, CMD_FROM_AI);
								if (result == ATTACKRESULT_POSSIBLE
									|| result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
								{
								setNemesisID(attackerID);
									owner->getTeam()->setTeamTargetObject(attacker);
									tunnels->updateNemesis(attacker);
									return true;
								}
							}
						}
					}
				}
			}
	}

	return false;
}
