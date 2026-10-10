// ?maintainNestedRiders@Rva0024CAE0Owner@@QAEXXZ
// Retail RVA 0x0024CAE0, reached as the first containment-maintenance call
// from HordeTransportContain::update.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport

#define __PLACEMENT_VEC_NEW_INLINE  // GameMemory.h provides array placement new.
#include <list>
#include "GameLogic/Damage.h"

class BfmeXCQE;

// Retail ILT 0x12E3B reaches 0x410BA0, an int-returning thiscall query.
// This caller consumes AL; retain that byte truncation at the call site.
class Gen_00410BA0
{
public:
	int isDrawableEffectivelyHidden(void) const;
};

// ILT 0x8337 reaches 0x411DD0: byte boolean argument, ret 4, no result.
class Gen_00411DD0
{
public:
	void bfmeSet(bool value);
};

class Rva0024CAE0Contain;

class Object
{
public:
	// Retail 0x24CBE0 calls ILT 0x14506 -> Object::kill at 0x1C30F0.
	void kill(DamageType damageType, DeathType deathType);

#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9)
#undef RVASLOT
	virtual BfmeXCQE *getState(void);

	char m_pad[0x1fc - 4];
	Rva0024CAE0Contain *m_contain;
};

class Rva0024CAE0Nested
{
public:
#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9) RVASLOT(10) RVASLOT(11)
	RVASLOT(12) RVASLOT(13) RVASLOT(14) RVASLOT(15) RVASLOT(16) RVASLOT(17)
	RVASLOT(18) RVASLOT(19) RVASLOT(20) RVASLOT(21) RVASLOT(22) RVASLOT(23)
	RVASLOT(24) RVASLOT(25) RVASLOT(26) RVASLOT(27) RVASLOT(28) RVASLOT(29)
	RVASLOT(30) RVASLOT(31) RVASLOT(32) RVASLOT(33) RVASLOT(34) RVASLOT(35)
	RVASLOT(36) RVASLOT(37) RVASLOT(38) RVASLOT(39)
#undef RVASLOT
	virtual void removeNested(Object *object);
};

class Rva0024CAE0Result
{
public:
#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9) RVASLOT(10) RVASLOT(11)
	RVASLOT(12) RVASLOT(13) RVASLOT(14) RVASLOT(15) RVASLOT(16) RVASLOT(17)
	RVASLOT(18) RVASLOT(19) RVASLOT(20) RVASLOT(21) RVASLOT(22) RVASLOT(23)
	RVASLOT(24) RVASLOT(25) RVASLOT(26) RVASLOT(27) RVASLOT(28) RVASLOT(29)
	RVASLOT(30) RVASLOT(31) RVASLOT(32) RVASLOT(33) RVASLOT(34) RVASLOT(35)
	RVASLOT(36) RVASLOT(37) RVASLOT(38) RVASLOT(39)
#undef RVASLOT
	virtual void removeNested(Object *object);

#define RVASLOT(n) virtual void slot##n();
	RVASLOT(41)
	RVASLOT(42) RVASLOT(43) RVASLOT(44) RVASLOT(45) RVASLOT(46) RVASLOT(47)
	RVASLOT(48) RVASLOT(49) RVASLOT(50) RVASLOT(51) RVASLOT(52) RVASLOT(53)
	RVASLOT(54) RVASLOT(55) RVASLOT(56) RVASLOT(57) RVASLOT(58)
#undef RVASLOT
	virtual _STL::list<Object *> *getNested(void);
};

class Rva0024CAE0Contain
{
public:
#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9) RVASLOT(10) RVASLOT(11)
	RVASLOT(12) RVASLOT(13) RVASLOT(14) RVASLOT(15) RVASLOT(16) RVASLOT(17)
	RVASLOT(18) RVASLOT(19) RVASLOT(20) RVASLOT(21) RVASLOT(22) RVASLOT(23)
	RVASLOT(24) RVASLOT(25)
#undef RVASLOT
	virtual Rva0024CAE0Result *getResult(void);
};

class Rva0024CAE0Notifier
{
public:
#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9) RVASLOT(10) RVASLOT(11)
	RVASLOT(12) RVASLOT(13) RVASLOT(14) RVASLOT(15) RVASLOT(16) RVASLOT(17)
	RVASLOT(18) RVASLOT(19) RVASLOT(20) RVASLOT(21) RVASLOT(22) RVASLOT(23)
	RVASLOT(24) RVASLOT(25) RVASLOT(26) RVASLOT(27) RVASLOT(28) RVASLOT(29)
	RVASLOT(30) RVASLOT(31) RVASLOT(32) RVASLOT(33) RVASLOT(34) RVASLOT(35)
#undef RVASLOT
	virtual void notifyRemoved(Object *object, int value);
};

class Rva0024CAE0Owner
{
public:
	void maintainNestedRiders(void);

private:
	char m_pad[0x20];
	Rva0024CAE0Notifier m_notifier;
	char m_pad024[0x14];
	_STL::list<Object *> m_objects;
};

void Rva0024CAE0Owner::maintainNestedRiders(void)
{
	_STL::list<Object *> nested;
	_STL::list<Object *> objects(m_objects);

	for (_STL::list<Object *>::iterator objectIt = objects.begin();
		 objectIt != objects.end(); ++objectIt)
	{
		Object *outer = *objectIt;
		if (outer == 0)
			continue;

		Rva0024CAE0Contain *contain = outer->m_contain;
		if (contain == 0)
			continue;

		Rva0024CAE0Result *result = contain->getResult();
		if (result == 0)
			continue;

		nested = *result->getNested();
		for (_STL::list<Object *>::iterator nestedIt = nested.begin();
			 nestedIt != nested.end(); ++nestedIt)
		{
			Object *object = *nestedIt;
			BfmeXCQE *state = object->getState();
			if (state == 0 || (char)((Gen_00410BA0 *)state)->isDrawableEffectivelyHidden())
			{
				result->removeNested(object);
				m_notifier.notifyRemoved(object, 0);
				object->kill((DamageType)8, (DeathType)0);
				if (state != 0)
					((Gen_00411DD0 *)state)->bfmeSet(true);
			}
		}
	}
}
