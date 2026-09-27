// Walks every live object and runs the AI-side action whose readiness gate is set.
// Candidate reconstruction of ?bfmeRunReadyAction@BfmeObjectAI@@QAEXXZ.
// Retail RVA 0x0027A7A0, 1083 bytes.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
#include <hash_map>
#include <new>
#include <vector>

typedef bool Bool;

typedef int ObjectID;

enum
{
	INVALID_OBJECT_ID = 0
};

enum KindOfType
{
	KINDOF_RUN_READY = 0x6c
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum DamageType
{
	BFME_DAMAGE_TYPE_8 = 8
};

enum DeathType
{
	BFME_DEATH_TYPE_0 = 0
};

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other)
		: x(other.x), y(other.y), z(other.z)
	{
	}

	float x;
	float y;
	float z;
};

class ModelConditionFlags
{
public:
	bool test(int bit) const { return m_bits.test(bit); }
	void set(int bit) { m_bits.set(bit); }

private:
	_STL::bitset<320> m_bits;
};

#define BFME_HAVE_COORD3D
#define BFME_HAVE_OBJECTID
#define BFME_HAVE_MODELCONDITIONFLAGS
#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType kind) const; \
	void setPosition(const Coord3D *position);
#define OBJECT_TU_MEMBERS \
	void kill(DamageType damage, DeathType death); \
	void notifyModelConditionChanged(); \
	void *unidentified_001BFE20() const; \
	void setLayer(PathfindLayerEnum layer);
#include "../Object/object.h"
#undef OBJECT_TU_MEMBERS
#undef THING_TU_MEMBERS
class Rva0027ObjectCallView
{
public:
	void kill(DamageType damage, DeathType death);
	void notifyModelConditionChanged();
	void *unidentified_001BFE20() const;
	void setLayer(PathfindLayerEnum layer);
};

class Rva0027AICallView
{
public:
	void destroyPath() throw();
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > BfmeObjectPtrHash;

class GameLogic
{
public:
	Object *getFirstObject(void);
	__forceinline Object *findObjectByID(ObjectID key)
	{
		if (key == INVALID_OBJECT_ID)
			return 0;
		BfmeObjectPtrHash::iterator it = m_objectHash.find(key);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_head[0xb0];
	BfmeObjectPtrHash m_objectHash;
};

class BfmeReadyGate
{
public:
	bool bfmeReady(void);
};

class BfmeObjAS
{
public:
	BfmeObjAS *bfmeParentAS(int which);
};

extern GameLogic *TheGameLogic; // retail 0x012F0898

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

struct Rva0027TemplateKindOfView
{
	char m_unknown00[0xc8];
	UnsignedInt m_kindOf[6];
};


class Locomotor;
class Waypoint;
class Path;

struct Rva003FD7D0Point
{
	float m_distance;
	float m_position[3];
	float m_nextPosition[3];
	int m_layer;
	int m_waypointID;
};


class Path
{
public:
	Coord3D bfmeGetLastValidWaypointPosition(void) const;
};

template <int N>
class Rva0027TerrainSlots : public Rva0027TerrainSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class Rva0027TerrainSlots<0>
{
};

class TerrainLogic : public Rva0027TerrainSlots<32>
{
public:
	virtual Waypoint *getWaypointByID(unsigned int waypointID);
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};
class Rva0027TerrainCallView
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};


struct Rva003FD060TerrainLogic;
extern Rva003FD060TerrainLogic *TheTerrainLogic;

template <int N>
class BfmeHordeSlots : public BfmeHordeSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class BfmeHordeSlots<0>
{
};

class HordeContainInterface : public BfmeHordeSlots<123>
{
public:
	virtual void scan(_STL::vector<ObjectID> *needRepath,
		_STL::vector<ObjectID> *lookupFailed,
		_STL::vector<ObjectID> *ok) = 0;
};

template <int N>
class BfmeObjectAISlots : public BfmeObjectAISlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class BfmeObjectAISlots<0>
{
};

class BfmeObjectAI : public BfmeObjectAISlots<122>
{
public:
	void bfmeRunReadyAction(void);
	virtual void completeReadyAction() = 0;

	void *m_bfmeModuleData;
	Object *m_object;
	char m_bfmeToGate[0x134];
	BfmeReadyGate *m_bfmeGate;
	char m_bfmeToLocomotor[0x88];
	Locomotor *m_curLocomotor;
	char m_bfmeToPathFlags[0x14e];
	unsigned char m_waitingForPath;
	unsigned char m_isAttackPath;
	char m_bfmeToBlocked[6];
	unsigned char m_isBlockedAndStuck;
};

extern void j_000022bb();
extern void j_00008a9e();
extern void j_0000ca68();
extern void j_0000d3b9();
extern void j_0000faa6();
extern void j_00014506();
extern void j_0001c675();
extern void j_0001f253();
extern void j_0002191d();
extern void j_000233d0();
extern void j_0003251f();
extern void j_0003a1a7();
extern void j_0000cb3f();
extern void j_000065e1();

static __forceinline const Overridable *resolveFinalOverride(
	Overridable *override)
{
	typedef const Overridable *(Overridable::*Call)() const;
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_000022bb;
	return (override->*cast.asMember)();
}

static __forceinline BfmeObjAS *getParentAS(BfmeObjAS *object)
{
	typedef BfmeObjAS *(BfmeObjAS::*Call)(int);
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_0000faa6;
	return (object->*cast.asMember)(0);
}

static __forceinline void computePointOnPath(Path *path, Object *object,
	Locomotor *locomotor, Rva003FD7D0Point *point, bool useCache)
{
	typedef void (Path::*Call)(Object *, Locomotor *, Rva003FD7D0Point *, bool);
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_00008a9e;
	(path->*cast.asMember)(object, locomotor, point, useCache);
}

static __forceinline bool isKindOf(Object *object, KindOfType kind)
{
	typedef Bool (Thing::*Call)(KindOfType) const;
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_0003251f;
	return ((Thing *)object->*cast.asMember)(kind);
}

static __forceinline void *getHordeContainInterface(Object *object)
{
	typedef void *(Rva0027ObjectCallView::*Call)() const;
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_0000d3b9;
	return (((Rva0027ObjectCallView *)object)->*cast.asMember)();
}

static __forceinline Object *findObjectByID(ObjectID id)
{
	typedef Object *(GameLogic::*Call)(ObjectID);
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_0001f253;
	return (TheGameLogic->*cast.asMember)(id);
}

static __forceinline void killObject(Object *object)
{
	typedef void (Rva0027ObjectCallView::*Call)(DamageType, DeathType);
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_00014506;
	(((Rva0027ObjectCallView *)object)->*cast.asMember)(
		BFME_DAMAGE_TYPE_8, BFME_DEATH_TYPE_0);
}

static __forceinline void notifyModelConditionChanged(Object *object)
{
	typedef void (Rva0027ObjectCallView::*Call)();
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_0002191d;
	(((Rva0027ObjectCallView *)object)->*cast.asMember)();
}

// The retail callee returns Coord3D through the hidden result pointer.
static __forceinline void getLastValidWaypointPosition(const Path *path,
	Coord3D *position)
{
	typedef void (Path::*Call)(Coord3D *) const;
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_000233d0;
	(path->*cast.asMember)(position);
}


static __forceinline void setObjectPosition(Object *object,
	const Coord3D *position)
{
	typedef void (Thing::*Call)(const Coord3D *);
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_0003a1a7;
	((Thing *)object->*cast.asMember)(position);
}

static __forceinline PathfindLayerEnum getLayerForDestination(
	TerrainLogic *terrain, Object *object, const Coord3D *position)
{
	typedef PathfindLayerEnum (Rva0027TerrainCallView::*Call)(Object *,
		const Coord3D *);
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_0001c675;
	return (((Rva0027TerrainCallView *)terrain)->*cast.asMember)(
		object, position);
}

static __forceinline void setObjectLayer(Object *object,
	PathfindLayerEnum layer)
{
	typedef void (Rva0027ObjectCallView::*Call)(PathfindLayerEnum);
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_0000cb3f;
	(((Rva0027ObjectCallView *)object)->*cast.asMember)(layer);
}

static __forceinline void destroyPath(Path *path)
{
	typedef void (Path::*Call)();
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_0000ca68;
	(path->*cast.asMember)();
	operator delete(path);
}
static __forceinline void destroyReadyPath(BfmeObjectAI *ai) throw()
{
	typedef void (Rva0027AICallView::*Call)();
	union
	{
		void *asVoid;
		Call asMember;
	} cast;
	cast.asVoid = (void *)j_000065e1;
	(((Rva0027AICallView *)ai)->*cast.asMember)();
}

static __forceinline void clearPath(BfmeObjectAI *ai)
{
	Path *path = (Path *)ai->m_bfmeGate;
	if (path != 0)
		destroyPath(path);

	ai->m_bfmeGate = 0;
	ai->m_waitingForPath = false;
	ai->m_isBlockedAndStuck = false;
	ai->m_isAttackPath = false;
	ai->completeReadyAction();
}

// ?bfmeRunReadyObjectAI@@YAXXZ
void __cdecl bfmeRunReadyObjectAI(void)
{
	for (Object *object = TheGameLogic->getFirstObject(); object != 0;
		object = object->m_next)
	{
		BfmeObjectAI *ai = (BfmeObjectAI *)object->m_ai;
		if (ai != 0 && ai->m_bfmeGate != 0 && ai->m_bfmeGate->bfmeReady())
			ai->bfmeRunReadyAction();
	}
}

// ?bfmeRunReadyAction@BfmeObjectAI@@QAEXXZ present-unmatched
void BfmeObjectAI::bfmeRunReadyAction(void)
{
	Object *object = m_object;
	Overridable *thingTemplate = (Overridable *)object->m_template;
	if (thingTemplate == 0)
	{
		thingTemplate = 0;
	}
	else if (thingTemplate->m_nextOverride != 0)
	{
		thingTemplate = (Overridable *)resolveFinalOverride(
			thingTemplate->m_nextOverride);
	}

	if ((((Rva0027TemplateKindOfView *)thingTemplate)->m_kindOf[
			KINDOF_RUN_READY / 32] &
			(1u << (KINDOF_RUN_READY % 32))) == 0)
	{
		BfmeObjAS *parent = getParentAS((BfmeObjAS *)object);
		if (parent != 0)
		{
			BfmeObjectAI *parentAI =
				(BfmeObjectAI *)((Object *)parent)->m_ai;
			if (parentAI == 0)
				return;
			if (parentAI->m_bfmeGate != 0)
			{
				parentAI->bfmeRunReadyAction();
				return;
			}
			goto destroy_current_path;
		}
	}

	if (m_bfmeGate == 0)
		return;

	Rva003FD7D0Point point;
	computePointOnPath((Path *)m_bfmeGate, object, m_curLocomotor,
		&point, false);
	if ((UnsignedInt)point.m_waypointID == 0x7fffffff)
	{
		goto destroy_current_path;
	}

	if (((TerrainLogic *)TheTerrainLogic)->getWaypointByID(
			(UnsignedInt)point.m_waypointID) == 0)
	{
		if (isKindOf(object, KINDOF_RUN_READY))
		{
			HordeContainInterface *horde =
				(HordeContainInterface *)getHordeContainInterface(object);
			if (horde == 0)
				return;

			{
				bool shouldUpdatePosition;
				_STL::vector<ObjectID> needRepath;
				_STL::vector<ObjectID> lookupFailed;
				_STL::vector<ObjectID> ok;

				horde->scan(&needRepath, &lookupFailed, &ok);

				for (_STL::vector<ObjectID>::iterator it = lookupFailed.begin();
					it != lookupFailed.end(); ++it)
				{
					Object *member = findObjectByID(*it);
					if (member != 0)
					{
						killObject(member);
						if (!member->m_modelConditionFlags.test(115))
						{
							member->m_modelConditionFlags.set(115);
							notifyModelConditionChanged(member);
						}
					}
				}

				shouldUpdatePosition = false;
				if (ok.size() < needRepath.size())
				{
					ok = needRepath;
					shouldUpdatePosition = true;
				}

				for (_STL::vector<ObjectID>::iterator it = needRepath.begin();
					it != needRepath.end(); ++it)
				{
					Object *member = findObjectByID(*it);
					if (member != 0)
					{
						killObject(member);
						if (!member->m_modelConditionFlags.test(115))
						{
							member->m_modelConditionFlags.set(115);
							notifyModelConditionChanged(member);
						}
					}
				}

				for (_STL::vector<ObjectID>::iterator it = ok.begin();
					it != ok.end(); ++it)
				{
					Object *member = TheGameLogic->findObjectByID(*it);
					if (member != 0)
					{
						BfmeObjectAI *memberAI =
							(BfmeObjectAI *)member->m_ai;
						if (memberAI != 0)
							clearPath(memberAI);
					}
				}

				if (shouldUpdatePosition)
				{
					Coord3D position;
					getLastValidWaypointPosition((Path *)m_bfmeGate, &position);
					setObjectPosition(object, &position);
					PathfindLayerEnum layer =
						getLayerForDestination((TerrainLogic *)TheTerrainLogic,
							object, &position);
					setObjectLayer(object, layer);
					clearPath(this);
				}
			}
			return;
		}
		killObject(object);
		return;
	}

destroy_current_path:
	destroyReadyPath(this);
}
