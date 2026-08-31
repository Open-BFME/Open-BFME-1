// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef float Real;

class AIGroup;
class Team;

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

class AI
{
public:
	AIGroup *createGroup();
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *);
};

class AIGroup
{
public:
	void groupSetEmoticon(const AsciiString &, Int);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

class ScriptActions
{
protected:
	void doTeamEmoticon(const AsciiString &, const AsciiString &, Real);
};

// ?doTeamEmoticon@ScriptActions@@IAEXABVAsciiString@@0M@Z
void ScriptActions::doTeamEmoticon(
	const AsciiString &teamName, const AsciiString &emoticonName, Real duration)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team) {
		return;
	}

	AIGroup *group = TheAI->createGroup();
	if (!group) {
		return;
	}

	team->getTeamAsAIGroup(group);
	Int frames = (Int)(duration * 30.0f);
	group->groupSetEmoticon(emoticonName, frames);
}
