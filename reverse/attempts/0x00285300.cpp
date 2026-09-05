// ?update@Rva00285300@@QAE_NXZ
// partial score=0.45 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: address-derived body, retail 0x00285300 size 313.
// IDENTITY NOT RECOVERED: class/member names are address- or role-derived.
// this-0xc is a moduleData pointer, this-8 the owning Object (same base shape
// as the sibling body at 0x002995E0); the two sibling thunk calls at the end
// take (char*)this-0x10, same pattern. The body gates a "formation refresh"
// action behind several BfmeHorde interfaces reached off Object fields at
// +0x204 (BfmeHordeMember*), +0x1f8 (BfmeHordeOwnerInterface*, resolved via
// bfmeResolveMeleeTarget when present) and +0x214 (BfmeHordeOwner*, which is
// also usable as Object* for bfmeResolveMeleeTarget, so it is declared here
// as inheriting Object). The tail (0x0105-0x0125) makes two virtual calls
// (vtable+0x68, then vtable+0x8c on the pointer that call returns, passing an
// uninitialized local and moduleData->field0C) whose real interface/struct
// shape is NOT recovered; modeled here as minimal virtual stubs so the body
// compiles, flagged as the likely remaining byte-diff source.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

class BFMESelectionStatusBits
{
public:
	Bool test(UnsignedInt bit) const;
};

class BfmeHordeMember
{
public:
	Bool bfmeBlocksFormationRefresh();

	unsigned char m_pad_000[0x31e];
	unsigned char m_flag31E;
};

class BfmeHordeOwnerInterface
{
public:
	Bool bfmeBlocksFormationRefresh();
};

class Object;

// Second virtual call's receiver: reached from the first call's return value.
class Rva00285300CallbackTail
{
public:
	unsigned char m_pad_000[0x8c];
	virtual Bool notify(void *outParam, Int radius);
};

// First virtual call's receiver: reached from Object::m_field1FC.
class Rva00285300Callback
{
public:
	unsigned char m_pad_000[0x68];
	virtual Rva00285300CallbackTail *getTail();
};

class BfmeHordeOwner;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BFMESelectionStatusBits
{
public:
	Object *bfmeResolveMeleeTarget(Int flags);

	unsigned char m_pad_000[0x94];
	UnsignedInt m_status94;
	unsigned char m_pad_098[0x118 - 0x98];
	UnsignedInt m_status118;
	unsigned char m_pad_11C[0x1f8 - 0x11c];
	BfmeHordeOwnerInterface *m_field1F8;
	Rva00285300Callback *m_field1FC;
	unsigned char m_pad_200[0x204 - 0x200];
	BfmeHordeMember *m_field204;
	unsigned char m_pad_208[0x214 - 0x208];
	BfmeHordeOwner *m_field214;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad_000[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class BfmeHordeOwner : public Object
{
public:
	UnsignedInt bfmeGetFormationRefreshValue();
};

struct Rva00285300ModuleData
{
	unsigned char m_pad_000[0xc];
	UnsignedInt m_field0C;
	unsigned char m_pad_010[0x38 - 0x10];
	unsigned char m_field38;
	unsigned char m_pad_039[8 - 1];
	Bool m_field8;
};

class Rva00285300Base
{
public:
	void j0003767d();
	void j000454d0(Object *object);
};

class Rva00285300
{
public:
	Bool update();
};

// ?update@Rva00285300@@QAE_NXZ
Bool Rva00285300::update()
{
	Rva00285300ModuleData *moduleData = *(Rva00285300ModuleData **)((char *)this - 0xc);
	Object *object = *(Object **)((char *)this - 8);

	if (!object)
		return moduleData->m_field8;

	if (object->m_status118 & 0x10)
		return moduleData->m_field8;

	if (object->m_status94 & 0x20000000)
		return moduleData->m_field8;

	BfmeHordeMember *hordeMember = object->m_field204;
	if (hordeMember)
	{
		if (hordeMember->bfmeBlocksFormationRefresh())
			return true;
		if (hordeMember->m_flag31E)
			return true;
	}

	Object *meleeTarget = object->bfmeResolveMeleeTarget(0);
	BfmeHordeOwnerInterface *owner = meleeTarget ? meleeTarget->m_field1F8 : object->m_field1F8;
	if (owner)
	{
		if (owner->bfmeBlocksFormationRefresh())
			return true;
	}

	if (moduleData->m_field38)
	{
		((Rva00285300Base *)((char *)this - 0x10))->j0003767d();
		return moduleData->m_field8;
	}

	if (object->test(0x25))
		return true;
	if (object->test(0x3c))
		return true;

	if (object->m_field214)
	{
		UnsignedInt frame = TheBfmeGameLogic->m_frame;
		UnsignedInt refreshValue = object->m_field214->bfmeGetFormationRefreshValue();
		if (refreshValue > frame - moduleData->m_field0C)
			return true;
	}

	if (object->m_field214)
	{
		Object *melee1 = object->m_field214->bfmeResolveMeleeTarget(0);
		if (melee1)
		{
			Object *melee2 = object->m_field214->bfmeResolveMeleeTarget(0);
			Rva00285300CallbackTail *tail = melee2->m_field1FC->getTail();
			int localOut;
			if (tail->notify(&localOut, moduleData->m_field0C))
				return true;
		}
	}

	((Rva00285300Base *)((char *)this - 0x10))->j000454d0(object);
	return moduleData->m_field8;
}
