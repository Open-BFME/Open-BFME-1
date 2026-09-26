// cl: /DNDEBUG /MD /GX- /O2 /Ob2
//
// Retail 0x002D7BD0, 67 bytes: Zero Hour's RadarUpgrade::upgradeImplementation.
// It overrides the UpgradeMux base at +0x10, so `this` arrives adjusted and the
// module data (+4) and object (+8) are read at -0xC and -8.  addRadar is the
// Player body the ledger keeps as Rva000CBFA0Player::addRadar, and BFME's module
// lookup is the protected Object::findModule.

typedef bool Bool;
enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(s) TheNameKeyGenerator->nameToKey(s)

class Player;

class Rva000CBFA0Player
{
public:
	void addRadar(Bool disableProof);
};

class Module;

class Object
{
	friend class RadarUpgrade;

public:
	Player *getControllingPlayer() const;

protected:
	Module *findModule(NameKeyType key) const;
};

class RadarUpdate
{
public:
	void extendRadar();
};

struct RadarUpgradeModuleData
{
	char m_unmodelled00[0x70];
	Bool m_isDisableProof;
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	const RadarUpgradeModuleData *m_moduleData;
	Object *m_object;
	int m_unmodelled0C;
};

class UpgradeMux
{
protected:
	virtual void upgradeImplementation() = 0;
};

class RadarUpgrade : public ObjectModule, public UpgradeMux
{
protected:
	virtual void upgradeImplementation();
};

void RadarUpgrade::upgradeImplementation()
{
	const RadarUpgradeModuleData *md = m_moduleData;

	Player *player = m_object->getControllingPlayer();

	((Rva000CBFA0Player *)player)->addRadar(md->m_isDisableProof);

	NameKeyType radarUpdateKey = NAMEKEY("RadarUpdate");
	RadarUpdate *radarUpdate = (RadarUpdate *)m_object->findModule(radarUpdateKey);
	if (radarUpdate)
		radarUpdate->extendRadar();
}
