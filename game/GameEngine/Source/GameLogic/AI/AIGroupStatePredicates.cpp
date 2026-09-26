// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the three AIGroup predicates that answer a question about the
// group by asking every member.
//
//   ?isIdle@          0x00151280, 73 bytes
//   ?isBusy@          0x001512E0, 73 bytes
//   ?isGroupAiDead@   0x00151390, 50 bytes
//
// One loop, three verdicts, and the differences are one line each. isIdle
// returns false the moment a member is neither idle nor already dead; isBusy
// returns false the moment a member is not busy OR is dead -- note the operator
// flips with the sense, `||` in isIdle and `&&` in isBusy; isGroupAiDead never
// short-circuits, ANDing every member's dead flag to the end.
//
// The three carried two vtable models of AIUpdateInterface and two names for
// one byte of Object, and both are settled by putting them together.
//
// isIdle padded out 96 unused slots and put isIdle at vtable+0x180; isBusy
// padded out 99 and put isBusy at +0x18C. Those are the same vtable measured
// twice and they agree: slot 96 is isIdle, slot 99 is isBusy, and 97 and 98 are
// still unknown.
//
// Slot 96 has a second, independent derivation, and the convergence is worth
// more than the number. Here it is measured from OUTSIDE the class: AIGroup
// calls ai->isIdle() through an AIUpdateInterface pointer, and reproducing
// retail's dispatch needs 96 declared slots ahead of the method. In
// AIUpdateInterfacePrivateCommands.cpp it is measured from INSIDE: 
// AIUpdateInterface::privateMoveToPosition calls its own isIdle() through this,
// and that body needs isIdle to be the class's first own virtual behind a
// BfmeVirtualSlots<96> base. Different bodies, different call sites, one
// construction by padding and one by template base -- and the same 96.
//
// (AIUpdateInterfaceHelpers.cpp uses the same template trick for a different
// method and a different number: setLocomotorGoalNone at slot 122. It is not
// evidence about isIdle.)
//
// Object+0x344 is the dead flag. isIdle and isBusy called it m_deadFlags and
// tested `& 1` with no name for the bit; isGroupAiDead called it m_privateStatus
// and named the bit EFFECTIVELY_DEAD in an ObjectPrivateStatusBits enum. The
// named version is kept -- and the offset is worth recording because BFME grew
// Object past Zero Hour's layout, where the same field is at +0x297.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual void unusedSlot10();
	virtual void unusedSlot11();
	virtual void unusedSlot12();
	virtual void unusedSlot13();
	virtual void unusedSlot14();
	virtual void unusedSlot15();
	virtual void unusedSlot16();
	virtual void unusedSlot17();
	virtual void unusedSlot18();
	virtual void unusedSlot19();
	virtual void unusedSlot20();
	virtual void unusedSlot21();
	virtual void unusedSlot22();
	virtual void unusedSlot23();
	virtual void unusedSlot24();
	virtual void unusedSlot25();
	virtual void unusedSlot26();
	virtual void unusedSlot27();
	virtual void unusedSlot28();
	virtual void unusedSlot29();
	virtual void unusedSlot30();
	virtual void unusedSlot31();
	virtual void unusedSlot32();
	virtual void unusedSlot33();
	virtual void unusedSlot34();
	virtual void unusedSlot35();
	virtual void unusedSlot36();
	virtual void unusedSlot37();
	virtual void unusedSlot38();
	virtual void unusedSlot39();
	virtual void unusedSlot40();
	virtual void unusedSlot41();
	virtual void unusedSlot42();
	virtual void unusedSlot43();
	virtual void unusedSlot44();
	virtual void unusedSlot45();
	virtual void unusedSlot46();
	virtual void unusedSlot47();
	virtual void unusedSlot48();
	virtual void unusedSlot49();
	virtual void unusedSlot50();
	virtual void unusedSlot51();
	virtual void unusedSlot52();
	virtual void unusedSlot53();
	virtual void unusedSlot54();
	virtual void unusedSlot55();
	virtual void unusedSlot56();
	virtual void unusedSlot57();
	virtual void unusedSlot58();
	virtual void unusedSlot59();
	virtual void unusedSlot60();
	virtual void unusedSlot61();
	virtual void unusedSlot62();
	virtual void unusedSlot63();
	virtual void unusedSlot64();
	virtual void unusedSlot65();
	virtual void unusedSlot66();
	virtual void unusedSlot67();
	virtual void unusedSlot68();
	virtual void unusedSlot69();
	virtual void unusedSlot70();
	virtual void unusedSlot71();
	virtual void unusedSlot72();
	virtual void unusedSlot73();
	virtual void unusedSlot74();
	virtual void unusedSlot75();
	virtual void unusedSlot76();
	virtual void unusedSlot77();
	virtual void unusedSlot78();
	virtual void unusedSlot79();
	virtual void unusedSlot80();
	virtual void unusedSlot81();
	virtual void unusedSlot82();
	virtual void unusedSlot83();
	virtual void unusedSlot84();
	virtual void unusedSlot85();
	virtual void unusedSlot86();
	virtual void unusedSlot87();
	virtual void unusedSlot88();
	virtual void unusedSlot89();
	virtual void unusedSlot90();
	virtual void unusedSlot91();
	virtual void unusedSlot92();
	virtual void unusedSlot93();
	virtual void unusedSlot94();
	virtual void unusedSlot95();
	virtual Bool isIdle(void) const;			// vtable +0x180, slot 96
	virtual void unusedSlot97();
	virtual void unusedSlot98();
	virtual Bool isBusy(void) const;			// vtable +0x18C, slot 99
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const AIUpdateInterface *getAIUpdateInterface(void) const { return m_ai; }
	Bool isEffectivelyDead(void) const { return (m_privateStatus & EFFECTIVELY_DEAD) != 0; }

private:
	enum ObjectPrivateStatusBits { EFFECTIVELY_DEAD = (1 << 0) };

	unsigned char m_unmodelled_000[0x204];
	AIUpdateInterface *m_ai;				// +0x204
	unsigned char m_unmodelled_208[0x344 - 0x208];
	// BFME grew Object past ZH's layout: m_privateStatus sits at +0x344 here,
	// not +0x297.
	unsigned char m_privateStatus;				// +0x344
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Bool isIdle(void) const;
	Bool isBusy(void) const;
	Bool isGroupAiDead(void) const;

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

Bool AIGroup::isIdle( void ) const
{
	Bool isIdle = true;
	_STL::list<Object *>::const_iterator memberIterator;
	for( memberIterator = m_memberList.begin(); memberIterator != m_memberList.end(); ++memberIterator )
	{
		Object *memberObject = *memberIterator;
		if (!memberObject) {
			continue;
		}

		const AIUpdateInterface *memberAIUpdate = memberObject->getAIUpdateInterface();
		if (!memberAIUpdate) {
			continue;
		}

		isIdle = memberAIUpdate->isIdle() || memberObject->isEffectivelyDead();
		if( !isIdle )
		{
			return false;
		}
	}

	return isIdle;
}

Bool AIGroup::isBusy( void ) const
{
	Bool isBusy = true;
	_STL::list<Object *>::const_iterator memberIterator;
	for( memberIterator = m_memberList.begin(); memberIterator != m_memberList.end(); ++memberIterator )
	{
		Object *memberObject = *memberIterator;
		if (!memberObject) {
			continue;
		}

		const AIUpdateInterface *memberAIUpdate = memberObject->getAIUpdateInterface();
		if (!memberAIUpdate) {
			continue;
		}

		isBusy = memberAIUpdate->isBusy() && !memberObject->isEffectivelyDead();
		if( !isBusy )
		{
			return false;
		}
	}

	return isBusy;
}

// The only one of the three that never short-circuits.
Bool AIGroup::isGroupAiDead( void ) const
{
	Bool isDead = true;
	_STL::list<Object *>::const_iterator memberIterator;
	for( memberIterator = m_memberList.begin(); memberIterator != m_memberList.end(); ++memberIterator )
	{
		Object *memberObject = *memberIterator;
		if (!memberObject) {
			continue;
		}

		isDead = (isDead && memberObject->isEffectivelyDead());
	}

	return isDead;
}
