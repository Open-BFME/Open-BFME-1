// RVA 0x0016F340: address-derived state predicate; the original owner identity
// is unproven. Calls at 0x0017DA80 and 0x0017DB10 use it as an int thiscall and
// stop on nonzero; this view follows the observed machine/owner and goal fields.
// ?checkRva0016F340@Rva0016F340StateView@@QAEHXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include <math.h>

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;

class StateMachine
{
public:
	virtual void halt();
	unsigned char m_pad04[0x0c];
	Object *m_owner;
	Object *getGoalObject();
};

class Rva0016F340ContainView
{
public:
#define SLOT(n) virtual void unused##n() = 0;
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
	SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25)
	virtual Rva0016F340ContainView *slot68() = 0;
	SLOT(27)
	virtual void slot70(Object *object, void *action, int flags) = 0;
	SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36)
	SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44)
	SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52)
	SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60)
	virtual void *slotF4() = 0;
#undef SLOT
};

class Rva0016F340ActionQuery
{
public:
#define SLOT(n) virtual void unused##n() = 0;
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
	SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
	SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
	SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87)
	SLOT(88) SLOT(89) SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95)
	SLOT(96) SLOT(97) SLOT(98) SLOT(99) SLOT(100) SLOT(101) SLOT(102) SLOT(103)
	SLOT(104) SLOT(105) SLOT(106) SLOT(107) SLOT(108) SLOT(109) SLOT(110) SLOT(111)
	SLOT(112) SLOT(113) SLOT(114) SLOT(115) SLOT(116) SLOT(117) SLOT(118) SLOT(119)
	SLOT(120) SLOT(121) SLOT(122) SLOT(123) SLOT(124) SLOT(125) SLOT(126) SLOT(127)
	virtual void *slot200() = 0;
#undef SLOT
};

class Drawable;
class Object
{
public:
#define OSLOT(n) virtual void objectSlot##n() = 0;
	OSLOT(0) OSLOT(1) OSLOT(2) OSLOT(3) OSLOT(4) OSLOT(5) OSLOT(6) OSLOT(7)
	OSLOT(8) OSLOT(9)
	virtual Drawable *getDrawable() const = 0;
	unsigned char m_pad04[0x34];
	Coord3D m_position;
	unsigned char m_pad44[0x1b8];
	Rva0016F340ContainView *m_contain;
	unsigned char m_pad200[4];
	Rva0016F340ActionQuery *m_actionQuery;
	unsigned char m_pad208[0x13c];
	unsigned char m_status;
#undef OSLOT
};

class Gen_000ED3B0
{
public:
	Real bfmeGapSq(const Gen_000ED3B0 *other) const;
};

class Rva0016F340StateView
{
public:
	virtual void slot00() = 0;
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	int checkRva0016F340();
};

class Rva0016F340ActionCallReceiver {};
typedef Bool (Rva0016F340ActionCallReceiver::*ActionCheck)(Object *, Object *, void *);
extern void d_000c4080();

template<class T> __forceinline T member(void (*function)())
{
	union { void (*raw)(); T method; } result;
	result.raw = function;
	return result.method;
}
#define CALL(T, object, function) (((Rva0016F340ActionCallReceiver *)(object))->*member<T>(function))

int Rva0016F340StateView::checkRva0016F340()
{
	register StateMachine *machine = m_machine;
	register Object *owner = machine->m_owner;
	Object *goal = machine->getGoalObject();
	if ((owner->m_status & 1) ||
		!goal ||
		(goal->m_status & 1) ||
		!CALL(ActionCheck, *(void **)0x012ED700, d_000c4080)(
			owner, goal, owner->m_actionQuery->slot200()))
		return -2;
	m_goalPosition = goal->m_position;

	if (((const Gen_000ED3B0 *)owner)->bfmeGapSq((const Gen_000ED3B0 *)goal) <
		*(const Real *)0x010977E8 &&
		fabs(goal->m_position.z - owner->m_position.z) < *(const Real *)0x01075C74)
	{
		Rva0016F340ContainView *related = 0;
		Object *other = goal;
		Rva0016F340ContainView *ownerContain = owner->m_contain;
		if (ownerContain)
			related = ownerContain->slot68();
		if (!related)
		{
			Rva0016F340ContainView *goalContain = goal->m_contain;
			if (!goalContain)
				return 0;
			related = goalContain->slot68();
			other = owner;
		}
		if (!related)
			return 0;

		void *containAction = related->slotF4();
		if (containAction)
			related->slot70(other, containAction, 0);
	}

	return 0;
}
