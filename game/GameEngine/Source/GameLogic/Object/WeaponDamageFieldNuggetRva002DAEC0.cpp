// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x002DAEC0 (392 B), slot 6 of vtable 0x010CE990, which the 0x64-byte
// nugget ctor ??0BfmeThingUBA@@QAE@XZ (0x002DB0B0) installs; the INI
// `DamageFieldNugget =` callback 0x001E5C90 allocates that object (see
// WeaponDamageFieldNuggetParse.cpp). Spawns GlobalData's generic damage field
// object for the damage source's team, hands its FireWeaponUpdate the nugget's
// weapon template (+0x58) and gives its DeletionUpdate the nugget's duration
// (+0x5C); a field missing either module is destroyed. The method name stays
// address-derived: nothing names the slot.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef unsigned int UnsignedInt;
typedef int ObjectID;
enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "ascii_string.h"

template<int NUMBITS>
class BitFlags
{
public:
	BitFlags() { }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class GlobalData
{
public:
	char m_pad00[0x10];
	AsciiString m_genericDamageFieldName;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class DamageInfo
{
public:
	char m_pad00[8];
	ObjectID m_sourceID;
};

class ThingTemplate;
class WeaponTemplate;
class Module;

class Team;

class Player
{
public:
	Team *getDefaultTeam() { return m_defaultTeam; }

private:
	char m_pad00[0x230];
	Team *m_defaultTeam;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void setProducer(const Object *obj);
	void setPosition(const Coord3D *pos);
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }

protected:
	Module *findModule(NameKeyType key) const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *obj);
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team,
		const ObjectStatusMaskType &statusBits = ObjectStatusMaskType(),
		UnsignedInt flags = 0);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class BfmeC1010
{
public:
	void bfmeGo1010C(void *weaponTemplate);
};

class DeletionUpdate
{
public:
	void setLifetimeRange(UnsignedInt minFrames, UnsignedInt maxFrames);
};

// Retail 0x012ED5C8 is ?TheWritableGlobalData@@3PAVGlobalData@@A (data_rows.csv,
// Common/GlobalData.cpp); TheGlobalData was only a pin.
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData
extern GameLogic *TheGameLogic;
extern ThingFactory *TheThingFactory;
extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

class BfmeThingUBA
{
public:
	virtual void rva002DAEC0(const DamageInfo *damageInfo, const Coord3D *pos) const;

private:
	char m_pad04[0x54];
	const WeaponTemplate *m_weaponTemplate;
	UnsignedInt m_duration;
	int m_field60;
};

void BfmeThingUBA::rva002DAEC0(const DamageInfo *damageInfo, const Coord3D *pos) const
{
	const AsciiString &name = TheGlobalData->m_genericDamageFieldName;
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(name);
	if (tmpl == 0 || m_weaponTemplate == 0)
		return;

	ObjectID sourceID = damageInfo->m_sourceID;
	Object *source = TheGameLogic->findObjectByID(sourceID);
	if (source == 0)
		return;

	Object *field = TheThingFactory->newObject(tmpl, source->getControllingPlayer()->getDefaultTeam());
	field->setProducer(source);
	field->setPosition(pos);

	static NameKeyType key_FireWeaponUpdate = NAMEKEY("FireWeaponUpdate");
	BfmeC1010 *fireWeaponUpdate = (BfmeC1010 *)field->findUpdateModule(key_FireWeaponUpdate);
	if (fireWeaponUpdate == 0)
	{
		TheGameLogic->destroyObject(field);
		return;
	}

	static NameKeyType key_DeletionUpdate = NAMEKEY("DeletionUpdate");
	DeletionUpdate *deletionUpdate = (DeletionUpdate *)field->findUpdateModule(key_DeletionUpdate);
	if (deletionUpdate == 0)
	{
		TheGameLogic->destroyObject(field);
		return;
	}

	fireWeaponUpdate->bfmeGo1010C((void *)m_weaponTemplate);
	deletionUpdate->setLifetimeRange(m_duration, m_duration);
}
