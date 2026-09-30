// ?d_0020ce30@@YAXXZ
// partial score=0.2675 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// SpawnTownsmenBehavior::update, retail RVA 0x0020CE30: slot 0 of the +0x10 interface vtable 0x010A6D04
// installed by the SpawnTownsmenBehavior ctor 0x0020CC70 (primary vtable 0x00CA6DD4 names the class).
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <bitset>
#include <vector>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS \
	void setPosition(const Coord3D *position);
#include "GameLogic/Object/object.h"
#undef THING_TU_MEMBERS
#undef BFME_HAVE_COORD3D

enum UpdateSleepTime
{
	UPDATE_SLEEP_SPAWN_TOWNSMEN = 30
};

class Team;

template <int N>
class BitFlags
{
public:
	BitFlags()
	{
	}

private:
	_STL::bitset<N> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *thing, Team *team,
		const ObjectStatusMaskType &status, UnsignedInt extra);
};

extern ThingFactory *TheThingFactory;

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;
};

extern TerrainLogic *TheTerrainLogic;

struct Rva001DB130Node
{
	_STL::vector<void *> m_bfmeValuesAK;	// +0x00
	Int m_0C;
	Rva001DB130Node *m_10;
};

class Rva001DB130
{
public:
	Rva001DB130Node *find(int v);
};

class BfmeListAK
{
public:
	BfmeListAK();
	void bfmeAddAK(void *key, void *value);

	void *m_bfmeHeadAK;
	void *m_bfmeRootAK;
};

// Retail constructs the list through ILT 0x00048135 (body 0x001DB0F0 zeroes both words).
#pragma comment(linker, "/alternatename:??0BfmeListAK@@QAE@XZ=?j_00048135@@YAXXZ")

class SpawnTownsmenBehaviorModuleData
{
public:
	UnsignedInt m_pad[2];
	AsciiString m_townsmanTemplateName;		// +0x08
	Int m_townsmanCount;					// +0x0C
	Real m_offsetX;							// +0x10
	Real m_offsetY;							// +0x14
	UnsignedInt m_updateDelay;				// +0x18
};

class SpawnTownsmenObjectModule
{
public:
	virtual void moduleSlot00();

	const SpawnTownsmenBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;										// +0x08
};

class SpawnTownsmenBehaviorInterface
{
public:
	virtual void behaviorSlot00();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class SpawnTownsmenBehavior : public SpawnTownsmenObjectModule,
	public SpawnTownsmenBehaviorInterface,
	public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

// Object+0x364 holds the spawned-object list keyed by 1; Object does not model that word.
static inline BfmeListAK *&townsmenList(Object *object)
{
	return *reinterpret_cast<BfmeListAK **>(reinterpret_cast<char *>(object) + 0x364);
}

// ?update@SpawnTownsmenBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime SpawnTownsmenBehavior::update()
{
	const SpawnTownsmenBehaviorModuleData *data = m_moduleData;
	Object *object = m_object;
	BfmeListAK *list = townsmenList(object);
	Int living = 0;

	if (list == 0)
	{
		list = new BfmeListAK;
		townsmenList(object) = list;
	}
	else
	{
		Rva001DB130Node *node = reinterpret_cast<Rva001DB130 *>(list)->find(1);
		if (node != 0)
		{
			_STL::vector<void *>::iterator it = node->m_bfmeValuesAK.begin();
			while (it != node->m_bfmeValuesAK.end())
			{
				Object *townsman = TheGameLogic->findObjectByID((Int)*it);
				if (townsman == 0)
					++it;
				else if (townsman->m_privateStatus & 1)
					it = node->m_bfmeValuesAK.erase(it);
				else
				{
					++it;
					++living;
				}
			}
		}
	}

	if (data->m_townsmanCount - living > 0)
	{
		const ThingTemplate *tmpl = TheThingFactory->findTemplate(data->m_townsmanTemplateName);
		if (tmpl != 0)
		{
			ObjectStatusMaskType status;
			Object *townsman = TheThingFactory->newObject(tmpl, object->m_team, status, 0);
			Real z = TheTerrainLogic->getGroundHeight(object->m_cachedPos.x + data->m_offsetX,
				data->m_offsetY + object->m_cachedPos.y, 0) + object->m_cachedPos.z;
			Coord3D pos;
			pos.x = object->m_cachedPos.x + data->m_offsetX;
			pos.y = data->m_offsetY + object->m_cachedPos.y;
			pos.z = z;
			townsman->setPosition(&pos);
			list->bfmeAddAK((void *)1, (void *)townsman->m_id);
		}
	}

	if (m_moduleData != 0)
		return (UpdateSleepTime)m_moduleData->m_updateDelay;
	return UPDATE_SLEEP_SPAWN_TOWNSMEN;
}
