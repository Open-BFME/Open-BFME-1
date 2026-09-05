// cl: /DNDEBUG /MD /Gy /O2 /Ob1
// TeamPrototype::evaluateProductionCondition at 0x000ED850 (216B).
// ZH twin: TeamPrototype::evaluateProductionCondition in Team.cpp.
// TheGameLogic 0x012F0898 +0x3C frame; TheScriptEngine 0x012F076C
// vcall +0x60 evaluateConditions, vcall +0xD4 findScriptByName.
// Callees: Player::getPlayerDifficulty ILT 0x000217D8, Script::duplicate ILT 0x0004589F.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum GameDifficulty
{
	DIFFICULTY_EASY = 0,
	DIFFICULTY_NORMAL = 1,
	DIFFICULTY_HARD = 2
};

class AsciiString
{
public:
	Bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)((const char *)m_data + 4) == 0;
	}

private:
	void *m_data;
};

class UnicodeString
{
	void *m_data;
};

class Script
{
public:
	Script *duplicate(void) const;

	UnsignedInt getFrameToEvaluate(void) const { return m_frameToEvaluateAt; }
	void setFrameToEvaluate(UnsignedInt frame) { m_frameToEvaluateAt = frame; }
	Int getDelayEvalSeconds(void) const { return m_delayEvaluationSeconds; }
	Bool isEasy(void) const { return m_easy; }
	Bool isNormal(void) const { return m_normal; }
	Bool isHard(void) const { return m_hard; }

private:
	void *m_vptr;					// +0x00
	char m_pad04[0x0C];				// +0x04
	Int m_delayEvaluationSeconds;			// +0x10
	char m_pad14[0x04];				// +0x14
	Bool m_easy;					// +0x18
	Bool m_normal;					// +0x19
	Bool m_hard;					// +0x1A
	char m_pad1b[0x0D];				// +0x1B
	UnsignedInt m_frameToEvaluateAt;		// +0x28
};

class Player
{
public:
	GameDifficulty getPlayerDifficulty(void) const;
};

class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }

private:
	char m_pad[0x3C];
	UnsignedInt m_frame;				// +0x3C
};

class Team;
class ScriptEngine
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual Bool evaluateConditions(UnicodeString *name, Script *pScript, Team *pThisTeam, Player *pPlayer);
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
	virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32();
	virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();
	virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
	virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
	virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
	virtual Script *findScriptByName(AsciiString *teamName, AsciiString *scriptName, UnicodeString *outName);
};

extern GameLogic *TheGameLogic;
extern ScriptEngine *TheScriptEngine;

class TeamPrototype
{
public:
	Bool evaluateProductionCondition(void);

private:
	void *m_vptr;					// +0x00
	void *m_factory;				// +0x04
	Player *m_owningPlayer;				// +0x08
	int m_id;					// +0x0C
	AsciiString m_name;				// +0x10
	int m_flags;					// +0x14
	int m_pad18;					// +0x18
	Bool m_productionConditionAlwaysFalse;		// +0x1C
	char m_pad1d[3];
	UnicodeString m_scriptNameOut;			// +0x20
	Script *m_productionConditionScript;		// +0x24
	char m_pad28[0x1C0];				// +0x28 -> +0x1E8
	AsciiString m_productionCondition;		// +0x1E8
};

Bool TeamPrototype::evaluateProductionCondition(void)
{
	if (m_productionConditionAlwaysFalse)
		return false;

	if (m_productionConditionScript)
	{
		if (TheGameLogic->getFrame() < m_productionConditionScript->getFrameToEvaluate())
			return false;
		Int delaySeconds = m_productionConditionScript->getDelayEvalSeconds();
		if (delaySeconds > 0)
			m_productionConditionScript->setFrameToEvaluate(TheGameLogic->getFrame() + delaySeconds * 5);
		Player *player = m_owningPlayer;
		return TheScriptEngine->evaluateConditions(&m_scriptNameOut, m_productionConditionScript, 0, player);
	}

	if (m_productionCondition.isEmpty())
	{
		m_productionConditionAlwaysFalse = true;
		return false;
	}

	Script *pScript = TheScriptEngine->findScriptByName(&m_name, &m_productionCondition, &m_scriptNameOut);
	if (pScript)
	{
		switch (m_owningPlayer->getPlayerDifficulty())
		{
		case DIFFICULTY_EASY:
			if (!pScript->isEasy())
			{
				m_productionConditionAlwaysFalse = true;
				return false;
			}
			break;
		case DIFFICULTY_NORMAL:
			if (!pScript->isNormal())
			{
				m_productionConditionAlwaysFalse = true;
				return false;
			}
			break;
		case DIFFICULTY_HARD:
			if (!pScript->isHard())
			{
				m_productionConditionAlwaysFalse = true;
				return false;
			}
			break;
		}

		m_productionConditionScript = pScript->duplicate();
		return TheScriptEngine->evaluateConditions(&m_scriptNameOut, m_productionConditionScript, 0, m_owningPlayer);
	}

	m_productionConditionAlwaysFalse = true;
	return false;
}
