// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring8outofline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Clean C++ recovery of ScriptActions::updateTeamAttackPrioritySet.
//
// Retail identity evidence comes from the two executeAction callers through
// ScriptActions::executeAction, the pinned getAttackInfo and getName callees,
// and the Team member-list walk. Retail also exposes the BFME string header,
// the Team head at +0x0c, the Object AI pointer at +0x204, and the attack-info
// field at +0x70.

typedef int BfmeBool;

#include "Common/AsciiString.h"

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

class AttackPriorityInfo
{
public:
	AsciiString getName() const;
};

class BfmeObject;
typedef BfmeObject *(__fastcall *BfmeDlinkNext)(BfmeObject *);

struct BfmeDlinkPmf
{
	BfmeDlinkNext pfn;
	int delta;
	int vbindex;
};

extern void j_00001140(void);

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef BfmeDlinkPmf GetNextFunc;

private:
	OBJCLASS *m_cur;
	int m_padding;
	GetNextFunc m_getNextFunc;
	int m_tailPadding;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance(void)
	{
		OBJCLASS *object = m_cur;
		int vbindex = m_getNextFunc.vbindex;
		char *vbptr = *(char **)((char *)object + 0x68);
		char *adjusted = (char *)object + 0x68;
		adjusted += *(int *)(vbptr + vbindex);
		adjusted += m_getNextFunc.delta;
		m_cur = m_getNextFunc.pfn((OBJCLASS *)adjusted);
	}

	BfmeBool done(void) const { return m_cur == 0; }
	OBJCLASS *cur(void) const { return m_cur; }
};

class BfmeAIUpdateInterface
{
public:
	void setAttackInfo(const AttackPriorityInfo *info)
	{
		*(const AttackPriorityInfo **)((char *)this + 0x70) = info;
	}
};

class BfmeObject
{
public:
	BfmeAIUpdateInterface *getAIUpdateInterface(void)
	{
		return *(BfmeAIUpdateInterface **)((char *)this + 0x204);
	}
};

class Team
{
public:
	unsigned char m_beforeMembers[0x0c];
	BfmeObject *m_head;

	void setAttackPriorityName(AsciiString name);

	DLINK_ITERATOR<BfmeObject> iterate_TeamMemberList(void) const
	{
		BfmeDlinkPmf pmf = {(BfmeDlinkNext)j_00001140, -100, 0};
		return DLINK_ITERATOR<BfmeObject>(m_head, pmf);
	}
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, BfmeBool exact) = 0;
	const AttackPriorityInfo *getAttackInfo(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void updateTeamAttackPrioritySet(const AsciiString &teamName,
		const AsciiString &attackPrioritySet);
};

void ScriptActions::updateTeamAttackPrioritySet(const AsciiString &teamName,
	const AsciiString &attackPrioritySet)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	const AttackPriorityInfo *info =
		TheScriptEngine->getAttackInfo(attackPrioritySet);
	BfmeBool empty = info->getName().isEmpty();
	if (!empty)
		team->setAttackPriorityName(info->getName());

	for (DLINK_ITERATOR<BfmeObject> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		BfmeObject *object = iter.cur();
		BfmeAIUpdateInterface *ai = object->getAIUpdateInterface();
		if (ai)
			ai->setAttackInfo(info);
	}
}
