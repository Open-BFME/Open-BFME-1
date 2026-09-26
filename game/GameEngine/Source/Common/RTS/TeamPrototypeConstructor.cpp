// ??0TeamPrototype@@QAE@PAVTeamFactory@@ABVAsciiString@@1PAVPlayer@@_NPAVDict@@H@Z
// Retail RVA0x000F3E40/367B; matched TeamFactory::initTeam caller proves identity.
// The native MAKE_DLINK_HEAD member constructor owns the zero store at+274;
// a raw pointer assignment loses the EH-state ordering and does not match.
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// Canonical BFME WWLib AsciiString. Its visible copy forwarder reaches the
// native StringBase<char> body at retail RVA 0x00887B60, while its inline
// default ctor and declared dtor supply the native EH-vector element ABI.
#include "ascii_string.h"

// TeamPrototypeDestructor.cpp proves that TeamPrototype's only base in this
// BFME layout is MemoryPoolObject, whose vptr occupies +0.
class MemoryPoolObject
{
protected:
	virtual ~MemoryPoolObject() {}
};

class Dict;
class TeamPrototype;
class Team;
class Script;

class TeamFactory
{
public:
	void addTeamPrototypeToList(TeamPrototype *team);
};

class Player
{
public:
	void addTeamToList(TeamPrototype *team);
};

// Existing TeamTemplateInfo constructor/destructor establish its 0x144-byte
// extent. Its out-of-line lifetime needs only an opaque layout here.
class TeamTemplateInfo
{
public:
	TeamTemplateInfo(Dict *dict);
	~TeamTemplateInfo();

private:
	unsigned char m_body[0x144];
};

class TeamPrototype : public MemoryPoolObject
{
protected:
	virtual ~TeamPrototype();

	// MAKE_DLINK_HEAD(Team, TeamInstanceList) from Team.h:675 expands to this
	// real one-word nested member.  Its inline ctor owns the +0x274 zero store.
	struct DLINKHEAD_TeamInstanceList
	{
		Team *m_head;
		DLINKHEAD_TeamInstanceList() : m_head(0) {}
		~DLINKHEAD_TeamInstanceList() {}
	};

public:
	TeamPrototype(TeamFactory *factory,
		const AsciiString &name,
		const AsciiString &ownerName,
		Player *owner,
		bool singleton,
		Dict *dict,
		int id);

private:
	TeamFactory *m_factory;                         // +0x04
	Player *m_owningPlayer;                         // +0x08
	int m_id;                                       // +0x0c
	AsciiString m_name;                             // +0x10
	AsciiString m_ownerName;                        // +0x14
	unsigned int m_flags;                           // +0x18
	unsigned char m_productionConditionAlwaysFalse; // +0x1c
	unsigned char m_pad1d[3];                       // +0x1d
	AsciiString m_productionConditionName;          // +0x20
	Script *m_productionConditionScript;            // +0x24
	unsigned char m_retrievedGenericScripts;        // +0x28
	unsigned char m_pad29[3];                       // +0x29
	Script *m_genericScriptsToRun[0x20];            // +0x2c
	AsciiString m_genericScriptNames[0x20];         // +0xac
	TeamTemplateInfo m_teamTemplate;                // +0x12c
	AsciiString m_attackPriorityName;               // +0x270
	DLINKHEAD_TeamInstanceList m_dlinkhead_TeamInstanceList; // +0x274
};

TeamPrototype::TeamPrototype(TeamFactory *factory,
	const AsciiString &name,
	const AsciiString &ownerName,
	Player *owner,
	bool singleton,
	Dict *dict,
	int id)
	: m_factory(factory),
	  m_owningPlayer(owner),
	  m_id(id),
	  m_name(name),
	  m_ownerName(ownerName),
	  m_flags(singleton ? 1u : 0u),
	  m_productionConditionAlwaysFalse(0),
	  m_pad1d(),
	  m_productionConditionName(),
	  m_productionConditionScript(0),
	  m_genericScriptNames(),
	  m_teamTemplate(dict),
	  m_attackPriorityName()
{
	if (m_factory)
		m_factory->addTeamPrototypeToList(this);
	if (m_owningPlayer)
		m_owningPlayer->addTeamToList(this);

	m_retrievedGenericScripts = 0;
	for (int i = 0; i < 0x20; ++i)
		m_genericScriptsToRun[i] = 0;
}
