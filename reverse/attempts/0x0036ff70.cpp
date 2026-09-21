// ?query@Rva0036ff70Module@@QAEHP6AHPAX0@Z0@Z
// partial score=0.83 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME5: Rva0036ff70Module::query, retail 0x0036FF70, 524 bytes.
//
// Identity is already proven by the landed caller
// Rva00370730CastleMemberInterface::run (Rva00370730CastleMemberState.cpp):
// it forward-declares this exact class/method pair and pins the mangled
// name ?query@Rva0036ff70Module@@QAEHP6AHPAX0@Z0@Z (reverse/symbols.csv).
// query() takes a cdecl (candidate, context) -> int callback and asks it
// about six candidates: a raw this+0x08 field, the result of a virtual
// call through a sub-object at this+0x20 (slot 6, only when non-null),
// then every id in four id ranges (this+0xdc/0xe0, this+0xb8/0xbc,
// this+0xd0/0xd4, this+0xc4/0xc8, in that order) resolved through
// GameLogic::findObjectByID. The first range goes through the real
// out-of-line GameLogic::findObjectByID (a genuine CALL in retail); the
// remaining three are resolved through the compiler's own inlined copy of
// the same hash_map::find body -- matching the established
// findObjectByIDInline idiom from Gen00370200Process.cpp. The callback
// short-circuits query() with a false return the moment it returns 0;
// completing every candidate returns true.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
// stlport
#include <hash_map>

class Object;
typedef int ObjectID;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	__forceinline Object *findObjectByIDInline(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objectMap.find(id);
		if (it == m_objectMap.end())
			return 0;

		return (*it).second;
	}

private:
	unsigned char m_pad00[0xb0];
	ObjectPtrHash m_objectMap;
};

extern GameLogic *TheBfmeGameLogic;

typedef int Int;

// Retail 0x0036ff70 iterates module-owned records and invokes the callback;
// its two explicit arguments are callback then callback context and it
// returns the callback-chain result. Declared identically to the forward
// declaration in Rva00370730CastleMemberState.cpp so both TUs mangle to the
// same symbol.
typedef Int (__cdecl *Rva0036ff70Callback)(void *, void *);

// Only vtable slot 6 (offset 0x18) of the sub-object at this+0x20 is
// exercised by the retail body; the other slots are unproven placeholders
// that keep the vtable shape wide enough to reach slot 6.
class Rva0036ff70Sub
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void *vf6();
};

class Rva0036ff70Module
{
public:
	Int query(Rva0036ff70Callback callback, void *context);

private:
	// Field offsets are proven by the retail body's own operand
	// displacements; no wider layout is claimed.
	unsigned char m_pad00[0x08];
public:
	void *m_field08;
private:
	unsigned char m_pad0c[0x20 - 0x0c];
public:
	Rva0036ff70Sub m_sub20;
private:
	unsigned char m_pad9c[0xb8 - (0x20 + sizeof(Rva0036ff70Sub))];
public:
	ObjectID *m_range1Begin;	// +0xb8
	ObjectID *m_range1End;		// +0xbc
private:
	unsigned char m_padc0[0xc4 - 0xc0];
public:
	ObjectID *m_range2Begin;	// +0xc4
	ObjectID *m_range2End;		// +0xc8
private:
	unsigned char m_padcc[0xd0 - 0xcc];
public:
	ObjectID *m_range3Begin;	// +0xd0
	ObjectID *m_range3End;		// +0xd4
private:
	unsigned char m_paddc[0xdc - 0xd8];
public:
	ObjectID *m_range0Begin;	// +0xdc
	ObjectID *m_range0End;		// +0xe0
};

Int Rva0036ff70Module::query(Rva0036ff70Callback callback, void *context)
{
	GameLogic *logic;
	ObjectID *it;

	if (!callback(m_field08, context))
		return 0;

	void *subResult = m_sub20.vf6();
	if (subResult != 0)
	{
		if (!callback(subResult, context))
			return 0;
	}

	{
		it = m_range0Begin;
		logic = TheBfmeGameLogic;
		if (it != m_range0End)
		{
			do
			{
				Object *value = logic->findObjectByID(*it);
				if (value != 0)
				{
					if (!callback(value, context))
						return 0;
					logic = TheBfmeGameLogic;
				}
				++it;
			} while (it != m_range0End);
		}
	}

	{
		it = m_range1Begin;
		if (it != m_range1End)
		{
			do
			{
				Object *value = logic->findObjectByIDInline(*it);
				if (value != 0)
				{
					if (!callback(value, context))
						return 0;
					logic = TheBfmeGameLogic;
				}
				++it;
			} while (it != m_range1End);
		}
	}

	{
		it = m_range3Begin;
		if (it != m_range3End)
		{
			do
			{
				Object *value = logic->findObjectByIDInline(*it);
				if (value != 0)
				{
					if (!callback(value, context))
						return 0;
					logic = TheBfmeGameLogic;
				}
				++it;
			} while (it != m_range3End);
		}
	}

	{
		it = m_range2Begin;
		if (it != m_range2End)
		{
			do
			{
				Object *value = logic->findObjectByIDInline(*it);
				if (value != 0)
				{
					if (!callback(value, context))
						return 0;
					logic = TheBfmeGameLogic;
				}
				++it;
			} while (it != m_range2End);
		}
	}

	return 1;
}
