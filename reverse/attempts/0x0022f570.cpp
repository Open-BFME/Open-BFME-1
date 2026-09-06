// ?d_0022f570@@YAXXZ
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TunnelContain::update against BFME's adjusted module layout.

typedef bool Bool;
typedef float Real;
typedef int ObjectID;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum Relationship
{
	ENEMIES = 0
};

struct DamageInfoInput
{
	void *m_snapshotVtable;
	ObjectID m_sourceID;
};

struct DamageInfo
{
	void *m_snapshotVtable;
	DamageInfoInput in;
};

class Object;

class TunnelTracker
{
public:
	void healObjects(Real frames);
	void updateNemesis(const Object *target);
};

class Player
{
public:
	TunnelTracker *getTunnelSystem() const { return m_tunnelSystem; }

private:
	unsigned char m_unreconstructed_000[0x22c];
	TunnelTracker *m_tunnelSystem;
};

class BodyModuleInterface
{
public:
	virtual int slot00() = 0; virtual int slot01() = 0;
	virtual int slot02() = 0; virtual int slot03() = 0;
	virtual int slot04() = 0; virtual int slot05() = 0;
	virtual int slot06() = 0; virtual int slot07() = 0;
	virtual int slot08() = 0; virtual int slot09() = 0;
	virtual int slot10() = 0; virtual int slot11() = 0;
	virtual int slot12() = 0; virtual int slot13() = 0;
	virtual int slot14() = 0;
	virtual const DamageInfo *getLastDamageInfo() const = 0;
	virtual UnsignedInt getLastDamageTimestamp() const = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Relationship getRelationship(const Object *other) const;

private:
	unsigned char m_unreconstructed_000[0x200];
	BodyModuleInterface *m_body;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned char m_unreconstructed_000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class TunnelContainModuleData
{
private:
	unsigned char m_unreconstructed_000[0x168];

public:
	Real m_framesForFullHeal;
};

extern void j_0000c1e9();

class TunnelContain
{
public:
	virtual UpdateSleepTime update();

private:
	TunnelContainModuleData *getModuleData() const
	{
		return *reinterpret_cast<TunnelContainModuleData *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x0c);
	}

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x08);
	}
};

// ?update@TunnelContain@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime TunnelContain::update()
{
	j_0000c1e9();

	const TunnelContainModuleData *data = getModuleData();
	Object *object = getObject();
	if (object != 0)
	{
		Player *controllingPlayer = 0;
		controllingPlayer = object->getControllingPlayer();
		if (controllingPlayer != 0)
		{
			TunnelTracker *tunnelSystem = controllingPlayer->getTunnelSystem();
			TunnelTracker *volatile &tunnelSystemRef = tunnelSystem;
			if (tunnelSystem != 0)
			{
				tunnelSystemRef->healObjects(data->m_framesForFullHeal);
			}

			BodyModuleInterface *body = object->getBodyModule();
			if (body != 0)
			{
				const DamageInfo *info = body->getLastDamageInfo();
				if (info != 0)
				{
					if (body->getLastDamageTimestamp() + 5 > TheGameLogic->m_frame)
					{
						Object *attacker = TheGameLogic->findObjectByID(info->in.m_sourceID);
						if (attacker != 0)
						{
							if (object->getRelationship(attacker) == ENEMIES)
							tunnelSystemRef->updateNemesis(attacker);
						}
					}
				}
			}
		}
	}

	return UPDATE_SLEEP_NONE;
}
