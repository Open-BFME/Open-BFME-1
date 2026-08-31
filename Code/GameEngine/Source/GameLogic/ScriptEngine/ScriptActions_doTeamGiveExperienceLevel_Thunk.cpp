// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

class AsciiString
{
private:
	char *m_text;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
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

class Object;
class Team;
class BfmeExperienceLevelDefinition;

typedef void (__cdecl *BfmeObjectVisitor)(Object *, void *);

class BfmeInnerIterable
{
public:
	Int bfmeVisit(BfmeObjectVisitor, void *);
};

extern void __cdecl bfmeTeamGiveExperienceLevelVisitor(Object *, void *);
extern void __cdecl bfmeTeamRefreshExperienceVisitor(Object *, void *);

class ExperienceLevelSystem
{
public:
	BfmeExperienceLevelDefinition *findLevel(const AsciiString &);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

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
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamGiveExperienceLevel(const AsciiString &, const AsciiString &);
};

// ?doTeamGiveExperienceLevel@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doTeamGiveExperienceLevel(
	const AsciiString &teamName, const AsciiString &levelName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	BfmeExperienceLevelDefinition *level =
		TheExperienceLevelSystem->findLevel(levelName);
	if (!level) {
		return;
	}

	BfmeInnerIterable *members = (BfmeInnerIterable *)team;
	members->bfmeVisit(bfmeTeamGiveExperienceLevelVisitor, level);
	members->bfmeVisit(bfmeTeamRefreshExperienceVisitor, 0);
}
