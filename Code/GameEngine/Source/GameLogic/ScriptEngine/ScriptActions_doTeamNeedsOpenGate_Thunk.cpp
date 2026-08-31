// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

class ScriptActionParameter
{
	friend class ScriptActions;

private:
	unsigned char m_unmodelled[0x10];
	AsciiString m_string;
};

class Object
{
public:
	Int getId() const { return m_id; }

private:
	unsigned char m_unmodelled[0x74];
	Int m_id;
};

class Team
{
public:
	void bfmeSetNeedsGateOpenRaw(Int, Int);
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
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *resolveUnit(ScriptActionParameter *) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamNeedsOpenGate(
		ScriptActionParameter *, ScriptActionParameter *, Bool);
};

// ?doTeamNeedsOpenGate@ScriptActions@@IAEXPAVScriptActionParameter@@0_N@Z
void ScriptActions::doTeamNeedsOpenGate(ScriptActionParameter *teamParameter,
	ScriptActionParameter *gateParameter, Bool needsOpen)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParameter->m_string, false);
	if (!team) {
		return;
	}

	Object *gate = TheScriptEngine->resolveUnit(gateParameter);
	if (!gate) {
		return;
	}

	team->bfmeSetNeedsGateOpenRaw(gate->getId(), *(const Int *)&needsOpen);
}
