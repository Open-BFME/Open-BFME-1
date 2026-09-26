// ?doNugget@DamageFieldNugget@@UBEXPBVDamageInfo@@PBUCoord3D@@@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// stlport
// DamageFieldNugget::doNugget, retail 0x002DAEC0.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <bitset>

typedef unsigned int UnsignedInt;
typedef int ObjectID;
typedef int NameKeyType;

class AsciiString
{
};

class GlobalData
{
private:
	char m_pad00[0x10];

public:
	AsciiString m_genericDamageFieldName;
};

class ThingTemplate
{
};

class WeaponTemplate
{
};

struct Coord3D
{
public:
	float x;
	float y;
	float z;
};

class DamageInfo
{
public:
};

struct DamageInfoLayout
{
	char m_pad00[8];
	ObjectID m_sourceID;
};

__forceinline ObjectID getDamageSourceID(const DamageInfo *damageInfo)
{
	return reinterpret_cast<const DamageInfoLayout *>(damageInfo)->m_sourceID;
}

class Team
{
};

class Player
{
public:
	char m_pad00[0x230];
	Team *m_defaultTeam;
};

class Module
{
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Module *findModule(NameKeyType key) const;
	void setProducer(const Object *object);
	void setPosition(const Coord3D *position);
};

typedef void (Object::*ObjectSetProducerCall)(const Object *object);

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *object);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
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

template<int NUMBITS>
class BitFlags
{
public:
	BitFlags() { }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheBfmeGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;
extern ThingFactory *TheThingFactory;
extern void j_0004494a();
extern void j_0000d990();

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

typedef Object *(__fastcall *ThingFactoryNewObjectCall)(
	ThingFactory *, ObjectStatusMaskType *, ThingTemplate *, Team *,
	const volatile ObjectStatusMaskType &, void *);

class DamageFieldNugget
{
public:
	virtual void doNugget(const DamageInfo *damageInfo,
		const Coord3D *position) const;

private:
	char m_pad00[0x54];
	const WeaponTemplate *m_weaponTemplate;
	UnsignedInt m_duration;
};

void DamageFieldNugget::doNugget(const DamageInfo *damageInfo,
	const Coord3D *position) const
{
	ThingTemplate *thingTemplate =
		TheThingFactory->findTemplate(
			TheWritableGlobalData->m_genericDamageFieldName);
	if (thingTemplate == 0 || m_weaponTemplate == 0)
		return;

	Object *source = TheBfmeGameLogic->findObjectByID(
		getDamageSourceID(damageInfo));
	if (source == 0)
		return;

	ObjectStatusMaskType statusMask;
	Player *player = source->getControllingPlayer();
	Object *field = ((ThingFactoryNewObjectCall)j_0004494a)(
		TheThingFactory, &statusMask, thingTemplate,
		player->m_defaultTeam, statusMask, 0);
	union
	{
		void (*raw)(void);
		ObjectSetProducerCall member;
	} setProducerCall;
	setProducerCall.raw = j_0000d990;
	(field->*setProducerCall.member)(source);
	field->setPosition(position);

	static volatile NameKeyType key_FireWeaponUpdate = NAMEKEY("FireWeaponUpdate");
	int objectID = (int)source;
	objectID |= -1;
	Module *fireWeaponUpdate = field->findModule(key_FireWeaponUpdate);
	if (fireWeaponUpdate == 0)
	{
		TheBfmeGameLogic->destroyObject(field);
		return;
	}

	static volatile NameKeyType key_DeletionUpdate = NAMEKEY("DeletionUpdate");
	Module *deletionUpdate = field->findModule(key_DeletionUpdate);
	if (deletionUpdate == 0)
		return;

	((BfmeC1010 *)fireWeaponUpdate)->bfmeGo1010C(
		(void *)m_weaponTemplate);
	((DeletionUpdate *)deletionUpdate)->setLifetimeRange(
		m_duration, m_duration);
}
