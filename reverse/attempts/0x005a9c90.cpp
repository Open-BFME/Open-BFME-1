// ?rva005A9C90@@YGXPAVGameMessage@@@Z
// partial score=0.9 date=2026-09-21
// cl: /DNDEBUG /MD
// Retail 0x005A9C90, 159 bytes, __stdcall (ret 4, one stack arg: a
// GameMessage*). Reads the message's argument 0 as a pixel region, and when
// it is a single point (zero width/height) and TheInGameUI is not busy,
// picks an object under it via TheTacticalView, resolves it to either its
// AI-thing's "goal" sub-object (when live) or a GameLogic re-lookup by id,
// and finally asks TheControlBar::objectSelectPredicate on whichever object
// it landed on (falling back to the picked action object itself when
// testStatus(0x25) is false). No named caller ties an owner, so this keeps
// the address token.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct ICoord2D { Int x; Int y; };
struct IRegion2D { ICoord2D lo; ICoord2D hi; };

union GameMessageArgumentType
{
	Int integer;
	IRegion2D pixelRegion;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(Int argIndex) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	unsigned char m_pad[0x12b1];
	Bool m_busy;						///< +0x12b1
};

extern InGameUI *TheInGameUI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/View.h
class View
{
public:
	virtual void rva005A9C90ViewSlot0();
	virtual void rva005A9C90ViewSlot1();
	virtual void rva005A9C90ViewSlot2();
	virtual void rva005A9C90ViewSlot3();
	virtual void rva005A9C90ViewSlot4();
	virtual void rva005A9C90ViewSlot5();
	virtual void rva005A9C90ViewSlot6();
	virtual void rva005A9C90ViewSlot7();
	virtual void rva005A9C90ViewSlot8();
	virtual void *rva005A9C90ViewPick(const IRegion2D *region, Int a, Int b);	///< vtbl+0x24
};

extern View *TheTacticalView;

class BFMEActionObject
{
public:
	Bool testStatus(Int status) const;
};

// The object the click resolves to: +0x78 is its GameLogic lookup id and
// +0x214 is its AI-thing pointer (the same field the sibling helper at
// 0x005A9BD0 reads on the object hanging off its own +0xfc holder field).
struct Rva005A9C90Object
{
	unsigned char m_pad78[0x78];
	Int m_lookupId;						///< +0x78
	unsigned char m_pad214[0x214 - 0x7c];
	void *m_aiThing;					///< +0x214
};

struct Rva005A9C90PickResult
{
	unsigned char m_padFC[0xfc];
	Rva005A9C90Object *m_object;		///< +0xfc
};

// The AI-thing's own +0x1fc field, vtable+0x68 on whatever it points to.
struct Rva005A9C90AIThing
{
	unsigned char m_pad1fc[0x1fc];
	void *m_goal;						///< +0x1fc
};

class Rva005A9C90Goal
{
public:
	virtual void rva005A9C90GoalSlot0();
	virtual void rva005A9C90GoalSlot1();
	virtual void rva005A9C90GoalSlot2();
	virtual void rva005A9C90GoalSlot3();
	virtual void rva005A9C90GoalSlot4();
	virtual void rva005A9C90GoalSlot5();
	virtual void rva005A9C90GoalSlot6();
	virtual void rva005A9C90GoalSlot7();
	virtual void rva005A9C90GoalSlot8();
	virtual void rva005A9C90GoalSlot9();
	virtual void rva005A9C90GoalSlot10();
	virtual void rva005A9C90GoalSlot11();
	virtual void rva005A9C90GoalSlot12();
	virtual void rva005A9C90GoalSlot13();
	virtual void rva005A9C90GoalSlot14();
	virtual void rva005A9C90GoalSlot15();
	virtual void rva005A9C90GoalSlot16();
	virtual void rva005A9C90GoalSlot17();
	virtual void rva005A9C90GoalSlot18();
	virtual void rva005A9C90GoalSlot19();
	virtual void rva005A9C90GoalSlot20();
	virtual void rva005A9C90GoalSlot21();
	virtual void rva005A9C90GoalSlot22();
	virtual void rva005A9C90GoalSlot23();
	virtual void rva005A9C90GoalSlot24();
	virtual void rva005A9C90GoalSlot25();
	virtual Int rva005A9C90GoalCheck();		///< vtbl+0x68
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void *findObjectByID(Int id);
};

extern GameLogic *TheBfmeGameLogic;

class ControlBar
{
public:
	Int objectSelectPredicate(void *obj);
};

extern ControlBar *TheControlBar;

void __stdcall rva005A9C90(GameMessage *msg)
{
	if (TheInGameUI->m_busy)
		return;

	const GameMessageArgumentType *arg = msg->getArgument(0);
	if (arg->pixelRegion.hi.y - arg->pixelRegion.lo.y != 0)
		return;
	if (arg->pixelRegion.hi.x - arg->pixelRegion.lo.x != 0)
		return;

	Rva005A9C90PickResult *picked = (Rva005A9C90PickResult *)TheTacticalView->rva005A9C90ViewPick(&arg->pixelRegion, 0, 4);
	if (!picked)
		return;

	Rva005A9C90Object *object = picked->m_object;
	if (!object)
		return;

	if (((BFMEActionObject *)object)->testStatus(0x25))
	{
		void *aiThing = object->m_aiThing;
		if (!aiThing)
		{
			aiThing = TheBfmeGameLogic->findObjectByID(object->m_lookupId);
			if (!aiThing)
				return;
		}

		void *goal = ((Rva005A9C90AIThing *)aiThing)->m_goal;
		if (!goal)
			return;
		if (!((Rva005A9C90Goal *)goal)->rva005A9C90GoalCheck())
			return;

		object = (Rva005A9C90Object *)aiThing;
	}

	TheControlBar->objectSelectPredicate(object);
}
