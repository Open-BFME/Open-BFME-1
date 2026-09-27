// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// BFME build dispatcher with address-derived owner and virtual ABI views.
// stlport
#include "ascii_string.h"
#include <bitset>
#include <list>
#include <map>
#include <hash_map>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#include "../../GameLogic/command_source_type.h"

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_DOZER = 14,
	KINDOF_PROJECTILE = 0x67
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class ProjectileUpdateInterface;

#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType kind) const; \
	void setOrientation(Real angle);
#define OBJECT_TU_MEMBERS \
	void setProducer(const Object *object); \
	void setPosition(const Coord3D *position); \
	ProjectileUpdateInterface *getProjectileUpdateInterface() const;
#include "GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS
#undef THING_TU_MEMBERS
#undef BFME_HAVE_COORD3D

class ThingTemplate
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Team;

class Player
{
	UnsignedByte m_pad[0x230];
	Team *m_defaultTeam;

public:
	Team *getDefaultTeam() { return m_defaultTeam; }
	void onStructureConstructionComplete(Object *builder, Object *structure,
		Bool isRebuild);
};

class Rva00101820;

class BuildAssistant
{
	friend class Rva00101820;

	protected:
	void clearRemovableForConstruction(const ThingTemplate *what,
		const Coord3D *position, Real angle);
	Bool moveObjectsForConstruction(const ThingTemplate *what,
		const Coord3D *position, Real angle, Player *player);
};

template <int N>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags()
	{
	}

	void set(Int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<N> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *thing, Team *team,
		const ObjectStatusMaskType &status, UnsignedInt extra);
};

class Rva0020AA00Registry;
extern Rva0020AA00Registry *Rva0020AA00TheRegistry;

class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
};

class AI
{
	UnsignedByte m_pad[0x0c];
	Pathfinder *m_pathfinder;

public:
	Pathfinder *pathfinder() const { return m_pathfinder; }
};

extern AI *TheAI;

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

class Rva00367E30Logic
{
public:
	void applyObjectColorIndex383930(Object *object, Int color)
	{
		void j_0003a279();
		union Call
		{
			void (*code)();
			void (Rva00367E30Logic::*method)(Object *, Int);
		} call;
		call.code = j_0003a279;
		(this->*call.method)(object, color);
	}
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class Rva00101820AIUpdateInterface
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual void slot096();
	virtual void slot097();
	virtual void slot098();
	virtual void slot099();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *position,
		Real angle, Player *player, Int firstFlag, Int secondFlag);
};

class Rva00101820ProjectileUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *position,
		Real angle, Player *player, Int firstFlag, Int secondFlag);
};

class Rva000C9530
{
	UnsignedByte m_pad[0x220];

public:
	void wrap(Int first, Int second);
};

extern void j_0003aa8f();

typedef void (Player::*Rva000D4770Call)(Object *builder, Object *object);

union Rva000D4770CallBits
{
	void (*raw)();
	Rva000D4770Call member;
};

class Drawable;
typedef _STL::list<Drawable *> DrawableList;

class GameMessage
{
public:
	enum Type { TYPE_UNKNOWN = 0x7DA };
};

class PickAndPlayInfo;
extern Bool pickAndPlayUnitVoiceResponse(const DrawableList *list,
	GameMessage::Type type, PickAndPlayInfo *info);

#ifndef FALSE
#define FALSE 0
#endif

class CreateModuleInterface
{
public:
	virtual void onCreate();
	virtual void onBuildComplete();
};

class BehaviorModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual CreateModuleInterface *getCreate();
};

class Rva00101820BehaviorModule
{
	void *m_primaryVtable;
	UnsignedInt m_objectModuleData[2];

public:
	BehaviorModuleInterface m_interfaces;
};

class Rva00101820ObjectVtable
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable() const;
};

class Rva00101820
{
public:
	virtual Object *buildObjectNow(Object *constructorObject,
		const ThingTemplate *what, const Coord3D *position, Real angle,
		Player *owningPlayer);
};

// ?buildObjectNow@Rva00101820@@UAEPAVObject@@PAV2@PBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@@Z
Object *Rva00101820::buildObjectNow(Object *constructorObject,
	const ThingTemplate *what, const Coord3D *position, Real angle,
	Player *owningPlayer)
{
	if (what == 0 || position == 0)
		return 0;
	if (owningPlayer == 0)
		return 0;

	BuildAssistant *assistant = reinterpret_cast<BuildAssistant *>(this);
	assistant->clearRemovableForConstruction(what, position, angle);
	assistant->moveObjectsForConstruction(what, position, angle, owningPlayer);

	if (constructorObject->isKindOf(KINDOF_DOZER))
	{
		AIUpdateInterface *ai = constructorObject->m_ai;
		if (ai == 0)
			return 0;

		reinterpret_cast<AICommandInterface *>(
			reinterpret_cast<UnsignedByte *>(ai) + 0x20)->aiIdle(CMD_FROM_AI);
		return reinterpret_cast<Rva00101820AIUpdateInterface *>(ai)->construct(
			what, position, angle, owningPlayer, 0, 0);
	}

	if (constructorObject->isKindOf(KINDOF_PROJECTILE))
	{
		ProjectileUpdateInterface *projectile =
			constructorObject->getProjectileUpdateInterface();
		return reinterpret_cast<Rva00101820ProjectileUpdateInterface *>(
			projectile)->construct(what, position, angle, owningPlayer, 0, 0);
	}

	ObjectStatusMaskType startingStatus;
	if (what->isKindOf(KINDOF_STRUCTURE))
		startingStatus.set(2);

	Object *object = reinterpret_cast<ThingFactory *>(
		Rva0020AA00TheRegistry)->newObject(what,
		owningPlayer->getDefaultTeam(), startingStatus, 0);
	object->setProducer(constructorObject);

	TheBfmeGameLogic->applyObjectColorIndex383930(object,
		*reinterpret_cast<Int *>(reinterpret_cast<UnsignedByte *>(constructorObject) + 0x370));

	Coord3D groundPosition;
	groundPosition.x = position->x;
	groundPosition.y = position->y;
	groundPosition.z = TheTerrainLogic->getGroundHeight(
		groundPosition.x, groundPosition.y, 0);
	object->setPosition(&groundPosition);
	object->setOrientation(angle);
	TheAI->pathfinder()->addObjectToPathfindMap(object);

	if (object->isKindOf(KINDOF_STRUCTURE))
	{
		Rva000D4770CallBits call;
		call.raw = j_0003aa8f;
		(owningPlayer->*call.member)(constructorObject, object);
		owningPlayer->onStructureConstructionComplete(constructorObject,
			object, FALSE);
	}
	else
	{
		reinterpret_cast<Rva000C9530 *>(owningPlayer)->wrap(
			reinterpret_cast<Int>(constructorObject), reinterpret_cast<Int>(object));
		DrawableList drawables;
		Drawable *drawable = reinterpret_cast<Rva00101820ObjectVtable *>(object)->getDrawable();
		drawables.push_back(drawable);
		pickAndPlayUnitVoiceResponse(&drawables, GameMessage::TYPE_UNKNOWN, 0);
	}

	for (Rva00101820BehaviorModule **module =
		 reinterpret_cast<Rva00101820BehaviorModule **>(object->m_behaviors);
		 *module != 0; ++module)
	{
		CreateModuleInterface *create = (*module)->m_interfaces.getCreate();
		if (create == 0)
			continue;
		create->onBuildComplete();
	}

	return object;
}
