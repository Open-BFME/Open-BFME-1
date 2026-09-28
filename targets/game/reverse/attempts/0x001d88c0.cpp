// ?reallyCreate@GenericObjectCreationNugget@@QBE?AV?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PBUCoord3D@@PBVMatrix3D@@MPBVObject@@I@Z
// partial score=0.1721 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object
// stlport
// PARTIAL (not matched): GenericObjectCreationNugget::reallyCreate, retail 0x001D88C0 (2556 B).
// Identity: EA name chain GenericObjectCreationNugget::reallyCreate, __FILE__ ObjectCreationList.cpp,
// FieldParse offsets (m_putInContainer +0x10, m_debrisToGenerate +0x28, formation +0x84..+0x8c,
// fade +0x7c/+0x80/+0x118/+0x119, flags +0x104..+0x11c). BFME returns vector<Object*> (ret 0x18).
// Measured: ours 2431 B vs 2556, 1866 differing bytes, shape 0.840.
// Main residue: retail leaves many inline helpers out of line (vector copy ctor, erase, ~vector at
// the final return, StringBase::isEmpty on sourceObj name) but inlines isEmpty on m_putInContainer,
// and keeps an EH state for the default-argument allocator temporary without a normal-path
// ~allocator call. Looks like an exhausted per-function inline budget; see the re_attempts verdict.
#include <vector>
#include <list>
#include "ascii_string.h"

typedef bool Bool;
enum ObjectID { INVALID_ID = 0 };
#define BFME_HAVE_OBJECTID
#define BFME_HAVE_ASCIISTRING
struct Coord3D { float x, y, z; };
#define BFME_HAVE_COORD3D
class Matrix3D;
class Player;
class Team;
enum KindOfType { KINDOF_TREE = 61, KINDOF_SHRUB = 62, KINDOF_OPTIMIZED_PROP = 67, KINDOF_HORDE = 108 };
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };
#define THING_TU_MEMBERS Bool isKindOf(KindOfType t) const;
#define OBJECT_TU_MEMBERS \
	Player *getControllingPlayer() const; \
	void setProducer(const Object *obj); \
	int getLayer() const; \
	void setLayer(PathfindLayerEnum layer); \
	const Coord3D *getPosition() const { return &m_cachedPos; }
#include "object.h"


namespace _STL {
template<> _Vector_base<Object *, allocator<Object *> >::_Vector_base(const allocator<Object *> &a);
template<> _Vector_base<Object *, allocator<Object *> >::~_Vector_base();
template<> vector<Object *, allocator<Object *> >::vector(const vector<Object *, allocator<Object *> > &x);
template<> vector<Object *, allocator<Object *> >::iterator vector<Object *, allocator<Object *> >::erase(iterator first, iterator last);
template<> void vector<Object *, allocator<Object *> >::push_back(Object *const &x);
}

class Drawable
{
public:
	void applyPendingModelConditionFlags(Bool);
	void bfmeDelayB(int frames); // fade in
	void bfmeDelayA(int frames); // fade out
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0xc8];
	UnsignedInt m_kindof[6]; // +0xc8
	unsigned char m_pad0e0[0x3c0 - 0xe0];
	Real m_3c0; // +0x3c0
	unsigned char m_pad3c4[0x480 - 0x3c4];
	unsigned short m_maxSimultaneousOfType; // +0x480
	Bool isKindOf(KindOfType t) const { return (m_kindof[(t - 32) >> 5] & (1 << (t & 31))) != 0; }
};

class Rva000C7CD0Obj;
class Rva000C7CD0
{
public:
	unsigned char ok(Rva000C7CD0Obj *tmpl, int count);
};

class Player
{
public:
	unsigned char m_pad000[0x30];
	Rva000C7CD0 m_030; // +0x30
	unsigned char m_pad031[0x230 - 0x31];
	Team *m_defaultTeam; // +0x230
	Bool isPlayerActive() const;
	void countObjectsByThingTemplate(int numTmplates, const ThingTemplate *const *things, Bool ignoreDead, int *counts, Bool ignoreUnderConstruction) const;
	Team *getDefaultTeam() { return m_defaultTeam; }
};

class ObjectCreationFlags { public: UnsignedInt m_bits[3]; ObjectCreationFlags() { m_bits[0] = 0; m_bits[1] = 0; m_bits[2] = 0; } };
template <int N> class BitFlags { public: UnsignedInt m_bits[3]; BitFlags() { m_bits[0] = 0; m_bits[1] = 0; m_bits[2] = 0; } };

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const BitFlags<86> &flags, UnsignedInt reserved);
};

class TerrainLogic
{
public:
	void onTreeTemplate001AD080(const ThingTemplate *tmpl, const Coord3D *pos, const Matrix3D *mtx, Real scale);
	void onShrubTemplate001A7A90(const ThingTemplate *tmpl, const Coord3D *pos, const Matrix3D *mtx, Real scale);
	void onOptimizedPropTemplate001A34C0(const ThingTemplate *tmpl, const Coord3D *pos, const Matrix3D *mtx, Real scale);
};

class GameLODManager
{
public:
	unsigned char m_pad[0x16d8];
	UnsignedInt m_debrisCounter; // +0x16d8
	UnsignedInt m_debrisMask; // +0x16dc
	Bool isDebrisSkipped() { ++m_debrisCounter; return (m_debrisCounter & m_debrisMask) != m_debrisMask; }
};

class ScriptEngine
{
public:
#define BFME_SE_SLOT(n) virtual void slot##n();
	BFME_SE_SLOT(00) BFME_SE_SLOT(01) BFME_SE_SLOT(02) BFME_SE_SLOT(03) BFME_SE_SLOT(04)
	BFME_SE_SLOT(05) BFME_SE_SLOT(06) BFME_SE_SLOT(07) BFME_SE_SLOT(08) BFME_SE_SLOT(09)
	BFME_SE_SLOT(10) BFME_SE_SLOT(11) BFME_SE_SLOT(12) BFME_SE_SLOT(13) BFME_SE_SLOT(14)
	BFME_SE_SLOT(15) BFME_SE_SLOT(16) BFME_SE_SLOT(17) BFME_SE_SLOT(18) BFME_SE_SLOT(19)
	BFME_SE_SLOT(20) BFME_SE_SLOT(21) BFME_SE_SLOT(22) BFME_SE_SLOT(23) BFME_SE_SLOT(24)
	BFME_SE_SLOT(25) BFME_SE_SLOT(26) BFME_SE_SLOT(27) BFME_SE_SLOT(28) BFME_SE_SLOT(29)
	BFME_SE_SLOT(30)
#undef BFME_SE_SLOT
	virtual void transferObjectName(const AsciiString &name, Object *obj); // +0x7c
};

typedef _STL::list<Object *> ContainedItemsList;

class Rva001D88C0Horde
{
public:
#define BFME_H_SLOT(n) virtual void slot##n();
	BFME_H_SLOT(00) BFME_H_SLOT(01) BFME_H_SLOT(02) BFME_H_SLOT(03) BFME_H_SLOT(04)
	BFME_H_SLOT(05) BFME_H_SLOT(06) BFME_H_SLOT(07) BFME_H_SLOT(08) BFME_H_SLOT(09)
	BFME_H_SLOT(10) BFME_H_SLOT(11) BFME_H_SLOT(12) BFME_H_SLOT(13) BFME_H_SLOT(14)
	BFME_H_SLOT(15) BFME_H_SLOT(16) BFME_H_SLOT(17) BFME_H_SLOT(18) BFME_H_SLOT(19)
	BFME_H_SLOT(20) BFME_H_SLOT(21) BFME_H_SLOT(22) BFME_H_SLOT(23) BFME_H_SLOT(24)
	BFME_H_SLOT(25) BFME_H_SLOT(26) BFME_H_SLOT(27) BFME_H_SLOT(28) BFME_H_SLOT(29)
	BFME_H_SLOT(30) BFME_H_SLOT(31) BFME_H_SLOT(32) BFME_H_SLOT(33) BFME_H_SLOT(34)
	BFME_H_SLOT(35) BFME_H_SLOT(36) BFME_H_SLOT(37) BFME_H_SLOT(38) BFME_H_SLOT(39)
	BFME_H_SLOT(40) BFME_H_SLOT(41) BFME_H_SLOT(42) BFME_H_SLOT(43) BFME_H_SLOT(44)
	BFME_H_SLOT(45) BFME_H_SLOT(46) BFME_H_SLOT(47) BFME_H_SLOT(48) BFME_H_SLOT(49)
	BFME_H_SLOT(50) BFME_H_SLOT(51) BFME_H_SLOT(52) BFME_H_SLOT(53) BFME_H_SLOT(54)
	BFME_H_SLOT(55) BFME_H_SLOT(56) BFME_H_SLOT(57) BFME_H_SLOT(58)
#undef BFME_H_SLOT
	virtual const ContainedItemsList *getMembers(); // +0xec
};

class ContainModuleInterface
{
public:
#define BFME_C_SLOT(n) virtual void slot##n();
	BFME_C_SLOT(00) BFME_C_SLOT(01) BFME_C_SLOT(02) BFME_C_SLOT(03) BFME_C_SLOT(04)
	BFME_C_SLOT(05) BFME_C_SLOT(06) BFME_C_SLOT(07) BFME_C_SLOT(08) BFME_C_SLOT(09)
	BFME_C_SLOT(10) BFME_C_SLOT(11) BFME_C_SLOT(12) BFME_C_SLOT(13) BFME_C_SLOT(14)
	BFME_C_SLOT(15) BFME_C_SLOT(16) BFME_C_SLOT(17) BFME_C_SLOT(18) BFME_C_SLOT(19)
	BFME_C_SLOT(20) BFME_C_SLOT(21) BFME_C_SLOT(22) BFME_C_SLOT(23) BFME_C_SLOT(24)
#undef BFME_C_SLOT
	virtual Rva001D88C0Horde *getHorde(); // +0x64
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual Bool isValidContainerFor(const Object *obj, Bool checkCapacity); // +0x84
	virtual void addToContain(Object *obj); // +0x88
};

class CreateModuleInterface
{
public:
	virtual void slot00();
	virtual void onBuildComplete(); // +0x4
};

class BehaviorModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual CreateModuleInterface *getCreate(); // +0xc
};

class BehaviorModule
{
public:
	unsigned char m_pad[0xc];
	BehaviorModuleInterface m_interface; // +0xc
};

class ExperienceTracker
{
public:
	Bool gainExpForLevel(int levelsToGain, Bool canScaleForBonus, Bool dontGiveExperience);
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int ownerID);
	~AudioEventRTS();
	void setObjectID(ObjectID id);
	unsigned char m_storage[0x70];
};

class AudioManager
{
public:
#define BFME_A_SLOT(n) virtual void slot##n();
	BFME_A_SLOT(00) BFME_A_SLOT(01) BFME_A_SLOT(02) BFME_A_SLOT(03) BFME_A_SLOT(04)
	BFME_A_SLOT(05) BFME_A_SLOT(06) BFME_A_SLOT(07) BFME_A_SLOT(08) BFME_A_SLOT(09)
	BFME_A_SLOT(10) BFME_A_SLOT(11) BFME_A_SLOT(12) BFME_A_SLOT(13) BFME_A_SLOT(14)
	BFME_A_SLOT(15) BFME_A_SLOT(16)
#undef BFME_A_SLOT
	virtual void addAudioEvent(const AudioEventRTS *event); // +0x44
};

struct FindPositionOptions
{
	UnsignedInt flags;
	Real minRadius;
	Real maxRadius;
	Real minZ;
	Real maxZ;
	Real maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	Player *relationshipObject;
	FindPositionOptions()
	{
		flags = 0; minRadius = 0.0f; maxRadius = 0.0f; minZ = -99999.9f; maxZ = 1e10f; maxZDelta = 0.0f;
		ignoreObject = 0; sourceToPathToDest = 0; relationshipObject = 0;
	}
};

class SpawnBoneRow { public: SpawnBoneRow(); float x, y, z, w; };
struct MatrixRows001D88C0 { SpawnBoneRow row[3]; };

extern ThingFactory *TheThingFactory;
extern TerrainLogic *TheTerrainLogic;
extern GameLODManager *TheGameLODManager;
extern ScriptEngine *TheScriptEngine;
extern AudioManager *TheAudio;
extern const AsciiString Rva01336E50EmptyString;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, int line);
Bool findPositionAround(const Coord3D *center, const FindPositionOptions *options, Coord3D *result);

class ObjectCreationNugget
{
public:
	virtual ~ObjectCreationNugget();
};

class GenericObjectCreationNugget : public ObjectCreationNugget
{
public:
	_STL::vector<Object *> reallyCreate(const Coord3D *pos, const Matrix3D *mtx, Real orientation, const Object *sourceObj, UnsignedInt lifetimeFrames) const;
	void doStuffToObj(Object *obj, const AsciiString &name, const Coord3D *pos, const Matrix3D *mtx, Real orientation, const Object *sourceObj, UnsignedInt lifetimeFrames, int index) const;

	_STL::vector<AsciiString> m_names; // +0x4
	AsciiString m_putInContainer; // +0x10
	unsigned char m_animSets[0xc]; // +0x14
	void *m_fxFinal; // +0x20
	AsciiString m_particleSysName; // +0x24
	int m_debrisToGenerate; // +0x28
	unsigned char m_pad02c[0x7c - 0x2c];
	int m_fadeFrames; // +0x7c
	AsciiString m_fadeSoundName; // +0x80
	Real m_minDistanceAFormation; // +0x84
	Real m_minDistanceBFormation; // +0x88
	Real m_maxDistanceFormation; // +0x8c
	int m_objectCount; // +0x90
	unsigned char m_bounceSound[0x70]; // +0x94
	Bool m_requiresLivePlayer; // +0x104
	Bool m_ignoreCommandPointLimit; // +0x105
	Bool m_inheritAttributesFromSource; // +0x106
	Bool m_inheritScriptingName; // +0x107
	Bool m_useJustBuiltFlag; // +0x108
	Bool m_containInsideSourceObject; // +0x109
	Bool m_preserveLayer; // +0x10a
	Bool m_ignoreAllObjects; // +0x10b
	Bool m_ignoreAllyUnits; // +0x10c
	Bool m_ignoreEnemyUnits; // +0x10d
	unsigned char m_pad10e[2];
	int m_startingBusyTime; // +0x110
	Bool m_nameAreObjects; // +0x114
	Bool m_okToChangeModelColor; // +0x115
	Bool m_orientInForceDirection; // +0x116
	Bool m_spreadFormation; // +0x117
	Bool m_fadeIn; // +0x118
	Bool m_fadeOut; // +0x119
	Bool m_inheritsVeterancy; // +0x11a
	Bool m_skipIfSignificantlyAirborne; // +0x11b
	int m_veterancyLevel; // +0x11c
};

_STL::vector<Object *> GenericObjectCreationNugget::reallyCreate(const Coord3D *pos, const Matrix3D *mtx, Real orientation, const Object *sourceObj, UnsignedInt lifetimeFrames) const
{
	static const ThingTemplate *debrisTemplate = TheThingFactory->findTemplate("GenericDebris");

	_STL::vector<Object *> objects;
	objects.clear();

	if (m_names.size() <= 0)
		return objects;

	if (m_requiresLivePlayer && (!sourceObj || !sourceObj->getControllingPlayer()->isPlayerActive()))
		return objects;

	Object *debris = NULL;
	Team *debrisOwner = NULL;
	if (sourceObj)
		debrisOwner = sourceObj->getControllingPlayer()->getDefaultTeam();

	Object *container = NULL;
	if (!m_putInContainer.isEmpty())
	{
		const ThingTemplate *containerTmpl = TheThingFactory->findTemplate(m_putInContainer);
		if (containerTmpl)
		{
			if (!containerTmpl->isKindOf(KINDOF_OPTIMIZED_PROP) && !containerTmpl->isKindOf(KINDOF_TREE) && !containerTmpl->isKindOf(KINDOF_SHRUB))
			{
				container = TheThingFactory->newObject(containerTmpl, debrisOwner, BitFlags<86>(), 0);
				container->setProducer(sourceObj);
			}
			else
			{
				MatrixRows001D88C0 rows;
				const SpawnBoneRow *src = (const SpawnBoneRow *)mtx;
				rows.row[0].x = src[0].x; rows.row[0].y = src[0].y; rows.row[0].z = src[0].z;
				rows.row[1].x = src[1].x; rows.row[1].y = src[1].y; rows.row[1].z = src[1].z;
				rows.row[2].x = src[2].x; rows.row[2].y = src[2].y; rows.row[2].z = src[2].z;
				rows.row[2].w = 0.0f; rows.row[1].w = 0.0f; rows.row[0].w = 0.0f;
				Real scale = containerTmpl->m_3c0;
				if (containerTmpl->isKindOf(KINDOF_TREE))
					TheTerrainLogic->onTreeTemplate001AD080(containerTmpl, pos, (const Matrix3D *)&rows, scale);
				else if (containerTmpl->isKindOf(KINDOF_SHRUB))
					TheTerrainLogic->onShrubTemplate001A7A90(containerTmpl, pos, (const Matrix3D *)&rows, scale);
				else
					TheTerrainLogic->onOptimizedPropTemplate001A34C0(containerTmpl, pos, (const Matrix3D *)&rows, scale);
			}
		}
	}

	for (int nn = 0; nn < m_debrisToGenerate; nn++)
	{
		int pick = GetGameLogicRandomValue(0, m_names.size() - 1, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 1373);

		const ThingTemplate *tmpl;
		if (m_nameAreObjects)
		{
			Player *player = sourceObj->getControllingPlayer();
			tmpl = TheThingFactory->findTemplate(m_names[pick]);
			if (!tmpl)
				continue;
			if (!m_ignoreCommandPointLimit)
			{
				if (!player->m_030.ok((Rva000C7CD0Obj *)tmpl, 1))
					return objects;
			}
			if (tmpl->m_maxSimultaneousOfType != 0)
			{
				int count = 0;
				player->countObjectsByThingTemplate(1, &tmpl, true, &count, false);
				if ((UnsignedInt)count >= tmpl->m_maxSimultaneousOfType)
					return objects;
			}
		}
		else
		{
			if (TheGameLODManager->isDebrisSkipped())
				continue;
			tmpl = debrisTemplate;
		}
		if (!tmpl)
			continue;

		if (!tmpl->isKindOf(KINDOF_OPTIMIZED_PROP) && !tmpl->isKindOf(KINDOF_TREE) && !tmpl->isKindOf(KINDOF_SHRUB))
		{
			debris = TheThingFactory->newObject(tmpl, debrisOwner, BitFlags<86>(), 0);
			objects.push_back(debris);

			Drawable *draw = debris->getDrawable();
			if (m_inheritAttributesFromSource && draw)
				draw->applyPendingModelConditionFlags(true);

			if (m_nameAreObjects && m_inheritScriptingName && sourceObj && !sourceObj->m_name.isEmpty() && m_debrisToGenerate == 1)
				TheScriptEngine->transferObjectName(sourceObj->m_name, debris);

			if (m_preserveLayer && sourceObj && container == NULL)
			{
				int layer = sourceObj->getLayer();
				if (layer != LAYER_GROUND)
					debris->setLayer((PathfindLayerEnum)layer);
			}

			if (container != NULL && container->m_contain != NULL && container->m_contain->isValidContainerFor(debris, true))
				container->m_contain->addToContain(debris);

			if (m_spreadFormation)
			{
				Coord3D resultPos;
				FindPositionOptions fpOptions;
				fpOptions.minRadius = GetGameLogicRandomValueReal(m_minDistanceAFormation, m_minDistanceBFormation, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp", 1482);
				fpOptions.maxRadius = m_maxDistanceFormation;
				UnsignedInt flags = 0x80;
				if (m_ignoreAllObjects)
					flags = 0x84;
				if (m_ignoreEnemyUnits)
					flags |= 0x20;
				if (m_ignoreAllyUnits)
					flags |= 0x8;
				fpOptions.flags = flags;
				if (!findPositionAround(pos, &fpOptions, &resultPos))
					resultPos = *sourceObj->getPosition();
				doStuffToObj(debris, m_names[pick], &resultPos, mtx, orientation, sourceObj, lifetimeFrames, nn);
			}
			else
			{
				doStuffToObj(debris, m_names[pick], pos, mtx, orientation, sourceObj, lifetimeFrames, nn);
			}

			for (BehaviorModule **m = debris->m_behaviors; *m; ++m)
			{
				CreateModuleInterface *create = (*m)->m_interface.getCreate();
				if (create)
					create->onBuildComplete();
			}

			if (m_veterancyLevel > 0)
				debris->m_experienceTracker->gainExpForLevel(m_veterancyLevel, true, false);

			debris->setProducer(sourceObj);

			if (m_fadeIn)
			{
				AudioEventRTS fadeAudioEvent(m_fadeSoundName, 0);
				fadeAudioEvent.setObjectID(sourceObj->m_id);
				TheAudio->addAudioEvent(&fadeAudioEvent);
				if (debris->isKindOf(KINDOF_HORDE))
				{
					ContainModuleInterface *contain = debris->m_contain;
					Rva001D88C0Horde *horde;
					if (contain && (horde = contain->getHorde()) != NULL)
					{
						ContainedItemsList members(*horde->getMembers());
						for (ContainedItemsList::iterator it = members.begin(); it != members.end(); ++it)
						{
							if (*it)
								(*it)->getDrawable()->bfmeDelayB(m_fadeFrames);
						}
					}
				}
				else
				{
					debris->getDrawable()->bfmeDelayB(m_fadeFrames);
				}
			}

			if (m_fadeOut)
			{
				AudioEventRTS fadeAudioEvent(m_fadeSoundName, 0);
				fadeAudioEvent.setObjectID(sourceObj->m_id);
				TheAudio->addAudioEvent(&fadeAudioEvent);
				debris->getDrawable()->bfmeDelayA(m_fadeFrames);
			}
		}
		else
		{
			MatrixRows001D88C0 rows;
			const SpawnBoneRow *src = (const SpawnBoneRow *)mtx;
			rows.row[0].x = src[0].x; rows.row[0].y = src[0].y; rows.row[0].z = src[0].z;
			rows.row[1].x = src[1].x; rows.row[1].y = src[1].y; rows.row[1].z = src[1].z;
			rows.row[2].x = src[2].x; rows.row[2].y = src[2].y; rows.row[2].z = src[2].z;
			rows.row[2].w = 0.0f; rows.row[1].w = 0.0f; rows.row[0].w = 0.0f;
			Real scale = tmpl->m_3c0;
			if (tmpl->isKindOf(KINDOF_TREE))
				TheTerrainLogic->onTreeTemplate001AD080(tmpl, pos, (const Matrix3D *)&rows, scale);
			else if (tmpl->isKindOf(KINDOF_SHRUB))
				TheTerrainLogic->onShrubTemplate001A7A90(tmpl, pos, (const Matrix3D *)&rows, scale);
			else
				TheTerrainLogic->onOptimizedPropTemplate001A34C0(tmpl, pos, (const Matrix3D *)&rows, scale);
		}
	}

	if (container)
	{
		doStuffToObj(container, Rva01336E50EmptyString, pos, mtx, orientation, sourceObj, lifetimeFrames, 0);
		container->setProducer(sourceObj);
	}

	return objects;
}
