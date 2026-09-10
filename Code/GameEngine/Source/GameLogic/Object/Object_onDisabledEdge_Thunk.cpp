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

void Object::onDisabledEdge(bool becomingDisabled)
{
	Player *controller;
	Object *self = this;
	Module *mod = 0;
	controller = self->m_team ? self->m_team->getControllingPlayer() : 0;
	if (controller)
	{
		static NameKeyType radar = TheNameKeyGenerator->nameToKey((const char *)0x0108ff50);
		mod = self->findModule(radar);
		if (mod)
		{
			if (mod->m_upgradeInterface.isAlreadyUpgraded())
			{
				if (becomingDisabled)
					controller->removeRadar(mod->m_owner->m_disableProof);
				else
					((Rva000CBFA0Player *)controller)->addRadar(mod->m_owner->m_disableProof);
			}
		}
	}

	ThingTemplate *finalTemplate = (ThingTemplate *)self->m_thing;
	if (finalTemplate)
	{
		Overridable *templateObject = ((Thing *)finalTemplate)->m_template;
		if (templateObject)
			finalTemplate = (ThingTemplate *)templateObject->getFinalOverride();
	}
	int power = finalTemplate->m_energyProduction;
	if (power > 0 && controller)
		controller->m_energy.adjustPower(power, !becomingDisabled);
}

#pragma comment(linker, "/alternatename:?getControllingPlayer@Team@@QBEPAVPlayer@@XZ=?j_0002369b@@YAXXZ")
#pragma comment(linker, "/alternatename:?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z=?j_0003add7@@YAXXZ")
#pragma comment(linker, "/alternatename:?findModule@Object@@IBEPAVModule@@W4NameKeyType@@@Z=?j_0002ae23@@YAXXZ")
#pragma comment(linker, "/alternatename:?removeRadar@Player@@QAEX_N@Z=?j_0000321a@@YAXXZ")
#pragma comment(linker, "/alternatename:?addRadar@Player@@QAEX_N@Z=?j_000179fe@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?adjustPower@Energy@@QAEXH_N@Z=?j_00041a56@@YAXXZ")
