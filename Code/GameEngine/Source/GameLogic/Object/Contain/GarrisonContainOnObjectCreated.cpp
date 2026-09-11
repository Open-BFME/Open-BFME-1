// ?onObjectCreated@GarrisonContain@@MAEXXZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The canonical GarrisonContain source and vtable identify this callback.
// Retail uses BFME's four-argument ThingFactory path and a 12-byte status
// mask temporary for each initial-roster object.

#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;

class AsciiString
{
private:
	void *m_data;
};
class ThingTemplate;
class Team;
class Object;

struct ObjectStatusMaskType
{
	_STL::bitset<86> m_bits;
};

class Player
{
public:
	unsigned char m_unreconstructed00[0x230];
	Team *m_defaultTeam;
};

class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n() = 0
	CONTAIN_SLOT(00); CONTAIN_SLOT(01); CONTAIN_SLOT(02); CONTAIN_SLOT(03);
	CONTAIN_SLOT(04); CONTAIN_SLOT(05); CONTAIN_SLOT(06); CONTAIN_SLOT(07);
	CONTAIN_SLOT(08); CONTAIN_SLOT(09); CONTAIN_SLOT(10); CONTAIN_SLOT(11);
	CONTAIN_SLOT(12); CONTAIN_SLOT(13); CONTAIN_SLOT(14); CONTAIN_SLOT(15);
	CONTAIN_SLOT(16); CONTAIN_SLOT(17); CONTAIN_SLOT(18); CONTAIN_SLOT(19);
	CONTAIN_SLOT(20); CONTAIN_SLOT(21); CONTAIN_SLOT(22); CONTAIN_SLOT(23);
	CONTAIN_SLOT(24); CONTAIN_SLOT(25); CONTAIN_SLOT(26); CONTAIN_SLOT(27);
	CONTAIN_SLOT(28); CONTAIN_SLOT(29); CONTAIN_SLOT(30); CONTAIN_SLOT(31);
	CONTAIN_SLOT(32);
#undef CONTAIN_SLOT
	virtual Bool isValidContainerFor(Object *object, Bool checkCapacity) = 0;
	virtual void addToContain(Object *object) = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_unreconstructed00[0x1fc];
	ContainModuleInterface *m_contain;
};

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

#pragma comment(linker, "/alternatename:?findTemplate@BfmeThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")

extern void j_0004494a();

static __forceinline Object *bfmeNewObject(BfmeThingFactory *factory,
	const ThingTemplate *thingTemplate, Team *team,
	const ObjectStatusMaskType &status, UnsignedInt unknown)
{
	typedef Object *(BfmeThingFactory::*Function)(const ThingTemplate *, Team *,
		const ObjectStatusMaskType &, UnsignedInt);
	union { void (*raw)(); Function member; } function;
	function.raw = j_0004494a;
	return (factory->*function.member)(thingTemplate, team, status, unknown);
}

extern BfmeThingFactory *TheThingFactory;

struct GarrisonContainModuleData
{
	unsigned char m_unreconstructed00[0x174];
	AsciiString m_initialRosterTemplateName;
	int m_initialRosterCount;
};

class GarrisonContain
{
protected:
	virtual void onObjectCreated();

private:
	GarrisonContainModuleData *m_moduleData;
	Object *m_object;
};

void GarrisonContain::onObjectCreated()
{
	GarrisonContainModuleData *moduleData = m_moduleData;
	int count = moduleData->m_initialRosterCount;
	if (count <= 0)
		return;

	const ThingTemplate *rosterTemplate =
		TheThingFactory->findTemplate(moduleData->m_initialRosterTemplateName);
	Object *object = m_object;
	for (int i = 0; i < count; ++i)
	{
		ObjectStatusMaskType status;
		Team *team = object->getControllingPlayer()->m_defaultTeam;
		Object *payload = bfmeNewObject(TheThingFactory, rosterTemplate,
			team, status, 0);
		ContainModuleInterface *contain = object->m_contain;
		if (contain && contain->isValidContainerFor(payload, true))
			object->m_contain->addToContain(payload);
	}
}
