// ?rva00374420Update@Gen_00374420@@QAEXPAVRva003720F0Context@@0@Z
// partial score=0.25 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x00374420, 386B. No caller/vtable proves the enclosing class's own
// identity (a CastleBehavior-shaped neighbourhood, but this+0xa0 and
// this+0xc4/+0xc8 do not match the CastleBehavior::m_pendingObjectID layout
// already witnessed at +0x14 in CastleBehaviorIsPendingObjectUnavailable.cpp,
// so it is a different/larger class). Everything else is proven: the
// nameToKey("CastleMemberBehavior") static-key cache is the same idiom
// landed in CastleMemberBehaviorFind.cpp; the inline hash_map bucket walk
// over TheBfmeGameLogic's object registry matches GameLogicFindObjectByID.cpp
// byte-for-byte (same STLport hash_map<ObjectID,Object*> instantiation,
// node layout next@0/key@4/value@8); and the per-object action block calls
// bfmeSetVKP (clearAndSetModelConditionFlags@Object), a vtable-slot-0x28
// Drawable accessor, DrawableApplyPendingThunk::apply(false)
// (applyPendingModelConditionFlags@Drawable), Object::findModule with the
// cached key, and Rva003720F0Owner::update (the SAME real landed method as
// Rva003720F0AudioRefresh.cpp) forwarding this function's own two Context*
// parameters -- so the found CastleMemberBehavior module shares that
// update(Context*, Context*) entry point. Address-derived owner name kept
// per naming rules.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Bool;
typedef int ObjectID;

class BfmeX1011;
class BfmeLook1011
{
public:
	BfmeX1011 *bfmeFind1011(int id);
};
extern BfmeLook1011 *TheBfmeGameLogic;

class BfmeQ1060
{
public:
	int bfmeConv1060(int name);
};
extern BfmeQ1060 *TheNameKeyGenerator;

class BfmeItemDJ;
class BfmeThingDJ
{
public:
	BfmeItemDJ *bfmeFindDJ(int key);
};

class BfmeThingVKP
{
public:
	void bfmeSetVKP(int a, int b);
};

class DrawableApplyPendingThunk
{
public:
	void apply(bool pending);
};

class Rva003720F0Context;
class Rva003720F0Owner
{
public:
	void update(Rva003720F0Context *previous, Rva003720F0Context *current);
};

// vtable slot 0x28 (index 10) reaches a Drawable-fetch accessor.
class ObjectSlot10View
{
public:
	virtual void _pad0(void);
	virtual void _pad1(void);
	virtual void _pad2(void);
	virtual void _pad3(void);
	virtual void _pad4(void);
	virtual void _pad5(void);
	virtual void _pad6(void);
	virtual void _pad7(void);
	virtual void _pad8(void);
	virtual void _pad9(void);
	virtual DrawableApplyPendingThunk *getDrawableSlot10(void);
};

// Object as this function reaches it: the hash_map's mapped_type. Same slice
// as GameLogicFindObjectByID.cpp's ObjectPtrHash value; here it is also a
// polymorphic pointer used for the vtable-0x28 call and the pinned wrappers.
class Object
{
public:
	void *m_vtable;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	char m_slice_pad[0xB0];
	ObjectPtrHash m_objHash;	// bucket vector at this+0xB4
};

class Gen_00374420
{
public:
	void rva00374420Update(Rva003720F0Context *previous,
		Rva003720F0Context *current);

private:
	unsigned char m_pad00[0xa0];
	ObjectID m_singleObjectID;
	unsigned char m_pad0a4[0xc4 - 0xa4];
	ObjectID *m_arrayBegin;
	ObjectID *m_arrayEnd;
};

// ?d_00374420@@YAXXZ
void Gen_00374420::rva00374420Update(Rva003720F0Context *previous,
	Rva003720F0Context *current)
{
	static int key = TheNameKeyGenerator->bfmeConv1060(
		(int)"CastleMemberBehavior");

	Object *object = (Object *)TheBfmeGameLogic->bfmeFind1011(
		m_singleObjectID);
	if (object)
	{
		((BfmeThingVKP *)object)->bfmeSetVKP((int)previous, (int)current);

		DrawableApplyPendingThunk *drawable =
			reinterpret_cast<ObjectSlot10View *>(object)->getDrawableSlot10();
		drawable->apply(false);

		BfmeItemDJ *module = ((BfmeThingDJ *)object)->bfmeFindDJ(key);
		if (module)
			((Rva003720F0Owner *)module)->update(previous, current);
	}

	for (int i = 0; i < m_arrayEnd - m_arrayBegin; ++i)
	{
		ObjectID id = m_arrayBegin[i];
		if (id == 0)
			continue;

		ObjectPtrHash::iterator it =
			((GameLogic *)TheBfmeGameLogic)->m_objHash.find(id);
		if (it == ((GameLogic *)TheBfmeGameLogic)->m_objHash.end())
			continue;

		Object *found = (*it).second;
		((BfmeThingVKP *)found)->bfmeSetVKP((int)previous, (int)current);

		DrawableApplyPendingThunk *drawable2 =
			reinterpret_cast<ObjectSlot10View *>(found)->getDrawableSlot10();
		drawable2->apply(false);

		BfmeItemDJ *module2 = ((BfmeThingDJ *)found)->bfmeFindDJ(key);
		if (module2)
			((Rva003720F0Owner *)module2)->update(previous, current);
	}
}
