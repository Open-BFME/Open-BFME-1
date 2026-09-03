// cl: /DNDEBUG /MD /EHsc /G6 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

struct UpgradeMaskType
{
	UnsignedInt m_bits[6];

	UpgradeMaskType()
	{
	}

	__forceinline UpgradeMaskType(const UpgradeMaskType &other)
	{
		for (UnsignedInt i = 0; i < 6; ++i)
			m_bits[i] = other.m_bits[i];
	}

	__forceinline void set(const UpgradeMaskType &other)
	{
		m_bits[0] |= other.m_bits[0];
		m_bits[1] |= other.m_bits[1];
		m_bits[2] |= other.m_bits[2];
		m_bits[3] |= other.m_bits[3];
		m_bits[4] |= other.m_bits[4];
		m_bits[5] |= other.m_bits[5];
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	const UpgradeMaskType *getCompletedUpgradeMask() const
	{
		return &m_upgradesCompleted;
	}

private:
	unsigned char m_unmodelled_000[0x8c];
	UpgradeMaskType m_upgradesCompleted;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

class Object;
class Module;

Module *rva0036BB10FindCastleMemberBehavior(const Object *object);

class CastleMemberBehavior
{
public:
	ObjectID getCastleID() const { return m_castleID; }

private:
	unsigned char m_unmodelled_000[0x14];
	ObjectID m_castleID;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
class UpgradeModuleInterface
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual Bool attemptUpgrade(const UpgradeMaskType &keyMask) = 0;
	virtual void bfmeSlot2() = 0;
	virtual void bfmeSlot3() = 0;
	virtual void bfmeSlot4() = 0;
	virtual void bfmeSlot5() = 0;
	virtual void bfmePostUpgradeCheck() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void bfmeSlot0() = 0;
	virtual void bfmeSlot1() = 0;
	virtual void bfmeSlot2() = 0;
	virtual void bfmeSlot3() = 0;
	virtual void bfmeSlot4() = 0;
	virtual void bfmeSlot5() = 0;
	virtual void bfmeSlot6() = 0;
	virtual void bfmeSlot7() = 0;
	virtual void bfmeSlot8() = 0;
	virtual UpgradeModuleInterface *getUpgrade() = 0;
};

class _BFMEObjectModule
{
public:
	virtual void bfmeObjectModuleSlot0() = 0;

private:
	UnsignedInt m_unmodelled[2];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public _BFMEObjectModule, public BehaviorModuleInterface
{
};

struct BfmeBehaviorVTable
{
	void *m_slots[9];
	UpgradeModuleInterface *(__fastcall *m_getUpgrade)(BehaviorModuleInterface *);
};

struct BfmeUpgradeVTable
{
	Bool (__fastcall *m_isAlreadyUpgraded)(
		UpgradeModuleInterface *, BfmeUpgradeVTable *);
};

class ObjectUpdateUpgradeModulesShim
{
public:
	void update();

private:
	unsigned char m_unmodelled_000[0x1f0];
	BehaviorModule **m_behaviors;
	unsigned char m_unmodelled_1f4[0x30];
	UpgradeMaskType m_objectUpgradesCompleted;
	Team *m_team;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const UpgradeMaskType &getObjectCompletedUpgradeMask() const
	{
		return m_objectUpgradesCompleted;
	}

private:
	unsigned char m_unmodelled_000[0x224];
	UpgradeMaskType m_objectUpgradesCompleted;
};

void ObjectUpdateUpgradeModulesShim::update()
{
	if (m_team == 0)
		return;

	Player *player = m_team->getControllingPlayer();
	if (player == 0)
		return;

	player = reinterpret_cast<Player *>(
		reinterpret_cast<unsigned char *>(player) + 0x8c);
	UpgradeMaskType maskToCheck(
		*reinterpret_cast<const UpgradeMaskType *>(player));
	maskToCheck.set(m_objectUpgradesCompleted);

	CastleMemberBehavior *castleMember = reinterpret_cast<CastleMemberBehavior *>(
		rva0036BB10FindCastleMemberBehavior(reinterpret_cast<const Object *>(this)));
	if (castleMember != 0)
	{
		Object *castle = TheGameLogic->findObjectByID(castleMember->getCastleID());
		if (castle != 0)
		{
			maskToCheck.set(castle->getObjectCompletedUpgradeMask());
		}
	}

	for (BehaviorModule **module = m_behaviors; *module != 0; ++module)
	{
		BehaviorModuleInterface *behavior = reinterpret_cast<BehaviorModuleInterface *>(
			reinterpret_cast<unsigned char *>(*module) + 0x0c);
		BfmeBehaviorVTable *vtable =
			*reinterpret_cast<BfmeBehaviorVTable **>(behavior);
		UpgradeModuleInterface *upgrade;
		upgrade = vtable->m_getUpgrade(behavior);
		if (upgrade != 0)
		{
			BfmeUpgradeVTable *upgradeVtable =
				*reinterpret_cast<BfmeUpgradeVTable **>(upgrade);
			if (upgradeVtable->m_isAlreadyUpgraded(
				upgrade, upgradeVtable) == false)
				upgrade->attemptUpgrade(maskToCheck);
			upgrade->bfmePostUpgradeCheck();
		}
	}
}
