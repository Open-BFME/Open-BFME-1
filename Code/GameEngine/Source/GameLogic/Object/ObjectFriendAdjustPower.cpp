// readable body of ?friend_adjustPowerForPlayer@Object@@QAEX_N@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp
class Object;
class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

struct ThingTemplatePowerABI
{
	void *vtable;
	Overridable *nextOverride;
	char pad[0x410];
	int energyProduction;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Energy.h
class Energy
{
public:
	// The friend helper reaches both methods through retail ILTs, so their
	// bodies must remain out of line even after being recovered in this TU.
	__declspec(noinline) void objectEnteringInfluence(Object *object);
	__declspec(noinline) void objectLeavingInfluence(Object *object);

private:
	void *m_vptrPad;
	int m_production;
	int m_consumption;
	Player *m_player;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
	public:
	void onPowerBrownOutChange(bool brownOut);
	char pad[0xA4];
	Energy energy;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
friend class Energy;
private:
	char pad0[4];
	ThingTemplatePowerABI *thingTemplate;
	char pad8[0x19C];
	void *disabledStates;
	char pad1A8[0x94];
	Team *team;

public:
	void friend_adjustPowerForPlayer(bool incoming);
};

void Object::friend_adjustPowerForPlayer(bool incoming)
{
	if (disabledStates != 0) {
		ThingTemplatePowerABI *powerTemplate = thingTemplate;
		if (powerTemplate != 0 && powerTemplate->nextOverride != 0) {
			powerTemplate = reinterpret_cast<ThingTemplatePowerABI *>(
				const_cast<Overridable *>(powerTemplate->nextOverride->getFinalOverride()));
		}
		if (powerTemplate->energyProduction > 0)
			return;
	}

	Player *player = team != 0 ? team->getControllingPlayer() : 0;
	if (player == 0)
		return;

	Energy *energy = &player->energy;
	if (energy == 0)
		return;

	if (incoming)
		energy->objectEnteringInfluence(this);
	else
		energy->objectLeavingInfluence(this);
}

void Energy::objectEnteringInfluence(Object *object)
{
	if (object == 0)
		return;

	ThingTemplatePowerABI *powerTemplate = object->thingTemplate;
	if (powerTemplate != 0 && powerTemplate->nextOverride != 0)
	{
		powerTemplate = reinterpret_cast<ThingTemplatePowerABI *>(
			const_cast<Overridable *>(powerTemplate->nextOverride->getFinalOverride()));
	}

	int power = powerTemplate->energyProduction;
	if (power < 0)
	{
		m_consumption -= power;
		if (m_player != 0)
			m_player->onPowerBrownOutChange(m_production < m_consumption);
	}
	else if (power > 0)
	{
		m_production += power;
		if (m_player != 0)
			m_player->onPowerBrownOutChange(m_production < m_consumption);
	}
}

void Energy::objectLeavingInfluence(Object *object)
{
	if (object == 0)
		return;

	ThingTemplatePowerABI *powerTemplate = object->thingTemplate;
	if (powerTemplate != 0 && powerTemplate->nextOverride != 0)
	{
		powerTemplate = reinterpret_cast<ThingTemplatePowerABI *>(
			const_cast<Overridable *>(powerTemplate->nextOverride->getFinalOverride()));
	}

	int power = powerTemplate->energyProduction;
	if (power < 0)
	{
		m_consumption += power;
		if (m_player != 0)
			m_player->onPowerBrownOutChange(m_production < m_consumption);
	}
	else if (power > 0)
	{
		m_production -= power;
		if (m_player != 0)
			m_player->onPowerBrownOutChange(m_production < m_consumption);
	}
}
