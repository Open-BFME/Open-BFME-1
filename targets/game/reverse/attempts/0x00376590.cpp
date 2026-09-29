// ?unpack@CastleBehavior@@QAEX_N@Z
// partial score=0.9846 date=2026-09-28
// ?unpack@CastleBehavior@@QAEX_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_NEWALLOC 1
#include <bitset>
#include <hash_map>
#include <vector>
#include "ascii_string.h"

template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef Int ObjectID;

enum NameKeyType { NAMEKEY_INVALID = 0 };

struct Coord3D
{
	Real x, y, z;
};

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit };
	BitFlags(BogusInitType, Int bit) { m_bits.set(bit); }
private:
	_STL::bitset<NUMBITS> m_bits;
};
typedef BitFlags<86> ObjectStatusMaskType;

class ModelConditionFlags
{
public:
	UnsignedInt test(Int bit) const { return m_bits[bit >> 5] & (1u << (bit & 31)); }
	void set(Int bit) { m_bits[bit >> 5] |= (1u << (bit & 31)); }
	void reset(Int bit) { m_bits[bit >> 5] &= ~(1u << (bit & 31)); }
private:
	UnsignedInt m_bits[10];
};

class Player
{
public:
	unsigned char m_pad00[0x1c];
	AsciiString m_playerName;
};

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0x18];
	AsciiString m_name;
};

class Drawable
{
	friend class CastleBehavior;
	void applyPendingModelConditionFlags(Bool);
};

class Module;

class Object
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual Drawable *getDrawable() const;

	Player *getControllingPlayer() const;
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void notifyModelConditionChanged();
	Module *findModule(NameKeyType key) const;

	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_position; }
	const ThingTemplate *getTemplate() const { return m_template; }

	ThingTemplate *m_template;
	unsigned char m_pad08[0x30];
	Coord3D m_position;
	unsigned char m_pad44[0x30];
	ObjectID m_id;
	unsigned char m_pad78[0x98];
	ModelConditionFlags m_modelConditionFlags;
	unsigned char m_pad138[0x120];
	Real m_unpackCost258;
};

static __forceinline void clearAndSetCondition(Object *object, Int clr, Int set)
{
	if (object->m_modelConditionFlags.test(clr) || !object->m_modelConditionFlags.test(set))
	{
		object->m_modelConditionFlags.reset(clr);
		object->m_modelConditionFlags.set(set);
		object->notifyModelConditionChanged();
	}
}

class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *object);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	__forceinline Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;
		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;
		return it->second;
	}
	Int getCRCTraceLevel() const { return m_crcTraceLevel; }

private:
	typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
	unsigned char m_pad40[0x70];
	ObjectPtrHash m_objHash;
	unsigned char m_padC4[0xdc];
	Int m_crcTraceLevel;
};

struct BfmeResFFG
{
	unsigned char m_pad00[0x370];
	Int m_id;
};

struct BfmeSubFFG;

class BfmeMidFFG
{
public:
	BfmeResFFG *bfmeFindFFG(BfmeSubFFG *source);
};

extern void j_0002d740(void);
class CastleMemberBehavior
{
public:
	unsigned char m_pad00[0x14];
	Int m_castleID014;
	ObjectID m_castleObjectID018;
	void setCastle(Int castleID, ObjectID objectID) { m_castleID014 = castleID; m_castleObjectID018 = objectID; }
};

class CastleBehaviorModuleData
{
public:
	unsigned char m_pad00[0x38];
	Real m_clearRadius038;
};

extern AI *TheAI;
extern BfmeThingFactory *TheThingFactory;
extern NameKeyGenerator *TheNameKeyGenerator;
class TerrainLogic
{
public:
	void clearNear001ACCC0(const Coord3D *pos, Real radius)
	{
		union { void *raw; void (TerrainLogic::*fn)(const Coord3D *, Real); } clear;
		clear.raw = (void *)j_0002d740;
		(this->*clear.fn)(pos, radius);
	}
};
extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheBfmeGameLogic;
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck *check, const char *format, ...);

extern void j_0003091d(void);
extern void j_0003d0af(void);
extern void j_0000eb97(void);
extern void j_000150cd(void);
extern void j_000293f7(void);
extern void j_00036070(void);
extern void j_0000796e(void);

class CastleBehavior
{
public:
	void unpack(Bool unpack);

private:
	Object *getObject() const { return m_object; }
	const CastleBehaviorModuleData *getCastleBehaviorModuleData() const { return m_moduleData; }

	void *m_vtable;
	const CastleBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x94];
	Int m_castleID0A0;
	unsigned char m_padA4[8];
	Bool m_flag0AC;
	unsigned char m_padAD[3];
	UnsignedInt m_unpackFrame0B0;
	Real m_unpackCost0B4;
	_STL::vector<ObjectID> m_members0B8;
	_STL::vector<ObjectID> m_members0C4;
	_STL::vector<ObjectID> m_members0D0;
	_STL::vector<ObjectID> m_members0DC;
	unsigned char m_padE8[0x18];
	AsciiString m_pendingObjectName;
	Int m_regionID104;
};

void CastleBehavior::unpack(Bool unpack)
{
	Object *obj = getObject();
	if (obj == 0)
		return;

	TheAI->pathfinder()->removeObjectFromPathfindMap(obj);
	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 4), true);

	Object *self = getObject();
	Player *player = self->getControllingPlayer();
	BfmeResFFG *region = ((BfmeMidFFG *)player)->bfmeFindFFG((BfmeSubFFG *)self->getPosition());
	m_regionID104 = region ? region->m_id : -1;
	m_flag0AC = false;

	if (!m_pendingObjectName.isEmpty())
	{
		const ThingTemplate *tmpl = TheThingFactory->findTemplate(m_pendingObjectName);
		if (tmpl)
		{
			union { void *raw; Object *(CastleBehavior::*fn)(const ThingTemplate *); } create;
			create.raw = (void *)j_0003d0af;
			Object *created = (this->*create.fn)(tmpl);
			UnsignedInt cost = 0;
			if (!unpack)
			{
				union { void *raw; UnsignedInt (CastleBehavior::*fn)(const ThingTemplate *); } withdraw;
				withdraw.raw = (void *)j_0000eb97;
				cost = (this->*withdraw.fn)(tmpl);
			}
			if (created)
				created->m_unpackCost258 = (Real)cost;
		}
		m_pendingObjectName.set(*(const AsciiString *)0x01336E50);
	}
	else
	{
		if (!unpack)
		{
			m_unpackCost0B4 = 0;
			union { void *raw; void (CastleBehavior::*fn)(); } charge;
			charge.raw = (void *)j_000150cd;
			(this->*charge.fn)();
		}
		union { void *raw; void (CastleBehavior::*fn)(Bool); } instantiate;
		instantiate.raw = (void *)j_000293f7;
		(this->*instantiate.fn)(unpack);
		union { void *raw; void (CastleBehavior::*fn)(); } createPlayerObject;
		createPlayerObject.raw = (void *)j_00036070;
		(this->*createPlayerObject.fn)();
	}

	if (TheTerrainLogic)
	{
		Real radius = 0.0f;
		if (getCastleBehaviorModuleData())
			radius = getCastleBehaviorModuleData()->m_clearRadius038;
		TheTerrainLogic->clearNear001ACCC0(obj->getPosition(), radius);
	}

	typedef void (__cdecl *SetMemberPayload)(_STL::vector<ObjectID> *, Int);
	((SetMemberPayload)j_0003091d)(&m_members0B8, m_castleID0A0);
	((SetMemberPayload)j_0003091d)(&m_members0C4, m_castleID0A0);
	((SetMemberPayload)j_0003091d)(&m_members0DC, m_castleID0A0);
	m_unpackFrame0B0 = TheBfmeGameLogic->getFrame();

	for (_STL::vector<ObjectID>::iterator it = m_members0B8.begin(); it != m_members0B8.end(); ++it)
	{
		Object *member = TheBfmeGameLogic->findObjectByID(*it);
		if (member)
		{
			static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
			CastleMemberBehavior *cmb = (CastleMemberBehavior *)member->findModule(key);
			if (cmb)
			{
				cmb->m_castleID014 = m_castleID0A0;
				cmb->m_castleObjectID018 = getObject()->getID();
			}
		}
	}

	for (_STL::vector<ObjectID>::iterator it2 = m_members0DC.begin(); it2 != m_members0DC.end(); ++it2)
	{
		Object *member = TheBfmeGameLogic->findObjectByID(*it2);
		if (member)
		{
			static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
			CastleMemberBehavior *cmb = (CastleMemberBehavior *)member->findModule(key);
			if (cmb)
				cmb->setCastle(m_castleID0A0, getObject()->getID());
		}
	}

	clearAndSetCondition(obj, 93, 95);
	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 3), true);
	obj->getDrawable()->applyPendingModelConditionFlags(false);
	union { void *raw; void (CastleBehavior::*fn)(); } refresh;
	refresh.raw = (void *)j_0000796e;
	(this->*refresh.fn)();

	if (TheBfmeGameLogic->getCRCTraceLevel() > 0)
	{
		if (!TheCRCParameterCheck)
			return;
		const char *callerName = obj->getControllingPlayer()->m_playerName.str();
		const ObjectID castleID = obj->getID();
		const ThingTemplate *thingTemplate = obj->getTemplate();
		const ThingTemplate *finalTemplate = thingTemplate;
		if (thingTemplate == 0)
			finalTemplate = 0;
		else if (thingTemplate->m_nextOverride)
			finalTemplate = (const ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
		else
			finalTemplate = thingTemplate;
		const char *castleName = finalTemplate->m_name.str();
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CAMP: Frame %d: Castle %s(%d) ::unpack() called by %s",
			TheBfmeGameLogic->getFrame(), castleName, castleID, callerName);
	}
}
