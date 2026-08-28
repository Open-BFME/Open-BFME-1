// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::removeAnyObjectsNotOwnedByPlayer, retail 0x00151890,
// 74 bytes.
//
// The reference's body unchanged, including its bug: the null-member branch
// takes `continue` in a for loop whose increment is empty, so it never advances
// -- which is why the null test jumps straight at the loop's end test with the
// node register untouched.
//
// The iterator is advanced before the removal, once, for both exits; MSVC
// hoists the two ++it into the one `mov esi,[esi]` ahead of the branch.
//
// m_memberList is at this+0x04, the same STLport sentinel walk the other
// AIGroup loops measured, payload at node+0x08.
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
	Bool removeAnyObjectsNotOwnedByPlayer(const Player *ownerPlayer);
	Bool remove(Object *obj);				// ILT 0x000441A2

private:
	unsigned char m_unmodelled_000[4];			// this+0x00, untouched
	_STL::list<Object *> m_memberList;			// this+0x04
};

Bool AIGroup::removeAnyObjectsNotOwnedByPlayer( const Player *ownerPlayer )
{
	_STL::list<Object *>::iterator it;

	for (it = m_memberList.begin(); it != m_memberList.end(); /* empty */) {
		Object *obj = (*it);
		if (!obj) {
			continue;
		}

		if (obj->getControllingPlayer() != ownerPlayer) {
			// Advance the iterator first, its about to become invalid.
			++it;

			if (remove(obj)) {
				return true;
			}
			continue;
		}

		++it;
	}

	return false;
}
