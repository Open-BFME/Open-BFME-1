// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::remove, retail 0x00151800, 104 bytes.
//
// Zero Hour's body line for line, and the retail frame confirms Zero Hour's
// member order as well: the member list at this+0x04 (so the pool object's
// vptr owns +0x00), m_memberListSize at +0x08, m_speed filling +0x0C and
// m_dirty at +0x10, which is the `mov byte ptr [esi+0x10], 1`.
//
// Everything but the three calls is inlined, so the shape is the evidence:
// std::find walks node->next from the header node comparing node+8, erase
// unlinks and hands the node back to the STLport node allocator with a size of
// 0x0C, and isEmpty() is m_memberList.empty() -- `cmp dword ptr [eax], eax` on
// the header node -- rather than a test of the count it just decremented.
//
// Compiled against the real STLport <list> and <algorithm> for the same reason
// GameLogicFindObjectByID.cpp compiles against the real <hash_map>: a
// hand-rolled replica gets the register assignment and the branch structure
// subtly wrong, and the container's own inlining is what the bytes are.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class AIGroup;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
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
	Bool remove(Object *obj);
	Bool isEmpty(void) { return m_memberList.empty(); }

private:
	virtual ~AIGroup();					// pool object vptr, this+0x00

	_STL::list<Object *> m_memberList;			// this+0x04
	UnsignedInt m_memberListSize;				// this+0x08
	Real m_speed;						// this+0x0C
	Bool m_dirty;						// this+0x10
};

Bool AIGroup::remove( Object *obj )
{
	_STL::list<Object *>::iterator i = _STL::find( m_memberList.begin(), m_memberList.end(), obj );

	// make sure object is actually in the group
	if (i == m_memberList.end())
		return false;

	// remove it
	m_memberList.erase( i );
	--m_memberListSize;

	// tell object to forget about group
	obj->leaveGroup();

	// list has changed, properties need recomputation
	m_dirty = true;

	// if the group is empty, no-one is using it any longer, so destroy it
	if (isEmpty()) {
		TheAI->destroyGroup( this );
		return true;
	}

	return false;
}
