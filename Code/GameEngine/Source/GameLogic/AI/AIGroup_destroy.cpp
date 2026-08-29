// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: AI::destroyGroup, retail 0x0014BC40 (69 bytes).
//
// The retail body is the STLport list erase used by AI's group registry.  The
// list sentinel is at AI+0x10; its nodes hold the AIGroup pointer at +0x08.
// Keeping the ABI slice local preserves those BFME offsets without changing
// the shared AI header.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	virtual ~AIGroup(void) { }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	void destroyGroup(AIGroup *group);

private:
	char m_beforeGroupList[0x10];
	_STL::list<AIGroup *> m_groupList;
};

// ?destroyGroup@AI@@QAEXPAVAIGroup@@@Z
// ?destroyGroup@AI@@ present-unmatched
void AI::destroyGroup(AIGroup *group)
{
	_STL::list<AIGroup *>::iterator i = _STL::find(m_groupList.begin(), m_groupList.end(), group);
	if (i == m_groupList.end())
		return;

	m_groupList.erase(i);
	if (group != 0)
		delete group;
}
