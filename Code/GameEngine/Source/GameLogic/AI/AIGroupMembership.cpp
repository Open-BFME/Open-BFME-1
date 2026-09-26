// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the four AIGroup members that ask or change who is in the group.
//
//   ?isMember@                            0x00150990,  37 bytes
//   ?containsAnyObjectsNotOwnedByPlayer@  0x001509C0,  57 bytes
//   ?remove@                              0x00151800, 104 bytes
//   ?removeAnyObjectsNotOwnedByPlayer@    0x00151890,  74 bytes
//
// Two pairs, and the pairing is the point. isMember and containsAny only ask --
// one by _STL::find over the member list, one by walking it and comparing each
// object's controlling player. remove and removeAny change it, and removeAny is
// written on top of remove: it walks, advances the iterator BEFORE calling
// remove because that call invalidates it, and stops the moment remove reports
// the group is gone.
//
// remove is the only one of the four that says what AIGroup actually looks like.
// The other three declare `unsigned char m_unmodelled_000[4]` at this+0x00 and
// stop at the member list; remove names the prefix -- a pool object's vptr at
// +0x00, the list at +0x04, the cached size at +0x08, the dirty flag at +0x10 --
// and it is the reason the four bodies agree the list is at +0x04 rather than at
// the start.
//
// Only two of those names are proved by a body in this TU: remove decrements
// +0x08 and sets +0x10. +0x0C it never touches, and the account it inherited
// called that slot m_speed. The constructor at 0x00151BF0
// (AIGroupAttackMoveOrder.cpp's flag family, so it cannot live here) settles it
// by writing every field: +0x0C is the ground path, and m_speed is at +0x24,
// past the group id at +0x14 and the seven formation floats. The name is
// corrected below; it is a void* either way, so the layout and these four bodies
// are unaffected.
//
// removeAny used to reach remove through a declaration carrying `ILT 0x000441A2`,
// because the definition was in another file. It is now a call inside one TU.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class Player;
class AIGroup;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;		// ILT 0x00020824
	void leaveGroup(void);					// ILT 0x0001F212
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	void destroyGroup(AIGroup *group);			// ILT 0x00015F69
};

extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Bool isMember(Object *member);
	Bool containsAnyObjectsNotOwnedByPlayer(const Player *ownerPlayer);
	Bool remove(Object *member);
	Bool removeAnyObjectsNotOwnedByPlayer(const Player *ownerPlayer);

	Bool isEmpty(void) { return m_memberList.empty(); }

private:
	virtual ~AIGroup();					// pool object vptr, this+0x00

	_STL::list<Object *> m_memberList;			// this+0x04
	UnsignedInt m_memberListSize;				// this+0x08
	void *m_groundPath;					// this+0x0C, not m_speed
	Bool m_dirty;						// this+0x10
};

Bool AIGroup::isMember( Object *member )
{
	_STL::list<Object *>::iterator memberIterator = _STL::find( m_memberList.begin(), m_memberList.end(), member );

	if (memberIterator == m_memberList.end())
		return false;

	return true;
}

Bool AIGroup::containsAnyObjectsNotOwnedByPlayer( const Player *ownerPlayer )
{
	_STL::list<Object *>::iterator memberIterator;

	for (memberIterator = m_memberList.begin(); memberIterator != m_memberList.end(); ++memberIterator) {
		Object *memberObject = (*memberIterator);
		if (!memberObject) {
			continue;
		}

		if (memberObject->getControllingPlayer() != ownerPlayer) {
			return true;
		}
	}

	return false;
}

Bool AIGroup::remove( Object *member )
{
	_STL::list<Object *>::iterator memberIterator = _STL::find( m_memberList.begin(), m_memberList.end(), member );

	// make sure object is actually in the group
	if (memberIterator == m_memberList.end())
		return false;

	// remove it
	m_memberList.erase( memberIterator );
	--m_memberListSize;

	// tell object to forget about group
	member->leaveGroup();

	// list has changed, properties need recomputation
	m_dirty = true;

	// if the group is empty, no-one is using it any longer, so destroy it
	if (isEmpty()) {
		TheAI->destroyGroup( this );
		return true;
	}

	return false;
}

Bool AIGroup::removeAnyObjectsNotOwnedByPlayer( const Player *ownerPlayer )
{
	_STL::list<Object *>::iterator memberIterator;

	for (memberIterator = m_memberList.begin(); memberIterator != m_memberList.end(); /* empty */) {
		Object *memberObject = (*memberIterator);
		if (!memberObject) {
			continue;
		}

		if (memberObject->getControllingPlayer() != ownerPlayer) {
			// Advance the iterator first, its about to become invalid.
			++memberIterator;

			if (remove(memberObject)) {
				return true;
			}
			continue;
		}

		++memberIterator;
	}

	return false;
}
