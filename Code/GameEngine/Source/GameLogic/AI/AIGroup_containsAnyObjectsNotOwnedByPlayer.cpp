// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::containsAnyObjectsNotOwnedByPlayer, retail 0x001509C0,
// 57 bytes.
//
// The reference's body unchanged: the first member whose controlling player is
// not the one asked about answers the question.
//
// m_memberList is at this+0x04, the same STLport sentinel walk the other
// AIGroup loops measured, payload at node+0x08; the player argument is loop
// invariant and lives in ebx.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;		// ILT 0x00020824
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Bool containsAnyObjectsNotOwnedByPlayer(const Player *ownerPlayer);

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

Bool AIGroup::containsAnyObjectsNotOwnedByPlayer( const Player *ownerPlayer )
{
	_STL::list<Object *>::iterator it;

	for (it = m_memberList.begin(); it != m_memberList.end(); ++it) {
		Object *obj = (*it);
		if (!obj) {
			continue;
		}

		if (obj->getControllingPlayer() != ownerPlayer) {
			return true;
		}
	}

	return false;
}
