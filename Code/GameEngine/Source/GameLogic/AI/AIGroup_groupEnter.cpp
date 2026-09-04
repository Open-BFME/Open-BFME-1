// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// stlport
// Open-BFME: AIGroup::groupEnter, retail 0x00156440, 229 bytes.
//
// Named by ScriptActions::doTeamEnterNamed / doTeamGarrisonSpecificBuilding.
// ZH walks m_memberList in place; BFME snapshots the STLport list first because
// aiEnter can unlink members. Identity is the matched aiEnter callee
// (ILT 0x000442A1 -> 0x000D89C0). Member walk is the same +0x204 AI /
// AI+0x20 command-interface layout as groupHunt.
//
// _STLP_NO_EXCEPTIONS drops the try in _M_create_node so it inlines and the
// callee-saved pushes stay in the entry block (ResourceGatheringManager_addSupply
// / Rva000D07A0ListPushBack). BFME_STLP_NODE_ALLOC keeps the 12-byte node
// alloc/free at 0x0082E540 / 0x0082E5F0.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

enum CommandSourceType { BFME_COMMAND_SOURCE_PLAYER };

class Object;

class AICommandInterface
{
public:
	void aiEnter(Object *obj, CommandSourceType cmdSource);
};

class BfmeGroupAI
{
public:
	char m_bfmeHead[0x20];
	AICommandInterface m_bfmeCommands;			// +0x20
};

class BfmeGroupMember
{
public:
	char m_bfmeHead[0x204];
	BfmeGroupAI *m_bfmeAI;					// +0x204
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupEnter(Object *obj, CommandSourceType cmdSource);

private:
	char m_bfmeHead[0x04];
	_STL::list<BfmeGroupMember *> m_memberList;		// +0x04
};

void AIGroup::groupEnter(Object *obj, CommandSourceType cmdSource)
{
	_STL::list<BfmeGroupMember *> snapshot;
	// Re-read end() each trip so `this` stays live in ebx and retail's
	// `cmp edi, [ebx+4]` form comes out.
	for (_STL::list<BfmeGroupMember *>::iterator src = m_memberList.begin();
			src != m_memberList.end();
			++src)
		snapshot.push_back(*src);

	for (_STL::list<BfmeGroupMember *>::iterator it = snapshot.begin();
			it != snapshot.end();
			++it)
	{
		BfmeGroupAI *ai = (*it)->m_bfmeAI;
		if (ai)
			ai->m_bfmeCommands.aiEnter(obj, cmdSource);
	}
}
