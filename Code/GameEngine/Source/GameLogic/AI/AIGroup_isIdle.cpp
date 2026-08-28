// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::isIdle, retail 0x00151280, 73 bytes.
//
// The reference's body unchanged. getAIUpdateInterface() is a member read of
// Object+0x204, isIdle is vtable slot 96 (+0x180) on the AI, and
// isEffectivelyDead() is inline -- bit 0 of the byte at Object+0x344.
//
// The reference's `state = ai->isIdle() || obj->isEffectivelyDead(); if
// (!state) return false;' is why both tests continue the loop and only the pair
// failing leaves it; the trailing `return state' folds to true because that is
// all that can reach it.
//
// m_memberList is at this+0x04, the same STLport sentinel walk the other
// AIGroup loops measured, payload at node+0x08.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
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
	virtual Bool isIdle(void) const;			// vtable +0x180
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const AIUpdateInterface *getAIUpdateInterface(void) const { return m_ai; }
	Bool isEffectivelyDead(void) const { return (m_deadFlags & 1) != 0; }

private:
	unsigned char m_unmodelled_000[0x204];
	AIUpdateInterface *m_ai;				// +0x204
	unsigned char m_unmodelled_208[0x344 - 0x208];
	unsigned char m_deadFlags;				// +0x344, bit 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Bool isIdle(void) const;

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

Bool AIGroup::isIdle( void ) const
{
	Bool isIdle = true;
	_STL::list<Object *>::const_iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		Object *obj = *i;
		if (!obj) {
			continue;
		}

		const AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (!ai) {
			continue;
		}

		isIdle = ai->isIdle() || obj->isEffectivelyDead();
		if( !isIdle )
		{
			return false;
		}
	}

	return isIdle;
}
