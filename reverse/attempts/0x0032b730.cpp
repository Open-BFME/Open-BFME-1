// ?evaluateNamedSelected@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@@Z
// partial score=0.5 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	Int compare(const StringBase<T> &other) const;

private:
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	Int compare(const AsciiString &other) const
	{
		return StringBase<char>::compare(other);
	}
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

// The condition caches its answer in two fields retail reads at +0x44 and +0x48.
class Condition
{
public:
	unsigned char m_beforeCache[0x44];
	Int m_cachedAnswer;
	Int m_cachedSelectionCount;
};

class ThingTemplate
{
public:
	const AsciiString &getName(void) const { return m_name; }

private:
	unsigned char m_beforeName[0x84];
	AsciiString m_name;
};

class Drawable
{
public:
	const ThingTemplate *getTemplate(void) const { return m_template; }

private:
	unsigned char m_beforeTemplate[0xfc];
	const ThingTemplate *m_template;
};

struct BfmeSelectionNode
{
	BfmeSelectionNode *m_next;
	BfmeSelectionNode *m_prev;
	Drawable *m_drawable;
};

struct BfmeSelectionList
{
	BfmeSelectionNode *m_sentinel;
};

class GameEngine
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
	virtual Bool isMultiplayerSession(void) = 0;
};

class InGameUI
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
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual Int getSelectionCount(void) = 0;
	virtual const BfmeSelectionList *getAllSelectedDrawables(void) = 0;
};

extern GameEngine *TheGameEngine;
extern InGameUI *TheInGameUI;

class ScriptConditions
{
protected:
	Bool evaluateNamedSelected(Condition *condition, Parameter *unit);
};

// ?evaluateNamedSelected@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@@Z
Bool ScriptConditions::evaluateNamedSelected(Condition *condition,
	Parameter *unit)
{
	if (TheGameEngine->isMultiplayerSession())
		return false;

	Bool stale;
	if (condition->m_cachedAnswer == 0)
		stale = true;
	else
		stale = false;
	Int count = TheInGameUI->getSelectionCount();
	if (count == condition->m_cachedSelectionCount && !stale)
	{
		if (condition->m_cachedAnswer == -1)
			return false;
		if (condition->m_cachedAnswer == 1)
			return true;
	}

	Bool selected = false;
	const BfmeSelectionList *list = TheInGameUI->getAllSelectedDrawables();
	const BfmeSelectionNode *sentinel = list->m_sentinel;
	const BfmeSelectionNode *node = sentinel->m_next;
	while (node != sentinel)
	{
		if (node->m_drawable->getTemplate()->getName().compare(
				unit->getString()) == 0)
		{
			selected = true;
			break;
		}
		node = node->m_next;
	}

	condition->m_cachedAnswer = selected ? 1 : -1;
	condition->m_cachedSelectionCount = TheInGameUI->getSelectionCount();
	return selected;
}
