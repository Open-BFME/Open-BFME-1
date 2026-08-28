// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::isMember, retail 0x00150990, 37 bytes.
//
// The reference's body unchanged: a find over the member list, then the
// end() comparison.  Both come out inline -- the walk stops on the first node
// whose payload is the object, and the answer is the setne against the list's
// own sentinel, reloaded from this+0x04 because the search clobbered it.
//
// m_memberList is at this+0x04, the same STLport sentinel walk the other
// AIGroup loops measured, payload at node+0x08.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

typedef bool Bool;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Bool isMember(Object *obj);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

Bool AIGroup::isMember( Object *obj )
{
	_STL::list<Object *>::iterator i = _STL::find( m_memberList.begin(), m_memberList.end(), obj );

	if (i == m_memberList.end())
		return false;

	return true;
}
