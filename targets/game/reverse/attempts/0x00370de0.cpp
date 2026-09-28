// ?rva00370de0@CastleBehavior@@QAEXPAVObject@@@Z
// partial score=0.977 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva00370de0@CastleBehavior@@QAEXPAVObject@@@Z

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
typedef bool Bool;
typedef int Int;
typedef int ObjectID;
typedef float Real;

#include <set>

#include "coord3d.h"
#include "ascii_string.h"
template <class T> inline const T *StringBase<T>::str() const { return m_data ? m_data->data : (const T*)""; }

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
	unsigned char m_pad24[0xCC - 0x24];
	unsigned int m_flagsCC;
};

class AIUpdateInterface;

class Thing
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = (const ThingTemplate *)
				thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}

	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3DBase m_cachedPos;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_pad78[0x204 - 0x78];
};

class Object : public Thing
{
public:
	AIUpdateInterface *m_ai;
};

template<int N> class Rva00370DE0AIBase : public Rva00370DE0AIBase<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<> class Rva00370DE0AIBase<0>
{
public:
	virtual Bool slot000() = 0;
};

class AIUpdateInterface : public Rva00370DE0AIBase<81>
{
public:
	virtual AIUpdateInterface *slot148() = 0;

	void requestPath(Coord3D *destination, Bool isFinalGoal);
};

class Pathfinder
{
};

class AI
{
public:
	unsigned char m_pad00[0x0C];
	Pathfinder *m_pathfinder;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

typedef void (__cdecl *Rva00370DE0Logger)(void *, const char *, ...);
extern void j_0003a17a();
extern void j_00015d02();
extern void j_00032dee();
extern void j_0003bcff();

class Rva00370DE0Receiver
{
};

template<class T> __forceinline T Rva00370DE0Member(void (*raw)())
{
	union { void (*raw)(); T member; } fn;
	fn.raw = raw;
	return fn.member;
}

#define Rva00370DE0CALL(T, object, function) \
	(((Rva00370DE0Receiver *)(object))->*Rva00370DE0Member<T>(function))

struct Gen_t_000ef440_k4
{
	int value;
};

bool operator==(const Gen_t_000ef440_k4 &, const Gen_t_000ef440_k4 &);
bool operator<(const Gen_t_000ef440_k4 &, const Gen_t_000ef440_k4 &);

#pragma comment(linker, "/alternatename:?insert_unique@?$_Rb_tree@UGen_t_000ef440_k4@@U1@U?$_Identity@UGen_t_000ef440_k4@@@_STL@@U?$less@UGen_t_000ef440_k4@@@3@V?$allocator@UGen_t_000ef440_k4@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@UGen_t_000ef440_k4@@U?$_Nonconst_traits@UGen_t_000ef440_k4@@@_STL@@@_STL@@_N@2@ABUGen_t_000ef440_k4@@@Z=?j_000499f9@@YAXXZ")

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class FoundationAIUpdateIface3
{
public:
	virtual void interface3Anchor() = 0;
};

class Gen_dtor_000b33c0
{
public:
	virtual ~Gen_dtor_000b33c0();

private:
	unsigned char m_data[0x6c];
};

class FoundationAIUpdate : public UpdateModule, public FoundationAIUpdateIface3
{
public:
	virtual ~FoundationAIUpdate();

private:
	Gen_dtor_000b33c0 m_member;
	void *m_pendingFoundation;
	bool m_pendingFlag;
};

class CastleBehavior : public FoundationAIUpdate
{
public:
	virtual ~CastleBehavior();
	void rva00370de0(Object *object);

private:
	int m_at9c;
	ObjectID m_objectID;
	unsigned char m_padA4[0xF4 - 0xA4];
	_STL::set<Gen_t_000ef440_k4> m_ownedObjectsF4;
};

void CastleBehavior::rva00370de0(Object *object)
{
	if (object == 0)
		return;

	const ThingTemplate *thingTemplate = object->getTemplate();
	if ((thingTemplate->m_flagsCC & 0x8000) != 0)
	{
		Object *pending;
		pending = (*(GameLogic **)0x012F0898)->findObjectByID(m_objectID);
		if (pending == 0)
			return;

		AIUpdateInterface *ai = object->m_ai;
		if (ai == 0)
			return;
 {
		AIUpdateInterface *query = ai->slot148();
		if (query == 0)
			return;

		if (*(Bool *)0x012F0238)
		{
			void *logger = *(void **)0x012ED4FC;
			if (logger)
				((Rva00370DE0Logger)j_0003a17a)(logger,
					(const char *)0x010E9978, object->getTemplate()->m_name.str());
		}

		if (!query->slot000())
		{
			if (*(Bool *)0x012F0238)
			{
				void *logger = *(void **)0x012ED4FC;
				if (logger)
					((Rva00370DE0Logger)j_0003a17a)(logger,
						(const char *)0x010E9938, object->getTemplate()->m_name.str());
			}
			return;
		}

 }
		Coord3DBase destination;
        destination.x=object->m_cachedPos.x; destination.y=object->m_cachedPos.y; destination.z=object->m_cachedPos.z;
		((Coord3D*)&destination)->Sub(pending->m_cachedPos);
		((Coord3D*)&destination)->Normalize();
		destination.x *= *(Real *)0x0109A028;
		destination.y *= *(Real *)0x0109A028;
		destination.z *= *(Real *)0x0109A028;
		((Coord3D*)&destination)->Add(object->m_cachedPos);

		Rva00370DE0CALL(void (Rva00370DE0Receiver::*)(Object *),
			(*(AI **)0x012EF214)->m_pathfinder, j_00015d02)(object);
		Rva00370DE0CALL(void (Rva00370DE0Receiver::*)(Coord3D *, Bool),
			ai, j_0003bcff)((Coord3D*)&destination, true);

		if (*(Bool *)0x012F0238)
		{
			void *logger = *(void **)0x012ED4FC;
			if (logger)
				((Rva00370DE0Logger)j_0003a17a)(logger,
					(const char *)0x010E98E0, object->getTemplate()->m_name.str(),
					(double)destination.x, (double)destination.y, (double)destination.z);
		}
		return;
	}

	Rva00370DE0CALL(void (Rva00370DE0Receiver::*)(Int, Bool), object,
		j_00032dee)(0x54, true);
 {
	Gen_t_000ef440_k4 value;
	value.value = object->m_id;
	m_ownedObjectsF4.insert(value);
 }
}

#undef Rva00370DE0CALL
