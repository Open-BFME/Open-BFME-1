// ?query@Rva0036ff70Module@@QAEHP6AHPAX0@Z0@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0036FF70: the module Rva00370730CastleMemberInterface::run finds under
// "CastleBehavior" offers its object, its +0x20 slot-6 object and four id ranges
// to a callback. GameLogic::findObjectByID is one ordinary inline; VC7.1 keeps the first site a call.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
// stlport
#include <hash_map>

class Object;
typedef int ObjectID;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
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

// Same declaration as the forward one in Rva00370730CastleMemberState.cpp.
typedef Int (__cdecl *Rva0036ff70Callback)(void *, void *);

// Slot 6 (retail 0x002BA1E0 via ILT) is thiscall, no arguments, returns an Object.
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

// Typed slot view: a one-register __fastcall keeps ECX as the receiver and the table in EAX.
typedef void *(__fastcall *Rva0036ff70Slot6)(Rva0036ff70Sub *);
struct Rva0036ff70SubVtable
{
	void *slots[6];
	Rva0036ff70Slot6 slot6;
};

class Rva0036ff70Module
{
public:
	Int query(Rva0036ff70Callback callback, void *context);

private:
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
	// Start and finish words of four _STL::vector<ObjectID> members.
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
	if (!callback(m_field08, context))
		return 0;

	Rva0036ff70SubVtable *vtable = *(Rva0036ff70SubVtable **)&m_sub20;
	void *subResult = vtable->slot6(&m_sub20);
	if (subResult != 0 && !callback(subResult, context))
		return 0;

	ObjectID *it;
	for (it = m_range0Begin; it != m_range0End; ++it)
	{
		Object *value = TheBfmeGameLogic->findObjectByID(*it);
		if (value != 0 && !callback(value, context))
			return 0;
	}
	for (it = m_range1Begin; it != m_range1End; ++it)
	{
		Object *value = TheBfmeGameLogic->findObjectByID(*it);
		if (value != 0 && !callback(value, context))
			return 0;
	}
	for (it = m_range3Begin; it != m_range3End; ++it)
	{
		Object *value = TheBfmeGameLogic->findObjectByID(*it);
		if (value != 0 && !callback(value, context))
			return 0;
	}
	for (it = m_range2Begin; it != m_range2End; ++it)
	{
		Object *value = TheBfmeGameLogic->findObjectByID(*it);
		if (value != 0 && !callback(value, context))
			return 0;
	}

	return 1;
}
