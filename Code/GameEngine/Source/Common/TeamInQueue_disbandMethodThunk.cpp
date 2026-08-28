// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_outofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// readable body of ?disband@TeamInQueue@@QAEXXZ: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	void *m_data;
public:
	AsciiString(const AsciiString &source);
	~AsciiString();
	void concat(const char *text, int length);
};

class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
	unsigned char m_pad[0x230];
public:
	Team *m_defaultTeam;
	Team *getDefaultTeam() { return m_defaultTeam; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
	unsigned char m_pad[0x14];
public:
	AsciiString m_name;
	unsigned int m_flags;
	Player *getControllingPlayer() const;
	const AsciiString &getName() const { return m_name; }
	Bool getIsSingleton() const { return (m_flags & 1) != 0; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	virtual ~Team();
	TeamPrototype *m_proto;
	TeamPrototype *getPrototype() { return m_proto; }
	void transferUnitsTo(Team *newTeam);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class TeamInQueue
{
	unsigned char m_pad[0x1c];
public:
	Team *m_team;
	void disband();
};

void TeamInQueue::disband()
{
	Team *newTeam = m_team->getPrototype()->getControllingPlayer()->getDefaultTeam();
	AsciiString teamName = m_team->getPrototype()->getName();
	teamName.concat(" - team disbanded, build time expired.", 38);
	TheScriptEngine->AppendDebugMessage(teamName, false);
	if (m_team != newTeam)
	{
		m_team->transferUnitsTo(newTeam);
		if (!m_team->getPrototype()->getIsSingleton())
			delete m_team;
		m_team = 0;
	}
}
