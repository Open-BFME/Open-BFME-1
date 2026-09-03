// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

typedef void (__cdecl *BfmeObjectVisitor)(Object *, void *);

class BfmeInnerIterable
{
public:
	Int bfmeVisit(BfmeObjectVisitor, void *);
};

extern void __cdecl bfmeTeamSetExperiencePointsVisitor(Object *, void *);
extern void __cdecl bfmeTeamRefreshExperienceVisitor(Object *, void *);

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
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamSetExperiencePoints(const AsciiString &, Int);
};

// ?doTeamSetExperiencePoints@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doTeamSetExperiencePoints(
	const AsciiString &teamName, Int points)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	BfmeInnerIterable *members = (BfmeInnerIterable *)team;
	members->bfmeVisit(bfmeTeamSetExperiencePointsVisitor, (void *)points);
	members->bfmeVisit(bfmeTeamRefreshExperienceVisitor, 0);
}
