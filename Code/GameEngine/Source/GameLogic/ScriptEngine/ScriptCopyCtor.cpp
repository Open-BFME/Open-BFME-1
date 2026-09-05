// cl: /DNDEBUG /MD /EHsc
// readable body of ??0Script@@QAE@ABV0@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp
// BFME Script copy constructor. Same pre-ZH layout as ScriptCtor.cpp: three
// AsciiString members, no action-comment field. Deep-copies the condition and
// action lists through OrCondition::duplicate / ScriptAction::duplicate and
// leaves m_nextScript plus the runtime fields empty.

class Xfer;

template <typename T>
struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();

protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class OrCondition
{
public:
	OrCondition *duplicate() const;
};

class ScriptAction
{
public:
	ScriptAction *duplicate() const;
};

class Script : public Snapshot
{
public:
	Script();
	Script(const Script &that);
	virtual ~Script();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	AsciiString m_scriptName;
	AsciiString m_comment;
	AsciiString m_conditionComment;
	int m_delayEvaluationSeconds;
	bool m_isActive;
	bool m_isOneShot;
	bool m_easy;
	bool m_isSubroutine;
	bool m_normal;
	bool m_hard;
	bool m_bfmeFlag;
	OrCondition *m_condition;
	ScriptAction *m_action;
	ScriptAction *m_actionFalse;
	Script *m_nextScript;
	bool m_hasWarnings;
	AsciiString m_conditionTeamName;
	float m_conditionTime;
	float m_curTime;
	int m_conditionExecutedCount;
};

Script::Script(const Script &that) :
	m_scriptName(that.m_scriptName),
	m_comment(that.m_comment),
	m_conditionComment(that.m_conditionComment),
	m_delayEvaluationSeconds(that.m_delayEvaluationSeconds),
	m_isActive(that.m_isActive),
	m_isOneShot(that.m_isOneShot),
	m_easy(that.m_easy),
	m_isSubroutine(that.m_isSubroutine),
	m_normal(that.m_normal),
	m_hard(that.m_hard),
	m_bfmeFlag(that.m_bfmeFlag),
	m_condition(that.m_condition ? that.m_condition->duplicate() : 0),
	m_action(that.m_action ? that.m_action->duplicate() : 0),
	m_actionFalse(that.m_actionFalse ? that.m_actionFalse->duplicate() : 0),
	m_nextScript(0),
	m_hasWarnings(false),
	m_conditionTime(0.0f),
	m_curTime(0.0f),
	m_conditionExecutedCount(0)
{
}
