// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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

	void assignTeamReference(const AsciiString &, Team *);
	void copyTeamReference(const AsciiString &, AsciiString);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doSetTeamReference(
		const AsciiString &, ScriptActionParameter *, Bool);
};

// ?doSetTeamReference@ScriptActions@@IAEXABVAsciiString@@PAVScriptActionParameter@@_N@Z
void ScriptActions::doSetTeamReference(const AsciiString &referenceName,
	ScriptActionParameter *parameter, Bool referenceToReference)
{
	if (referenceToReference) {
		TheScriptEngine->copyTeamReference(referenceName, parameter->m_string);
		return;
	}

	Team *team = TheScriptEngine->getTeamNamed(parameter->m_string, false);
	TheScriptEngine->assignTeamReference(referenceName, team);
}
