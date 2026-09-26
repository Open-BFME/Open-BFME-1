// cl: /DNDEBUG /MD /EHsc
// The two script-reference setters:
//
//   0x002F5A10  doSetUnitReference  SET_UNIT_REFERENCE
//   0x002F5B00  doSetTeamReference  SET_TEAM_REFERENCE
//
// Same two-armed shape: when the flag says the parameter names another
// reference, copy that reference under the new name and stop; otherwise resolve
// the parameter to a thing and assign it. Only the kind of thing differs, and
// the unit form has one extra step -- it binds the object back to the name so
// the object knows what it is called.

typedef bool Bool;

class Object;
class Team;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void bindUnitReference(Object *, const AsciiString &) = 0;

	// Not slots: the four reference-table entries the two actions share
	// between them.
	void assignUnitReference(const AsciiString &, Object *);
	void copyUnitReference(const AsciiString &, AsciiString);
	void assignTeamReference(const AsciiString &, Team *);
	void copyTeamReference(const AsciiString &, AsciiString);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doSetUnitReference(
		const AsciiString &, ScriptActionParameter *, Bool);
	void doSetTeamReference(
		const AsciiString &, ScriptActionParameter *, Bool);
};

// ?doSetUnitReference@ScriptActions@@IAEXABVAsciiString@@PAVScriptActionParameter@@_N@Z
void ScriptActions::doSetUnitReference(const AsciiString &referenceName,
	ScriptActionParameter *parameter, Bool referenceToReference)
{
	if (referenceToReference) {
		TheScriptEngine->copyUnitReference(referenceName, parameter->m_string);
		return;
	}

	Object *object = TheScriptEngine->resolveUnit(parameter);
	TheScriptEngine->assignUnitReference(referenceName, object);
	TheScriptEngine->bindUnitReference(object, referenceName);
}

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
