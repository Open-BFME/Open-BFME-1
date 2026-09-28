// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Retail 0x0016ED40: Rva000A19E0StateBase::onEnter.

enum StateReturnType
{
	STATE_FAILURE = -2
};

struct Rva0016ED40ObjectView;

class Rva000A19E0StateBase
{
public:
	virtual StateReturnType onEnter();
};

#define THING_TU_MEMBERS \
	Real bfmeRelativeAngleTo(const Coord3D *point) const; \
	void setOrientation(Real angle);
#include "../../Common/Thing/thing.h"
#undef THING_TU_MEMBERS

template <int N>
class Rva0016ED40Slots : public Rva0016ED40Slots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class Rva0016ED40Slots<0>
{
};

class Rva0016ED40AIUpdate : public Rva0016ED40Slots<130>
{
public:
	virtual void slot130() = 0;
};

class Rva0016ED40HandleView;

class Rva0016ED40ContainView : public Rva0016ED40Slots<26>
{
public:
	virtual Rva0016ED40HandleView *slot26() = 0;
};

template <int N>
class Rva0016ED40HandleSlots : public Rva0016ED40HandleSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class Rva0016ED40HandleSlots<0>
{
};

template <>
class Rva0016ED40HandleSlots<91> : public Rva0016ED40HandleSlots<90>
{
public:
	virtual void slot(char (*)[91]) = 0;
	virtual void setGoal(Rva0016ED40ObjectView *) = 0;
};

template <>
class Rva0016ED40HandleSlots<92> : public Rva0016ED40HandleSlots<91>
{
public:
	virtual void setEnabled(int) = 0;
};

template <int N>
class Rva0016ED40HandleTailSlots : public Rva0016ED40HandleTailSlots<N - 1>
{
public:
	virtual void tail(char (*)[N]) = 0;
};

template <>
class Rva0016ED40HandleTailSlots<0> : public Rva0016ED40HandleSlots<92>
{
};

class Rva0016ED40HandleView : public Rva0016ED40HandleTailSlots<13>
{
public:
	virtual void finish() = 0;
};

class Rva0016ED40StateMachineView
{
public:
	char m_pad00[0x10];
	Rva0016ED40ObjectView *m_owner;
};

extern void j_0000e570();
typedef Rva0016ED40ObjectView *(__fastcall *Rva0016ED40GetGoalObject)(
	Rva0016ED40StateMachineView *machine);

StateReturnType Rva000A19E0StateBase::onEnter()
{
	Rva0016ED40StateMachineView *machine =
		*(Rva0016ED40StateMachineView **)((char *)this + 0x1c);
	Rva0016ED40ObjectView *owner = machine->m_owner;
	if (owner == 0)
		return STATE_FAILURE;

	Rva0016ED40ObjectView *goal =
		((Rva0016ED40GetGoalObject)j_0000e570)(machine);
	if (goal == 0)
		return STATE_FAILURE;

	Rva0016ED40AIUpdate *ai =
		*(Rva0016ED40AIUpdate **)((char *)owner + 0x204);
	if (ai == 0)
		return STATE_FAILURE;
	ai->slot130();

	Rva0016ED40ContainView *contain =
		*(Rva0016ED40ContainView **)((char *)owner + 0x1fc);
	if (contain != 0)
	{
		Rva0016ED40HandleView *handle = contain->slot26();
		if (handle != 0)
		{
			handle->setGoal(goal);
			handle->setEnabled(1);
			handle->finish();
			return (StateReturnType)0;
		}
	}

	Thing *thing = (Thing *)owner;
	Coord3D *goalPosition = (Coord3D *)((char *)goal + 0x38);
	thing->setOrientation(
		thing->bfmeRelativeAngleTo(goalPosition) +
		*(float *)((char *)owner + 0x44));
	return (StateReturnType)0;
}
