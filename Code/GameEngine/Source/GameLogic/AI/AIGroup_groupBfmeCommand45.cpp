// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: AIGroup wrapper for AICMD 0x45, retail 0x00156A90, 103 bytes.
// First member only (not the full walk used by groupBfmeCommand44). Both the
// member and the target pass through bfmeResolveMeleeTarget before the
// command. Callee is the AICMD 0x45 builder at 0x00152C20 (ILT 0x00019628).
//
// Member list is the STLport list at +4 (same as AIGroup::remove). empty()
// is `_M_data->_M_next == _M_data` -> `cmp [eax], eax`.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

enum CommandSourceType { BFME_COMMAND_SOURCE_PLAYER };

class Object;

class AICommandInterface
{
public:
	void aiBfmeCommand45(Object *target, CommandSourceType cmdSource);
};

class BfmeGroupAI
{
public:
	char m_bfmeHead[0x20];
	AICommandInterface m_bfmeCommands;
};

class Object
{
public:
	Object *bfmeResolveMeleeTarget(int unused);

	char m_bfmeHead[0x204];
	BfmeGroupAI *m_bfmeAI;
};

class AIGroup
{
public:
	void groupBfmeCommand45(Object *target, CommandSourceType cmdSource);

private:
	char m_bfmeHead[0x04];
	_STL::list<Object *> m_memberList;
};

void AIGroup::groupBfmeCommand45(Object *target, CommandSourceType cmdSource)
{
	if (m_memberList.empty())
		return;

	Object *obj = m_memberList.front();
	Object *tgt = target;
	if (obj == 0)
		return;
	if (tgt == 0)
		return;

	if (obj->bfmeResolveMeleeTarget(0))
		obj = obj->bfmeResolveMeleeTarget(0);
	if (tgt->bfmeResolveMeleeTarget(0))
		tgt = tgt->bfmeResolveMeleeTarget(0);

	BfmeGroupAI *ai = obj->m_bfmeAI;
	if (ai)
		ai->m_bfmeCommands.aiBfmeCommand45(tgt, cmdSource);
}
