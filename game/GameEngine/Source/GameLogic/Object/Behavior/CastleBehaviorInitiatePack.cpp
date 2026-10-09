// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// CastleBehavior packing uses an address-derived receiver ABI view.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>
#include <bitset>
#include "CastleBehaviorRecovery.h"
#include "ascii_string.h"

typedef bool Bool;

template<int N> class BitFlags
{
public:
	BitFlags() {}
	void set(int bit) { m_bits._Unchecked_set(bit); }

private:
	_STL::bitset<N> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class ModelConditionFlags
{
public:
	bool test(int bit) const { return m_bits._Unchecked_test(bit); }
	void set(int bit) { m_bits._Unchecked_set(bit); }
	void reset(int bit) { m_bits._Unchecked_reset(bit); }

private:
	_STL::bitset<320> m_bits;
};

class Player
{
public:
	unsigned char m_pad00[0x1c];
	AsciiString m_playerName;
};

#define BFME_HAVE_MODELCONDITIONFLAGS
#define OBJECT_TU_MEMBERS void setStatus(const ObjectStatusMaskType &, Bool); Player *getControllingPlayer() const;
#include "object.h"
#include "../../game_logic.h"

class Drawable
{
public:
	void bfmeDelayA(int);

private:
	void applyPendingModelConditionFlags(bool);
	friend class CastleBehavior;
};

extern void j_00010820();
extern void j_000279f8();
extern void j_0002191d();
extern void j_00026094();
extern void j_00047c58();
extern void j_000022bb();
extern void j_0003a17a();

class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;

typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectPtrHash;

struct Rva00376C70Logic
{
	char m_pad00[0x3c];
	int m_frame;
	char m_pad40[0x70];
	ObjectPtrHash m_objects;
};

// ?findObject00376C70@@YAPAVObject@@H@Z absent-from-retail
static __forceinline Object *findObject00376C70(int id)
{
	if (!id)
		return 0;
	ObjectPtrHash &objects = ((Rva00376C70Logic *)TheGameLogic)->m_objects;
	ObjectPtrHash::iterator it = objects.find(id);
	if (it == objects.end())
		return 0;
	return (*it).second;
}

template<class T> static __forceinline T &field00376C70(void *p, int offset)
{
	return *(T *)((char *)p + offset);
}

class Rva00376C70Calls {};

template<class R> static __forceinline R call00376C70(void (*fn)(), void *self)
{
	typedef R (Rva00376C70Calls::*F)();
	union { void (*fn)(); F f; } u;
	u.fn = fn;
	return (((Rva00376C70Calls *)self)->*u.f)();
}

template<class A> static __forceinline void call00376C70(void (*fn)(), void *self, A a)
{
	typedef void (Rva00376C70Calls::*F)(A);
	union { void (*fn)(); F f; } u;
	u.fn = fn;
	(((Rva00376C70Calls *)self)->*u.f)(a);
}

template<class A, class B> static __forceinline void call00376C70(void (*fn)(), void *self, A a, B b)
{
	typedef void (Rva00376C70Calls::*F)(A, B);
	union { void (*fn)(); F f; } u;
	u.fn = fn;
	(((Rva00376C70Calls *)self)->*u.f)(a, b);
}

struct Rva00376C70TreeNode
{
	unsigned char color;
	unsigned char m_pad01[3];
	Rva00376C70TreeNode *parent, *left, *right;
};

struct Rva00376C70Tree
{
	Rva00376C70TreeNode *m_header;
	int m_size;

	// ?clear@Rva00376C70Tree@@QAEXXZ absent-from-retail
	void clear()
	{
		if (m_size)
		{
			call00376C70(j_00047c58, this, m_header->parent);
			m_header->left = m_header;
			m_header->parent = 0;
			m_header->right = m_header;
			m_size = 0;
		}
	}
};

struct Rva00376C70Data
{
	char m_pad00[0x28];
	float m_wait28;
};

// ?initiatePack@CastleBehavior@@QAEXXZ
void CastleBehavior::initiatePack()
{
	Rva00376C70Data *data = field00376C70<Rva00376C70Data *>(this, 4);
	Object *object = field00376C70<Object *>(this, 8);
	if (!object)
		return;
	call00376C70<void>(j_00010820, this);
	field00376C70<int>(this, 0x9c) = 5;
	call00376C70(j_000279f8, this, object);
	int delay = (int)(data->m_wait28 * 30.0f);
	for (_STL::vector<ObjectID>::iterator it = field00376C70<_STL::vector<ObjectID> >(this, 0xb8).begin(); it != field00376C70<_STL::vector<ObjectID> >(this, 0xb8).end(); ++it)
	{
		Object *owned = findObject00376C70(*it);
		if (owned)
			owned->getDrawable()->bfmeDelayA(delay);
	}
	for (_STL::vector<ObjectID>::iterator it = field00376C70<_STL::vector<ObjectID> >(this, 0xdc).begin(); it != field00376C70<_STL::vector<ObjectID> >(this, 0xdc).end(); ++it)
	{
		Object *owned = findObject00376C70(*it);
		if (owned)
			owned->getDrawable()->bfmeDelayA(delay);
	}
	for (_STL::vector<ObjectID>::iterator it = field00376C70<_STL::vector<ObjectID> >(this, 0xc4).begin(); it != field00376C70<_STL::vector<ObjectID> >(this, 0xc4).end(); ++it)
	{
		Object *owned = findObject00376C70(*it);
		if (owned)
			owned->getDrawable()->bfmeDelayA(delay);
	}
	if (object->m_modelConditionFlags.test(207))
	{
		object->m_modelConditionFlags.reset(207);
		call00376C70<void>(j_0002191d, object);
	}
	if (object->m_modelConditionFlags.test(95) || !object->m_modelConditionFlags.test(93))
	{
		object->m_modelConditionFlags.reset(95);
		object->m_modelConditionFlags.set(93);
		call00376C70<void>(j_0002191d, object);
	}
	ObjectStatusMaskType mask;
	mask.set(3);
	object->setStatus(mask, false);
	object->getDrawable()->applyPendingModelConditionFlags(false);
	call00376C70(j_00026094, this, 5, true);
	field00376C70<float>(this, 0xa8) = data->m_wait28;
	field00376C70<Rva00376C70Tree>(this, 0x108).clear();
	if (field00376C70<int>(TheGameLogic, 0x1a0) > 0 && TheCRCParameterCheck)
	{
		const char *caller = object->getControllingPlayer()->m_playerName.str();
		int id = object->m_id;
		ThingTemplate *tmpl = object->m_template;
		if (!tmpl)
			tmpl = 0;
		else if (field00376C70<void *>(tmpl, 4))
			tmpl = call00376C70<ThingTemplate *>(j_000022bb, field00376C70<void *>(tmpl, 4));
		const char *name = field00376C70<AsciiString>(tmpl, 0x20).str();
		typedef void (__cdecl *Log)(void *, const char *, ...);
		((Log)j_0003a17a)(TheCRCParameterCheck, "CAMP: Frame %d: Castle %s(%d) ::initiatePack(aka:DIE) called by %s", field00376C70<int>(TheGameLogic, 0x3c), name, id, caller);
	}
}
