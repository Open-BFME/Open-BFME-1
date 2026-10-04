typedef bool Bool;
enum NameKeyType
{
	NameKeyTypeDummy = 0
};

class Player;

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Energy
{
public:
	void adjustPower(int amount, bool add);
};

class Player
{
public:
	void removeRadar(bool disableProof);

	unsigned char m_pad[0xa4];
	Energy m_energy;
};

class Rva000CBFA0Player : public Player
{
public:
	void addRadar(bool disableProof);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class ThingTemplate
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	unsigned char m_pad[0x410];
	int m_energyProduction;
};

class Thing
{
public:
	void *m_vtable;
	Overridable *m_template;
};

class UpgradeInterface
{
public:
	virtual bool isAlreadyUpgraded() const;
};

class RadarFields
{
public:
	unsigned char m_pad[0x70];
	bool m_disableProof;
};

class Module
{
public:
	void *m_vtable;
	RadarFields *m_owner;
	unsigned char m_pad[8];
	UpgradeInterface m_upgradeInterface;
};

class Object
{
public:
	virtual void objectAnchor();

protected:
	void onDisabledEdge(bool becomingDisabled);

public:
	Module *findModule(NameKeyType key) const;

	Thing *m_thing;
	unsigned char m_pad[0x234];
	Team *m_team;
};

extern NameKeyGenerator *TheNameKeyGenerator;

// Retail routes these calls through incremental-link thunks at these addresses;
// call them directly so the object references the thunk names.
extern void j_0002369b();
extern void j_0003add7();
extern void j_0002ae23();
extern void j_0000321a();
extern void j_000179fe();
extern void j_000022bb();
extern void j_00041a56();

void Object::onDisabledEdge(bool becomingDisabled)
{
	Player *controller;
	Object *self = this;
	Module *mod = 0;
	typedef Player *(Team::*GetControllingPlayer)() const;
	union { void (*fn)(); GetControllingPlayer call; } getControllingPlayer = { j_0002369b };
	controller = self->m_team ? (self->m_team->*getControllingPlayer.call)() : 0;
	if (controller)
	{
		typedef NameKeyType (NameKeyGenerator::*NameToKey)(const char *);
		union { void (*fn)(); NameToKey call; } nameToKey = { j_0003add7 };
		static NameKeyType radar = (TheNameKeyGenerator->*nameToKey.call)("RadarUpgrade");
		typedef Module *(Object::*FindModule)(NameKeyType) const;
		union { void (*fn)(); FindModule call; } findModule = { j_0002ae23 };
		mod = (self->*findModule.call)(radar);
		if (mod)
		{
			if (mod->m_upgradeInterface.isAlreadyUpgraded())
			{
				if (becomingDisabled)
				{
					typedef void (Player::*RemoveRadar)(bool);
					union { void (*fn)(); RemoveRadar call; } removeRadar = { j_0000321a };
					(controller->*removeRadar.call)(mod->m_owner->m_disableProof);
				}
				else
				{
					typedef void (Rva000CBFA0Player::*AddRadar)(bool);
					union { void (*fn)(); AddRadar call; } addRadar = { j_000179fe };
					(((Rva000CBFA0Player *)controller)->*addRadar.call)(mod->m_owner->m_disableProof);
				}
			}
		}
	}

	ThingTemplate *finalTemplate = (ThingTemplate *)self->m_thing;
	if (finalTemplate)
	{
		Overridable *templateObject = ((Thing *)finalTemplate)->m_template;
		if (templateObject)
		{
			typedef const Overridable *(Overridable::*GetFinalOverride)() const;
			union { void (*fn)(); GetFinalOverride call; } getFinalOverride = { j_000022bb };
			finalTemplate = (ThingTemplate *)(templateObject->*getFinalOverride.call)();
		}
	}
	int power = finalTemplate->m_energyProduction;
	if (power > 0 && controller)
	{
		typedef void (Energy::*AdjustPower)(int, bool);
		union { void (*fn)(); AdjustPower call; } adjustPower = { j_00041a56 };
		(controller->m_energy.*adjustPower.call)(power, !becomingDisabled);
	}
}

