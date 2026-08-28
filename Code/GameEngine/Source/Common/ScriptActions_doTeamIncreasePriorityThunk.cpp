// cl: /DNDEBUG /MD /EHsc
// readable body of ?doTeamIncreasePriority@ScriptActions@@IAEXABVAsciiString@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

typedef bool Bool;
typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	unsigned char m_header[8];
	char m_text[1];
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	StringBase(const char *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	~AsciiString();

	void __cdecl format(AsciiString format, ...);
	const char *str() const
	{
		static const char TheNullChr = 0;
		return m_data ? m_data->m_text : &TheNullChr;
	}

private:
	AsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
struct TeamTemplateInfo
{
	Int m_productionPriority;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	void increaseAIPriorityForSuccess() const;
	const TeamTemplateInfo *getTemplateInfo() const { return &m_teamTemplate; }

private:
	unsigned char m_unreconstructed[0x1C8];
	TeamTemplateInfo m_teamTemplate;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	virtual ~Team();
	const TeamPrototype *getPrototype() const { return m_proto; }

private:
	TeamPrototype *m_proto;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual Team *getTeamNamed(AsciiString, Bool = false) = 0;

	void AppendDebugMessage(const AsciiString &, Bool);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamIncreasePriority(const AsciiString &);
};

// ?doTeamIncreasePriority@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doTeamIncreasePriority(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName);
	if (!team)
		return;

	const TeamPrototype *teamPrototype = team->getPrototype();
	if (!teamPrototype)
		return;

	teamPrototype->increaseAIPriorityForSuccess();

	AsciiString message;
	message.format("Team '%s' priority increased to %d for success.", teamName.str(),
		teamPrototype->getTemplateInfo()->m_productionPriority);
	TheScriptEngine->AppendDebugMessage(message, false);
}
