// ?applyNamed@ScriptEngine@@QAEXPAX0@Z
// partial score=0.2 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/scriptenginevtable /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include

#include "ascii_string.h"
inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

typedef bool Bool;
enum GameDifficulty
{
	RVA_DIFFICULTY_EASY,
	RVA_DIFFICULTY_NORMAL,
	RVA_DIFFICULTY_HARD
};

class Script;
class ScriptAction;
class Team;
class Player;

// The canonical shim places evaluateConditions at vtable slot 23.
class Rva00340F10EngineBase
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22();
	virtual Bool evaluateConditions(Script *script, Team *team, Player *player);
};

template <class T> class BFMERetailStringBase;

class BFMERetailAsciiString : public StringBase<char>
{
	friend class BFMERetailStringBase<char>;
private:
	void releaseBuffer();
};

template <class T> class BFMERetailStringBase
{
public:
	struct Data
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};
	BFMERetailStringBase(const BFMERetailStringBase<T> &other);
	~BFMERetailStringBase()
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}
	bool isEmpty() const { return !m_data || m_data->length == 0; }
	Data *m_data;
};

class Rva00338EF0Host
{
public:
	BFMERetailStringBase<char> copyStringAt30();
};

class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(AsciiString &name);
};

class Player
{
public:
	GameDifficulty getPlayerDifficulty() const;
};

class TeamPrototype
{
public:
	int countTeamInstances();
};

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &name,
		const AsciiString &ownerName);
};

class Gen_000c8a30
{
public:
	void *m();
};

AsciiString Rva00195FC0JoinPath(const AsciiString &left,
	const AsciiString &right);
void _appendMessage(const AsciiString &message, bool forcePause, bool playSound);

struct Rva00340F10ScriptFields
{
	char pad00[0x10];
	int delaySeconds;
	unsigned char isActive;
	char pad15;
	unsigned char isOneShot;
	unsigned char easy;
	unsigned char normal;
	unsigned char hard;
	char pad1b[5];
	ScriptAction *trueActions;
	ScriptAction *falseActions;
	unsigned int frameToEvaluateAt;
	char pad2c[4];
	AsciiString name;
	float conditionTime;
};

class ScriptEngine : public Rva00340F10EngineBase
{
public:
	void applyNamed(void *object, void *slot);

protected:
	void executeActions(ScriptAction *head);
};

void ScriptEngine::applyNamed(void *object, void *slot)
{
	Script *script = (Script *)object;
	AsciiString *scriptName = (AsciiString *)slot;
	Rva00340F10ScriptFields *fields = (Rva00340F10ScriptFields *)script;
	fields->conditionTime = 0.0f;
	if (!fields->isActive)
		return;

	int difficulty = *(int *)((char *)this + 0x17620);
	Player *player = *(Player **)((char *)this + 0x170ac);
	if (player)
		difficulty = player->getPlayerDifficulty();
	if (difficulty < 0 || difficulty > 2)
		return;
	if (difficulty == 0 && !fields->easy)
		return;
	if (difficulty == 1 && !fields->normal)
		return;
	if (difficulty == 2 && !fields->hard)
		return;

	unsigned int frame = *(unsigned int *)((char *)*(void **)0x012f0898 + 0x3c);
	if (frame < fields->frameToEvaluateAt)
		return;
	if (fields->delaySeconds > 0)
		fields->frameToEvaluateAt = frame + fields->delaySeconds * 5;

	Team **currentTeam = (Team **)((char *)this + 0x17094);
	Team *savedTeam = *currentTeam;

	{
		BFMERetailStringBase<char> name =
			((Rva00338EF0Host *)script)->copyStringAt30();
		if (name.isEmpty())
			return;
	}

	BFMERetailStringBase<char> rawName =
		((Rva00338EF0Host *)script)->copyStringAt30();
	AsciiString canonical =
		((BfmeScriptEngineSlashName *)this)->bfmeName(*(AsciiString *)&rawName);
	TeamPrototype *prototype =
		((TeamFactory *)*(void **)0x012ed810)->findTeamPrototype(canonical,
			*(const AsciiString *)scriptName);
	if (prototype && prototype->countTeamInstances() > 0)
	{
		Team *team = *(Team **)((char *)prototype + 0x274);
		while (team)
		{
			*currentTeam = team;
			if (evaluateConditions(script, team, 0))
			{
				if (fields->trueActions)
				{
					AsciiString message = Rva00195FC0JoinPath(
						*(AsciiString *)((char *)this + 0x17088), *scriptName);
					_appendMessage(message, true, false);
					executeActions(fields->trueActions);
				}
				if (fields->isOneShot)
					fields->isActive = 0;
			}
			else if (fields->falseActions)
			{
				AsciiString message = Rva00195FC0JoinPath(
					*(AsciiString *)((char *)this + 0x17088), *scriptName);
				_appendMessage(message, false, false);
				executeActions(fields->falseActions);
			}
		team = (Team *)((Gen_000c8a30 *)team)->m();
		}
	}
	else
	{
		*currentTeam = 0;
		if (evaluateConditions(script, 0, 0))
		{
			if (fields->trueActions)
			{
				AsciiString message = Rva00195FC0JoinPath(
					*(AsciiString *)((char *)this + 0x17088), *scriptName);
				_appendMessage(message, true, false);
				executeActions(fields->trueActions);
			}
			if (fields->isOneShot)
				fields->isActive = 0;
		}
		else if (fields->falseActions)
		{
			AsciiString message = Rva00195FC0JoinPath(
				*(AsciiString *)((char *)this + 0x17088), *scriptName);
			_appendMessage(message, false, false);
			executeActions(fields->falseActions);
		}
	}
	*currentTeam = savedTeam;
}
