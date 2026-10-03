// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva002DF120
{
public:
	unsigned char test(void *first, void *second);
};

class Object;
class Weapon;
class BfmeX1004;
class BfmeItemMD;
class BfmeX1004
{
public:
#define RVA002DCDA0_SLOT(number) virtual BfmeX1004 *slot##number() = 0;
	RVA002DCDA0_SLOT(00)
	RVA002DCDA0_SLOT(01)
	RVA002DCDA0_SLOT(02)
	RVA002DCDA0_SLOT(03)
	RVA002DCDA0_SLOT(04)
	RVA002DCDA0_SLOT(05)
	RVA002DCDA0_SLOT(06)
	RVA002DCDA0_SLOT(07)
	RVA002DCDA0_SLOT(08)
	RVA002DCDA0_SLOT(09)
	RVA002DCDA0_SLOT(10)
	RVA002DCDA0_SLOT(11)
	RVA002DCDA0_SLOT(12)
	RVA002DCDA0_SLOT(13)
	RVA002DCDA0_SLOT(14)
	RVA002DCDA0_SLOT(15)
	RVA002DCDA0_SLOT(16)
	RVA002DCDA0_SLOT(17)
	RVA002DCDA0_SLOT(18)
	RVA002DCDA0_SLOT(19)
	virtual BfmeX1004 *slot20() = 0;
	RVA002DCDA0_SLOT(21)
	RVA002DCDA0_SLOT(22)
	RVA002DCDA0_SLOT(23)
	RVA002DCDA0_SLOT(24)
	RVA002DCDA0_SLOT(25)
	RVA002DCDA0_SLOT(26)
	RVA002DCDA0_SLOT(27)
	RVA002DCDA0_SLOT(28)
	RVA002DCDA0_SLOT(29)
	RVA002DCDA0_SLOT(30)
	RVA002DCDA0_SLOT(31)
	RVA002DCDA0_SLOT(32)
	RVA002DCDA0_SLOT(33)
	RVA002DCDA0_SLOT(34)
	RVA002DCDA0_SLOT(35)
	RVA002DCDA0_SLOT(36)
	RVA002DCDA0_SLOT(37)
	RVA002DCDA0_SLOT(38)
	RVA002DCDA0_SLOT(39)
	RVA002DCDA0_SLOT(40)
	RVA002DCDA0_SLOT(41)
	RVA002DCDA0_SLOT(42)
	RVA002DCDA0_SLOT(43)
	RVA002DCDA0_SLOT(44)
	RVA002DCDA0_SLOT(45)
	RVA002DCDA0_SLOT(46)
	RVA002DCDA0_SLOT(47)
	RVA002DCDA0_SLOT(48)
	RVA002DCDA0_SLOT(49)
	RVA002DCDA0_SLOT(50)
	RVA002DCDA0_SLOT(51)
	RVA002DCDA0_SLOT(52)
	RVA002DCDA0_SLOT(53)
	RVA002DCDA0_SLOT(54)
	RVA002DCDA0_SLOT(55)
	RVA002DCDA0_SLOT(56)
	RVA002DCDA0_SLOT(57)
	RVA002DCDA0_SLOT(58)
	RVA002DCDA0_SLOT(59)
	RVA002DCDA0_SLOT(60)
	RVA002DCDA0_SLOT(61)
	virtual BfmeX1004 *slot62(int value) = 0;
#undef RVA002DCDA0_SLOT
};

// Retail reaches both accessors through their incremental-link thunks:
// 0x0000D3B9 (-> ?j_0000d3b9@@YAXXZ, game/gen_small/thunks_005.cpp) and
// 0x00031A7F (-> ?j_00031a7f@@YAXXZ, game/gen_small/thunks_023.cpp).  A pin
// alone cannot bind a name no object defines, so the calls are spelled through
// the thunks themselves: the raw cdecl address is reinterpreted as a thiscall
// member pointer, which leaves `this` in ecx and emits the identical direct
// call to the same retail address.  Same idiom as
// game/GameEngine/Source/GameLogic/AI/Rva0017DA80.cpp; it needs one inliner,
// hence /Ob1 above (/Ob0 emits a real call to the template).
extern void j_0000d3b9(void);
extern void j_00031a7f(void);

class Rva002DCDA0ThunkReceiver
{
};

template <class Function>
__forceinline Function rva002dcda0Thunk(void (*raw)())
{
	union { void (*raw)(); Function member; } fn;
	fn.raw = raw;
	return fn.member;
}

#define RVA002DCDA0_THUNK_CALL(object, Function, raw) \
	(reinterpret_cast<Rva002DCDA0ThunkReceiver *>(object)->*rva002dcda0Thunk<Function>(raw))

class BfmeHolderMD
{
public:
	BfmeItemMD *bfmeFindMD(int slot);
};

class BfmeHold1004
{
public:
	BfmeX1004 *bfmeFind1004();
};

class BfmeThingAIA
{
public:
	bool bfmeAskAIA(int kind);
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class Weapon
{
public:
	bool bfmeCanAffect(const Object *first, const Object *second) const;
};

class Rva002DCDA0ObjectId
{
private:
	unsigned char m_padding[8];

public:
	int m_id;
};

class Rva002DCDA0 : public Rva002DF120
{
public:
	unsigned char test(void *first, void *second);
};

// Retail VA 0x012F0898 is the pointer defined in GameLogic.cpp.
extern GameLogic *TheGameLogic;

unsigned char Rva002DCDA0::test(void *first, void *second)
{
	if (!Rva002DF120::test(first, second))
		return 0;

	Object *found = TheGameLogic->findObjectByID(
		((Rva002DCDA0ObjectId *)first)->m_id);
	if (found == 0 || *(void **)((unsigned char *)found + 0x1fc) == 0)
		return 1;

	typedef BfmeX1004 *(Rva002DCDA0ThunkReceiver::*Find1004)(void);
	BfmeX1004 *controller =
		RVA002DCDA0_THUNK_CALL(found, Find1004, j_0000d3b9)();
	if (controller == 0)
		return 1;
	if (((BfmeThingAIA *)found)->bfmeAskAIA(0x6d))
		controller = controller->slot20();
	else
		controller = controller->slot62(0xa3);
	if (controller == 0)
		return 1;
	typedef BfmeItemMD *(Rva002DCDA0ThunkReceiver::*FindMD)(int);
	if (RVA002DCDA0_THUNK_CALL(controller, FindMD, j_00031a7f)(0) == 0)
		return 1;
	return ((Weapon *)RVA002DCDA0_THUNK_CALL(controller, FindMD, j_00031a7f)(0))
		->bfmeCanAffect((Object *)found, (Object *)second);
}
