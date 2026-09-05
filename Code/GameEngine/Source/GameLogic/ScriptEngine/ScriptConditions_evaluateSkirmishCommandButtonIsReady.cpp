// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// ZH evaluateSkirmishCommandButtonIsReady with BFME command-type 0x16 fallthrough.
// DLINK PMF layout from ObjectDlinkPmf.h; m_specialPower at +0x34.

#include "StringInline.h"

typedef bool Bool;

enum SpecialPowerType
{
	SPECIAL_INVALID = 0
};

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(void); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
	Bool hasSpecialPower(SpecialPowerType type) const;
};

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class Overridable
{
public:
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

private:
	void *m_vptr;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerType getSpecialPowerType() const { return m_type; }

private:
	unsigned char m_beforeType[0x14 - 0xC];
	SpecialPowerType m_type;
};

class UpgradeTemplate;

class CommandButton
{
public:
	int getCommandType() const { return m_command; }
	const UpgradeTemplate *getUpgradeTemplate() const { return m_upgradeTemplate; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	Bool isReady(const Object *sourceObj) const;

private:
	unsigned char m_beforeCommand[0x10];
	int m_command;
	unsigned char m_beforeUpgrade[0x20 - 0x14];
	const UpgradeTemplate *m_upgradeTemplate;
	unsigned char m_beforeSpecialPower[0x34 - 0x24];
	const SpecialPowerTemplate *m_specialPower;
};

class Team
{
	void *m_unmodelled0;
	void *m_unmodelled1;
	void *m_unmodelled2;
	Object *m_head;
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &);
};

extern ScriptEngine *TheScriptEngine;
extern ControlBar *TheControlBar;

class ScriptConditions
{
protected:
	virtual Bool evaluateSkirmishCommandButtonIsReady(Parameter *, Parameter *, Parameter *, Bool);
};

// ?evaluateSkirmishCommandButtonIsReady@ScriptConditions@@MAE_NPAVParameter@@00_N@Z
Bool ScriptConditions::evaluateSkirmishCommandButtonIsReady(
	Parameter *, Parameter *pTeamParm, Parameter *pCommandButtonParm, Bool allReady)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	const CommandButton *commandButton =
		TheControlBar->findCommandButton(pCommandButtonParm->getString());
	if (!commandButton)
		return false;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance()) {
		Object *pObj = iter.cur();
		if (commandButton->getSpecialPowerTemplate()) {
			const SpecialPowerTemplate *sp = commandButton->getSpecialPowerTemplate();
			const Overridable *finalOverride = sp->friend_getFinalOverride();
			if (!pObj->hasSpecialPower(
				((const SpecialPowerTemplate *)finalOverride)->getSpecialPowerType()))
				continue;
		} else if (!commandButton->getUpgradeTemplate()) {
			if (commandButton->getCommandType() != 0x16)
				continue;
		}

		if (commandButton->isReady(pObj)) {
			if (!allReady)
				return true;
		} else {
			if (allReady)
				return false;
		}
	}

	return allReady;
}
