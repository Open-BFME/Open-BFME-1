// ?rva0038F7B0@GameLogic@@QAEXPAUObjectMapVector@@PBW4KindOfType@@1_N@Z
// partial score=0.2184 date=2026-11-04
// ?rva0038F7B0@GameLogic@@QAEXPAUObjectMapVector@@PBW4KindOfType@@1_N@Z  (EA: GameLogic::loadAllObjects)
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <math.h>
#include <string.h>
#include <set>
#include "ascii_string.h"

typedef bool Bool;
#define TRUE true
#define FALSE false
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long ms);

struct Coord3D { Real x, y, z; };

class Vector4
{
public:
	__forceinline float &operator[](int i) { return (&X)[i]; }
	__forceinline const float &operator[](int i) const { return (&X)[i]; }
	float X, Y, Z, W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline explicit Matrix3D(bool init)
	{
		Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
		Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
		Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
	}
	__forceinline void Rotate_Z(float theta)
	{
		float tmp1, tmp2;
		float c, s;
		c = cosf(theta);
		s = sinf(theta);
		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[0][1] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)( c*tmp1 + s*tmp2);
		Row[1][1] = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
	}
	Vector4 Row[3];
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum KindOfType { KINDOF_INVALID = -1 };
enum PathfindLayerEnum { LAYER_INVALID = 0 };

class StaticNameKey { public: NameKeyType key() const; };
extern StaticNameKey TheKey_originalOwner;   // 0x012A7778
extern StaticNameKey TheKey_alignToTerrain;  // 0x012A7910
extern StaticNameKey TheKey_scale;           // 0x012A7800

class Dict
{
public:
	AsciiString getAsciiString(NameKeyType key, Bool *exists = 0) const;
	Real getReal(NameKeyType key, Bool *exists = 0) const;
	Bool getBool(NameKeyType key, Bool *exists = 0) const;
};

class ThingTemplate;
class Object;
class Team;

class MapObject
{
public:
	ThingTemplate *getThingTemplate();
	const Coord3D *getLocation();
	char m_pad00[4];
	MapObject *m_next;
	char m_pad08[0x14];
	Real m_angle;
	UnsignedInt m_flags;
	Dict m_properties;
};
extern MapObject **BfmeTheMapObjectListHolder;
void handleNameChange(MapObject *mapObj);

class AssetList;
struct AssetLoadMode;

class ThingTemplate
{
public:
	Bool isKindOf(KindOfType kind) const;
	void rva00144DC0(AssetList &assets, AssetLoadMode *mode);
	ThingTemplate *resolveFinalOverride();
	__forceinline UnsignedInt getWord(UnsignedInt pos) const { return m_kindOf[pos >> 5]; }
	static __forceinline UnsignedInt maskBit(UnsignedInt pos) { return (UnsignedInt)1 << (pos & 31); }
	__forceinline Bool testKind(UnsignedInt kind) const
	{
		return (getWord(kind) & maskBit(kind)) != 0;
	}
	char m_pad000[0xc8];
	UnsignedInt m_kindOf[4];
	char m_pad0d8[0x398 - 0xd8];
	Real m_f398;
	char m_pad39c[0x3c0 - 0x39c];
	Real m_scale;
	char m_pad3c4[0x485 - 0x3c4];
	Bool m_b485;
	char m_pad486[0x48b - 0x486];
	Bool m_b48b;
	Bool m_b48c;
};
extern const Real g_bfmeDefaultBR;

struct ObjectStatusBits { __forceinline ObjectStatusBits() { m_bits[0] = 0; m_bits[1] = 0; m_bits[2] = 0; } UnsignedInt m_bits[3]; };
struct AssetLoadMode { __forceinline AssetLoadMode() : m_mode(0) {} unsigned char m_mode; };

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const ObjectStatusBits &status, UnsignedInt flags);
};
extern ThingFactory *TheThingFactory;

class Drawable { public: char m_pad[0x110]; UnsignedInt m_status; };

class CreateModuleInterface { public: virtual void slot0(); virtual void onBuildComplete(); };
class BehaviorModuleInterface { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual CreateModuleInterface *getCreate(); };
class BehaviorModule { public: char m_pad[0xc]; BehaviorModuleInterface m_iface; };

class Object
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual Drawable *getDrawable();
	Bool isKindOf(KindOfType kind) const;
	void setOrientation(Real angle);
	void setPosition(const Coord3D *pos);
	void rva00132200(const Matrix3D *mtx);
	void updateObjValuesFromMapProperties(Dict *props);
	void setLayer(PathfindLayerEnum layer);
	char m_pad004[0x1f0 - 4];
	BehaviorModule **m_behaviors;
};

class Team { public: __forceinline void setActive() { if (!m_active) { m_wasActive = TRUE; m_active = TRUE; } } char m_pad[0x31]; Bool m_active; Bool m_wasActive; };
class PlayerHolder { public: char m_pad[0x230]; Team *m_neutral; };
class Players
{
public:
	Team *validateTeam(AsciiString name, MapObject *mapObj);
	char m_pad[0x14];
	PlayerHolder *m_holder;
};
extern Players *ThePlayers;

class TerrainLogic
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0);
	virtual Real getHeightAndNormal(Real x, Real y, Bool a, Coord3D *normal, Bool b);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
	void placeTree(const ThingTemplate *t, const Coord3D *pos, const Matrix3D *mtx, Real scale);
	void addShrub(const ThingTemplate *t, const Coord3D *pos, const Matrix3D *mtx, Real scale);
	void addProp(const ThingTemplate *t, const Coord3D *pos, const Matrix3D *mtx, Real scale);
};
extern TerrainLogic *TheTerrainLogic;

class Pathfinder { public: void addObjectToPathfindMap(Object *obj); };
struct AIData
{
	char m_pad[0xd4];
	Bool m_useTrees;
	char m_pad2[3];
	AsciiString m_treeA;
	AsciiString m_treeB;
	AsciiString m_treeC;
	Real m_treeScale;
	Bool m_noShrubs;
};
class AI { public: char m_pad[0xc]; Pathfinder *m_pathfinder; char m_pad2[4]; AIData *m_data; };
extern AI *TheAI;

class Recorder { public: Bool isMultiplayer(); };
extern Recorder *TheRecorder;
struct GameLogicState { char m_pad[0x10c]; Int m_mode; };
extern GameLogicState *TheBfmeGameLogic;
struct GameLODManager { char m_pad[0x16c4]; Int m_level; };
extern GameLODManager *TheGameLODManager;
class Subsystem { public: virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void update(); };
extern Subsystem *FirstUpdateSubsystem;
class Engine { public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void serviceWindowsOS(); };
extern Engine *TheGameEngine;
void Rva0090F050();
void Rva009EBAC0(Int assets);
Real normalizeAngle(Real angle);
void makeAlignToNormalMatrix(Real angle, const Coord3D &pos, const Coord3D &normal, Matrix3D &mtx);

struct Gen_t_00140950_k4 { int m_value; };
typedef _STL::_Rb_tree<Gen_t_00140950_k4, Gen_t_00140950_k4, _STL::_Identity<Gen_t_00140950_k4>,
	_STL::less<Gen_t_00140950_k4>, _STL::allocator<Gen_t_00140950_k4> > AssetTree;
template <> AssetTree::~_Rb_tree();

struct AssetTreeHeader { unsigned char m_color; void *m_parent; void *m_left; void *m_right; };

class AssetList
{
public:
	__forceinline AssetList()
	{
		m_header = 0;
		m_header = (AssetTreeHeader *)_STL::__node_alloc<true, 0>::allocate(0x14);
		m_count = 0;
		m_header->m_color = 0;
		m_header->m_parent = 0;
		m_header->m_left = m_header;
		m_header->m_right = m_header;
		m_pad = 0;
		m_changed = true;
	}
	__forceinline ~AssetList() { ((AssetTree *)this)->~AssetTree(); }
	void clear();
	AssetTreeHeader *m_header;
	UnsignedInt m_count;
	UnsignedInt m_compare;
	UnsignedInt m_pad;
	Bool m_changed;
};

struct ObjectMapPair { Object *first; MapObject *second; };
struct ObjectMapVector { void push_back(const ObjectMapPair &p); };

static __forceinline void serviceOS()
{
	Sleep(0);
	if (TheGameEngine)
		TheGameEngine->serviceWindowsOS();
}

class GameLogic
{
public:
	void rva0038F7B0(ObjectMapVector *created, const KindOfType *skipKind, const KindOfType *requireKind, Bool loadingSaveGame);
};

void GameLogic::rva0038F7B0(ObjectMapVector *created, const KindOfType *skipKind, const KindOfType *requireKind, Bool loadingSaveGame)
{
	Bool useTrees = TRUE;
	ThingTemplate *treeA = TheThingFactory->findTemplate(TheAI->m_data->m_treeA);
	ThingTemplate *treeB = TheThingFactory->findTemplate(TheAI->m_data->m_treeB);
	if (treeB == 0)
		treeA = 0;
	ThingTemplate *treeC = TheThingFactory->findTemplate(TheAI->m_data->m_treeC);
	if (treeC == 0)
		treeA = 0;
	Bool useOverrides = FALSE;
	Bool multiplayer = TheRecorder->isMultiplayer();
	if (TheBfmeGameLogic->m_mode == 6)
		multiplayer = FALSE;
	if (TheBfmeGameLogic->m_mode == 2)
		multiplayer = FALSE;
	if (!multiplayer)
	{
		if (TheAI->m_data->m_useTrees && TheGameLODManager->m_level <= 1 && treeA)
		{
			useOverrides = TRUE;
			treeA = treeA->resolveFinalOverride();
			treeB = treeB->resolveFinalOverride();
			treeC = treeC->resolveFinalOverride();
		}
		useTrees = !TheAI->m_data->m_noShrubs;
	}

	AssetList assets;
	Int count = 0;
	for (MapObject *mapObj = *BfmeTheMapObjectListHolder; mapObj; mapObj = mapObj->m_next)
	{
		FirstUpdateSubsystem->update();
		Rva0090F050();
		serviceOS();
		if (mapObj->m_flags & 0x36)
			continue;
		serviceOS();
		handleNameChange(mapObj);
		ThingTemplate *thingTemplate = mapObj->getThingTemplate();
		if (thingTemplate == 0)
			continue;
		if (thingTemplate->m_b485)
			continue;
		if (skipKind && thingTemplate->testKind(*skipKind))
			continue;
		if (requireKind && !thingTemplate->testKind(*requireKind))
			continue;
		if ((thingTemplate->m_kindOf[0] & 0x40) && !useTrees)
			continue;

		Coord3D pos = *mapObj->getLocation();
		pos.z += TheTerrainLogic->getGroundHeight(pos.x, pos.y);
		Real angle = normalizeAngle(mapObj->m_angle);
		Bool isProp = (thingTemplate->m_kindOf[3] >> 3) & 1;
		if ((thingTemplate->m_kindOf[1] & 0x40000) && thingTemplate->m_f398 == 0.0f)
			isProp = TRUE;
		if (isProp || (thingTemplate->m_kindOf[2] & 0x20000000) || thingTemplate->isKindOf((KindOfType)0x5e))
		{
			Dict *props = &mapObj->m_properties;
			Bool hasScale;
			Real scaleFactor = props->getReal(TheKey_scale.key(), &hasScale);
			Matrix3D mtx(true);
			Bool align;
			if (props->getBool(TheKey_alignToTerrain.key(), &align) && align)
			{
				Coord3D normal;
				TheTerrainLogic->getHeightAndNormal(pos.x, pos.y, TRUE, &normal, TRUE);
				Coord3D zero;
				zero.x = 0.0f;
				zero.y = 0.0f;
				zero.z = 0.0f;
				makeAlignToNormalMatrix(angle, zero, normal, mtx);
			}
			else
			{
				mtx.Rotate_Z(mapObj->m_angle);
			}
			Real scale = thingTemplate->m_scale;
			if (hasScale)
				scale *= scaleFactor;
			AssetLoadMode mode;
			thingTemplate->rva00144DC0(assets, &mode);
			if (++count == 20)
			{
				count = 0;
				Rva009EBAC0((Int)&assets);
				assets.clear();
			}
			if (loadingSaveGame)
				continue;
			if (thingTemplate->isKindOf((KindOfType)0x5d))
			{
				if (treeA && useOverrides)
				{
					if (thingTemplate->m_b48b && thingTemplate->m_b48c)
						thingTemplate = treeA;
					else if (!thingTemplate->m_b48b && thingTemplate->m_b48c)
						thingTemplate = treeB;
					else
						thingTemplate = treeC;
					scale = TheAI->m_data->m_treeScale;
				}
				if (useTrees)
					TheTerrainLogic->placeTree(thingTemplate, &pos, &mtx, scale);
			}
			else if (thingTemplate->isKindOf((KindOfType)0x5e))
				TheTerrainLogic->addShrub(thingTemplate, &pos, &mtx, scale);
			else
				TheTerrainLogic->addProp(thingTemplate, &pos, &mtx, scale);
		}
		else
		{
			Dict *props = &mapObj->m_properties;
			AsciiString originalOwner = props->getAsciiString(TheKey_originalOwner.key());
			Team *team = ThePlayers->validateTeam(originalOwner, mapObj);
			if (ThePlayers->m_holder->m_neutral == team && strncmp("Player_", originalOwner.str(), 7) == 0)
				continue;
			AssetLoadMode mode;
			thingTemplate->rva00144DC0(assets, &mode);
			if (++count == 20)
			{
				count = 0;
				Rva009EBAC0((Int)&assets);
				assets.clear();
			}
			if (loadingSaveGame)
				continue;
			ObjectStatusBits status;
			Object *obj = TheThingFactory->newObject(thingTemplate, team, status, 0);
			if (obj)
			{
				if ((mapObj->m_flags & 1) || obj->isKindOf((KindOfType)5))
				{
					Drawable *draw = obj->getDrawable();
					if (draw)
						draw->m_status |= 1;
				}
				Bool align;
				if (props->getBool(TheKey_alignToTerrain.key(), &align) && align)
				{
					Coord3D zero;
					zero.x = 0.0f;
					zero.y = 0.0f;
					zero.z = 0.0f;
					Coord3D normal;
					TheTerrainLogic->getHeightAndNormal(pos.x, pos.y, TRUE, &normal, TRUE);
					Matrix3D mtx;
					makeAlignToNormalMatrix(angle, zero, normal, mtx);
					obj->rva00132200(&mtx);
				}
				else
				{
					obj->setOrientation(angle);
				}
				obj->setPosition(&pos);
				obj->updateObjValuesFromMapProperties(props);
				obj->setLayer(TheTerrainLogic->getLayerForDestination(obj, &pos));
				serviceOS();
				FirstUpdateSubsystem->update();
				Rva0090F050();
				for (BehaviorModule **m = obj->m_behaviors; *m; ++m)
				{
					serviceOS();
					CreateModuleInterface *create = (*m)->m_iface.getCreate();
					if (create)
						create->onBuildComplete();
				}
				team->setActive();
				TheAI->m_pathfinder->addObjectToPathfindMap(obj);
				serviceOS();
				ObjectMapPair entry;
				entry.first = obj;
				entry.second = mapObj;
				created->push_back(entry);
				serviceOS();
			}
		}
	}
	Rva009EBAC0((Int)&assets);
}
