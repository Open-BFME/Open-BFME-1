// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?createGroup@AI@@QAEPAVAIGroup@@XZ: Code/GameEngine/Source/GameLogic/AI/ai.cpp
// Open-BFME: AI::createGroup, retail 0x0014C630, 127 bytes.
//
// The reference's two lines. sizeof(AIGroup) is the 0x40 pushed to the global
// operator new, and the group list is at this+0x10 -- the same list
// AIGroup::remove's destroyGroup unlinks from.
//
// The element copy inlines here where AerialPathfinder_addNoFlyZone.cpp's does
// not: a pointer is small enough for MSVC to expand _Construct into the
// null-checked store, an eight-byte struct is not.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	AIGroup(void);						// ILT 0x0002A031

private:
	char m_bfme_body[0x40];					// sizeof(AIGroup), the pushed size
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup(void);

private:
	char m_slice_pad[0x10];					// retail this+0x00 .. +0x0F, untouched
	_STL::list<AIGroup *> m_groupList;			// this+0x10
};

AIGroup *AI::createGroup( void )
{
	// create a new instance
	AIGroup *group = new AIGroup;

	// add it to the list
	m_groupList.push_back( group );

	return group;
}
