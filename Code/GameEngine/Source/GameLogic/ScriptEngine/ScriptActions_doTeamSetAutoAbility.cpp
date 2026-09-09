// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Clean C++ recovery of the BFME TEAM_SET_AUTO_ABILITY action.
//
// The retail 0x002F6EB0 body is the three-argument team action selected by
// script template 482.  It resolves the team at ScriptEngine vtable slot 17,
// resolves the command button once, then visits each team member's
// AutoAbilityBehavior only when that member's command set contains the button.
// The member-list and Object views below are TU-local BFME layout views; they
// preserve the retail +0x0c Team head and +0x68 Object link member without
// changing a shared header.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Object;
class Module {};

// The retail Object+0x68/vbtable walk is represented explicitly here.  This
// keeps the call ABI without asserting a C++ virtual-base hierarchy for Object.
class Object
{
public:
	Module *findModule(NameKeyType key) const;
	const AsciiString &getCommandSetString(void) const;
};

typedef Object *(__fastcall *BfmeDlinkNext)(Object *);
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

	Bool done(void) const
	{
		return m_cur == 0;
	}

	OBJCLASS *cur(void) const
	{
		return m_cur;
	}
};

class Team
{
public:
	unsigned char m_beforeMembers[0x0c];
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		BfmeDlinkPmf pmf = {(BfmeDlinkNext)j_00001140, -100, 0};
		return DLINK_ITERATOR<Object>(m_head, pmf);
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
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

class CommandButton
{
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
	const CommandSet *findCommandSet(const AsciiString &name);
};

class AutoAbilityBehavior
{
};

extern void j_0003c27c(void);

class AutoAbilityBehaviorApplyCall
{
public:
	void invoke(const CommandButton *commandButton, char enabled);
};

static __forceinline void callAutoAbilityApply(AutoAbilityBehavior *behavior,
	const CommandButton *commandButton, char enabled)
{
	typedef void (AutoAbilityBehaviorApplyCall::*CallABI)(
		const CommandButton *, char);
	union
	{
		void (*raw)(void);
		CallABI member;
	} fn;
	fn.raw = j_0003c27c;
	(reinterpret_cast<AutoAbilityBehaviorApplyCall *>(behavior)->*fn.member)(
		commandButton, enabled);
}

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern ScriptEngine *TheScriptEngine;
extern ControlBar *TheControlBar;
extern NameKeyGenerator *TheNameKeyGenerator;

class ScriptActions
{
protected:
	void doTeamSetAutoAbility(const AsciiString &teamName,
		const AsciiString &commandButtonName, Bool enabled);
};

// ?doTeamSetAutoAbility@ScriptActions@@IAEXABVAsciiString@@0_N@Z
void ScriptActions::doTeamSetAutoAbility(
	const AsciiString &teamName, const AsciiString &commandButtonName,
	Bool enabled)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	static NameKeyType autoAbilityBehaviorKey =
		TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
	const CommandButton *commandButton =
		TheControlBar->findCommandButton(commandButtonName);
	if (!commandButton ||
		!*(const unsigned char *)((const char *)commandButton + 0x158))
		return;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *object = iter.cur();
		AutoAbilityBehavior *behavior =
			(AutoAbilityBehavior *)object->findModule(autoAbilityBehaviorKey);
		if (behavior)
		{
			const CommandSet *commandSet =
				TheControlBar->findCommandSet(object->getCommandSetString());
			if (commandSet)
			{
				for (Int i = 0; i < 20; ++i)
				{
					if (commandButton == commandSet->getCommandButton(i))
					{
						callAutoAbilityApply(behavior, commandButton, enabled);
					}
				}
			}
		}
	}
}
