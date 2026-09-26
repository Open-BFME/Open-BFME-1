// ?unpack@CastleBehavior@@QAEX_N@Z
// partial score=0.28 date=2026-09-22
// ?unpack@CastleBehavior@@QAEX_N@Z
// CastleBehavior's owned-object unpack path.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_NEWALLOC 1
#include <bitset>
#include <hash_map>
#include <set>
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType { };

template <int NUMBITS>
class BitFlags
{
public:
	enum InitType { kInit };

	BitFlags() { }

	BitFlags(InitType, Int bit)
	{
		m_bits._Unchecked_set(bit);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Player
{
public:
	unsigned char m_pad00[0x1c];
	struct Name
	{
		void *m_data;
	};
	Name m_playerName;
};

class Drawable
{
public:
	void applyPendingModelConditionFlags(Bool immediate);
};

class ThingTemplate;
class Module;

class AsciiString
{
public:
	void *m_data;
};

class Object
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0c() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1c() = 0;
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual Drawable *getDrawable() const;

	Player *getControllingPlayer() const;
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void notifyModelConditionChanged();
	Module *findModule(NameKeyType key) const;

	ThingTemplate *m_template;

	Int getID() const
	{
		return *(const Int *)((const char *)this + 0x74);
	}

	Int &status118()
	{
		return *(Int *)((char *)this + 0x118);
	}
};

class ThingTemplate
{
public:
	void *m_vtable;
	ThingTemplate *m_nextOverride;
	unsigned char m_pad08[0x18];
	struct Name
	{
		void *m_data;
	};
	Name m_name;
	const ThingTemplate *getFinalOverride() const;
};

class BfmeResult
{
public:
	unsigned char m_pad00[0x370];
	Int m_id;

	Int getID() const { return m_id; }
};

class CastleMemberBehavior
{
public:
	unsigned char m_pad00[0x14];
	Int m_castleObjectID;
	Int m_objectID;
};

class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *object);
};

class BfmeHostCL;

class BfmePathCL
{
public:
	void bfmeDropOneCL(BfmeHostCL *object);
};

class AI
{
public:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;
};

class BfmeThingFactory
{
public:
	void *findTemplate(const AsciiString &name) const;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	Int m_frame;
	unsigned char m_pad40[0x70];
	_STL::hash_map<Int, Object *> m_objects;
};

class TerrainLogic
{
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeSubFFG
{
};

class BfmeResFFG
{
public:
	unsigned char m_pad00[0x370];
	Int m_id;
};

class BfmeMidFFG
{
public:
	BfmeResFFG *bfmeFindFFG(BfmeSubFFG *source);
};

class UnicodeString
{
public:
	void set(const UnicodeString &that);
	void *m_data;
};

struct BfmeTripleZP
{
	void *m_a;
	void *m_b;
	void *m_c;
};

class Rva0036BA60PurchaseContext
{
public:
	UnsignedInt withdrawPurchaseCost(const void *cost) const;
};

class CastleBehavior;

typedef void (__cdecl *VectorUpdateCall)(void *, Int);
typedef void (__cdecl *TerrainUpdateCall)(void *, void *);
typedef UnsignedInt (Rva0036BA60PurchaseContext::*WithdrawCall)(
	const void *) const;
typedef void (CastleBehavior::*BoolUpdateCall)(Bool);
typedef void (CastleBehavior::*NoArgUpdateCall)();
typedef void (Pathfinder::*DropCall)(Object *);
typedef void (Object::*SetStatusCall)(const ObjectStatusMaskType &, Bool);
typedef Player *(Object::*ControllingPlayerCall)() const;
typedef void *(BfmeThingFactory::*FindCall)(const AsciiString &) const;
typedef Object *(CastleBehavior::*CreateCall)(void *);
typedef void (CastleBehavior::*ChargeCall)();
typedef Module *(Object::*FindModuleCall)(NameKeyType) const;
typedef void (Object::*NotifyCall)();
typedef void (Drawable::*ApplyCall)(Bool);
typedef const ThingTemplate *(ThingTemplate::*OverrideCall)() const;
typedef void (__cdecl *DebugLogFunction)(void *, const char *, ...);

extern void j_00006d7f(void);

extern void j_000022bb(void);

extern void j_00020824(void);
extern void j_0002191d(void);
extern void j_00028560(void);
extern void j_0000eb97(void);
extern void j_000150cd(void);
extern void j_000293f7(void);
extern void j_0002d439(void);
extern void j_0002d740(void);
extern void j_0002ae23(void);
extern void j_0003091d(void);
extern void j_00036070(void);
extern void j_000307e7(void);
extern void j_0003add7(void);
extern void j_0003d0af(void);
extern void j_0003a17a(void);
extern void j_0003b890(void);
extern void j_0000796e(void);

#define TheAI (*(AI **)0x012EF214)
#define TheThingFactory (*(BfmeThingFactory **)0x012EF1D8)
#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheNameKeyGenerator (*(NameKeyGenerator **)0x012ED600)
#define g_012ED4FC (*(void **)0x012ED4FC)

class CastleBehavior
{
public:
	void unpack(Bool unpack);
	void chargePlayerForUnpack();
	Object *createOwnedObject(void *definition);

private:
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x90];
	Int m_state;
	Int m_objectID;
	unsigned char m_padA4[8];
	Bool m_flagAC;
	unsigned char m_padAD[3];
	Int m_lastFrame;
	float m_unpackedCost;
	_STL::vector<Int> m_ownedObjectsB8;
	_STL::vector<Int> m_ownedObjectsC4;
	_STL::vector<Int> m_ownedObjectsD0;
	_STL::vector<Int> m_ownedObjectsDC;
	_STL::vector<Int> m_ownedObjectsE8;
	_STL::set<Int> m_ownedObjectSetF4;
	UnicodeString m_objectName;
	Int m_objectNameKey;
};

void CastleBehavior::unpack(Bool unpack)
{
	Object *object = m_object;
	if (object != 0)
	{
		((BfmePathCL *)TheAI->m_pathfinder)->bfmeDropOneCL(
			(BfmeHostCL *)object);

		ObjectStatusMaskType status(ObjectStatusMaskType::kInit, 4);
		union { void *asVoid; SetStatusCall asMember; } setStatusCast;
		setStatusCast.asVoid = (void *)j_000307e7;
		(object->*setStatusCast.asMember)(status, true);

		union { void *asVoid; ControllingPlayerCall asMember; }
			controllingPlayerCast;
		controllingPlayerCast.asVoid = (void *)j_00020824;
		Player *player = (object->*controllingPlayerCast.asMember)();
		BfmeResFFG *result = ((BfmeMidFFG *)player)->bfmeFindFFG(
			(BfmeSubFFG *)((char *)object + 0x38));
		m_objectID = result != 0 ? result->m_id : -1;
		m_flagAC = false;

		UnicodeString *name = &m_objectName;
		if (name->m_data != 0 &&
			*(const unsigned short *)((const char *)name->m_data + 4) != 0)
		{
			union { void *asVoid; FindCall asMember; } findCast;
			findCast.asVoid = (void *)j_00028560;
			void *definition = (TheThingFactory->*findCast.asMember)(
				*(const AsciiString *)name);
			if (definition != 0)
			{
				union { void *asVoid; CreateCall asMember; } createCast;
				createCast.asVoid = (void *)j_0003d0af;
				Object *created = (this->*createCast.asMember)(definition);
				UnsignedInt cost = 0;
				if (!unpack)
				{
					union { void *asVoid; WithdrawCall asMember; } withdrawCast;
					withdrawCast.asVoid = (void *)j_0000eb97;
					cost = (((Rva0036BA60PurchaseContext *)this)->*
						withdrawCast.asMember)(definition);
				}
				if (created != 0 && cost != 0)
				{
					float value = (float)cost;
					*(float *)((char *)created + 0x258) = value;
				}
			}
			name->set(*(const UnicodeString *)0x01336E50);
		}
		else
		{
			if (!unpack)
			{
				m_unpackedCost = 0;
				union { void *asVoid; ChargeCall asMember; } chargeCast;
				chargeCast.asVoid = (void *)j_000150cd;
				(this->*chargeCast.asMember)();
			}
			union { void *asVoid; BoolUpdateCall asMember; } boolCast;
			boolCast.asVoid = (void *)j_000293f7;
			(this->*boolCast.asMember)(unpack);
			union { void *asVoid; NoArgUpdateCall asMember; } noArgCast;
			noArgCast.asVoid = (void *)j_00036070;
			(this->*noArgCast.asMember)();
		}

		if (TheTerrainLogic != 0)
		{
			void *moduleData = m_moduleData != 0 ?
				*(void **)((char *)m_moduleData + 0x38) : 0;
			((TerrainUpdateCall)j_0002d740)((char *)object + 0x38,
				moduleData);
		}

		((VectorUpdateCall)j_0003091d)(&m_ownedObjectsB8, m_objectID);
		((VectorUpdateCall)j_0003091d)(&m_ownedObjectsC4, m_objectID);
		((VectorUpdateCall)j_0003091d)(&m_ownedObjectsDC, m_objectID);
		m_lastFrame = TheBfmeGameLogic->m_frame;

		for (std::vector<Int>::iterator it = m_ownedObjectsB8.begin();
			it != m_ownedObjectsB8.end(); ++it)
		{
			Int id = *it;
			Object *owned = 0;
			if (id != 0)
			{
				_STL::hash_map<Int, Object *>::iterator found =
					TheBfmeGameLogic->m_objects.find(id);
				if (found != TheBfmeGameLogic->m_objects.end())
					owned = (*found).second;
			}
			if (owned != 0)
			{
				static NameKeyType key =
					TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
				union { void *asVoid; FindModuleCall asMember; } findModuleCast;
				findModuleCast.asVoid = (void *)j_0002ae23;
				CastleMemberBehavior *member =
					(CastleMemberBehavior *)
						(owned->*findModuleCast.asMember)(key);
				if (member != 0)
				{
					member->m_castleObjectID = m_objectID;
					member->m_objectID = object->getID();
				}
			}
		}

		for (std::vector<Int>::iterator it = m_ownedObjectsDC.begin();
			it != m_ownedObjectsDC.end(); ++it)
		{
			Int id = *it;
			Object *owned = 0;
			if (id != 0)
			{
				_STL::hash_map<Int, Object *>::iterator found =
					TheBfmeGameLogic->m_objects.find(id);
				if (found != TheBfmeGameLogic->m_objects.end())
					owned = (*found).second;
			}
			if (owned != 0)
			{
				static NameKeyType key =
					TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
				union { void *asVoid; FindModuleCall asMember; } findModuleCast;
				findModuleCast.asVoid = (void *)j_0002ae23;
				CastleMemberBehavior *member =
					(CastleMemberBehavior *)
						(owned->*findModuleCast.asMember)(key);
				if (member != 0)
				{
					member->m_castleObjectID = m_objectID;
					member->m_objectID = object->getID();
				}
			}
		}

		Int &status118 = object->status118();
		if ((status118 & 0x20000000) != 0 || status118 >= 0)
		{
			status118 &= 0xdfffffff;
			status118 |= 0x80000000;
			union { void *asVoid; NotifyCall asMember; } notifyCast;
			notifyCast.asVoid = (void *)j_0002191d;
			(object->*notifyCast.asMember)();
		}

		ObjectStatusMaskType finalStatus(ObjectStatusMaskType::kInit, 3);
		union { void *asVoid; SetStatusCall asMember; } finalStatusCast;
		finalStatusCast.asVoid = (void *)j_000307e7;
		(object->*finalStatusCast.asMember)(finalStatus, true);
		Drawable *drawable = object->getDrawable();
		union { void *asVoid; ApplyCall asMember; } applyCast;
		applyCast.asVoid = (void *)j_0002d439;
		(drawable->*applyCast.asMember)(false);
		union { void *asVoid; NoArgUpdateCall asMember; } processCast;
		processCast.asVoid = (void *)j_0000796e;
		(this->*processCast.asMember)();

		if (TheBfmeGameLogic->m_frame > 0 && g_012ED4FC != 0)
		{
			controllingPlayerCast.asVoid = (void *)j_00020824;
			Player *owner = (object->*controllingPlayerCast.asMember)();
			const char *callerName = owner->m_playerName.m_data != 0 ?
				(const char *)((const char *)owner->m_playerName.m_data + 8) :
				(const char *)0x0107388B;
			ThingTemplate *thingTemplate = object->m_template;
			ThingTemplate *finalTemplate = thingTemplate;
			if (thingTemplate->m_nextOverride != 0)
			{
				union { void *asVoid; OverrideCall asMember; } overrideCast;
				overrideCast.asVoid = (void *)j_000022bb;
				finalTemplate = (ThingTemplate *)
					(thingTemplate->m_nextOverride->*
						overrideCast.asMember)();
			}
			const char *castleName = finalTemplate->m_name.m_data != 0 ?
				(const char *)((const char *)finalTemplate->m_name.m_data + 8) :
				(const char *)0x0107388B;
			((DebugLogFunction)j_0003a17a)(g_012ED4FC,
				(const char *)0x010E9D50, TheBfmeGameLogic->m_frame,
				castleName, object->getID(), callerName);
		}
	}
}
