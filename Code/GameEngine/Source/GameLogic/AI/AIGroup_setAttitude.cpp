// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::setAttitude, retail 0x00150FE0, 50 bytes.
//
// The reference's body unchanged: hand the attitude to every member's AI.
//
// getAIUpdateInterface() is not a call here -- the AI sits at Object+0x204 and
// is read straight out of the member, guarded, and used as the `this` of the
// setter; the setter itself is reached directly, not through a vtable.
//
// m_memberList is at this+0x04, the same STLport sentinel walk the other
// AIGroup loops measured, payload at node+0x08.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

enum AttitudeType {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void setAttitude(AttitudeType tude);			// ILT 0x00030553
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface(void) { return m_ai; }

private:
	unsigned char m_unmodelled_000[0x204];
	AIUpdateInterface *m_ai;				// +0x204
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void setAttitude(AttitudeType tude);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

void AIGroup::setAttitude( AttitudeType tude )
{
	_STL::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		AIUpdateInterface *ai = (*i)->getAIUpdateInterface();
		if (ai)
		{
			ai->setAttitude( tude );
		}
	}
}
