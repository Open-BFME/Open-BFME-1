// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::groupSetEmoticon, retail 0x001514C0, 58 bytes.
//
// The reference's body unchanged: every member's drawable, when it has one, is
// given the emoticon and its duration.
//
// getDrawable() is a virtual in BFME -- vtable slot 10 (+0x28) on the object,
// not the inline member read the reference has -- and both arguments are loop
// invariant, which is why they sit in ebx and ebp for the whole walk.
//
// m_memberList is at this+0x04, the same STLport sentinel walk the other
// AIGroup loops measured, payload at node+0x08.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;

class AsciiString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void setEmoticon(const AsciiString &name, Int duration);	// ILT 0x00001A3C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
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
	virtual Drawable *getDrawable(void) const;		// vtable +0x28
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupSetEmoticon(const AsciiString &name, Int duration);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

void AIGroup::groupSetEmoticon( const AsciiString &name, Int duration )
{
	_STL::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		Object *object = (*i);
		Drawable *draw = object->getDrawable();
		if( draw )
		{
			draw->setEmoticon( name, duration );
		}
	}
}
