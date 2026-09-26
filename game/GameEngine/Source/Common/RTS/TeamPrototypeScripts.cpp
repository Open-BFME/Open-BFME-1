// cl: /DNDEBUG /MD /EHsc /Gy /O2 /Ob1
// The two TeamPrototype bodies that deal in Scripts, adjacent in the image:
//
//   0x000ED6F0  getGenericScript            236B
//   0x000ED850  evaluateProductionCondition 216B
//
// Both reach TheScriptEngine's findScriptByName at vtable slot 53 and both
// duplicate() what it hands back, so they share the whole ScriptEngine vtable
// and the Script class -- each written out once per file before this.
//
// The real find is TeamPrototype itself. The two files agree on everything they
// both name -- vptr, factory, owning player, id, name at +0x10 -- and then each
// pads blindly over exactly the region the other describes:
//
//   getGenericScript             pads +0x14..+0x27, names +0x28..+0x12B
//   evaluateProductionCondition  names +0x14..+0x27, pads +0x28..+0x1E7
//
// So between them they cover the object continuously from +0x00 to +0x1F0 with
// no gap and no contradiction, and neither file could see that it was padding
// over the other's fields. Written once, the production-condition state at
// +0x14..+0x24 sits directly in front of the generic-script table at
// +0x28..+0x12B, and the two AsciiStrings at the end -- the production
// condition at +0x1E8 and the generic script names at +0x1F0 -- are eight bytes
// apart rather than two unrelated addresses.
//
// UnicodeString is the one model that had to be chosen rather than merged.
// getGenericScript needs the real shape, privately derived from StringBase<char>
// with a destructor, because its body builds a temporary and the temp cleanup at
// 0x00887940 is StringBase<char>::releaseBuffer. evaluateProductionCondition
// declared it as a bare void * because it only ever takes the member's address.
// The derived shape serves both; the opaque one could not have.
//
// The production-condition file built without /EHsc; it byte-verifies unchanged
// with it, probed before merging.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum GameDifficulty
{
	DIFFICULTY_EASY = 0,
	DIFFICULTY_NORMAL = 1,
	DIFFICULTY_HARD = 2
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// Temp cleanup at 0x00887940 is StringBase<char>::releaseBuffer (export
// ?releaseBuffer@?$StringBase@D@@AAEXXZ), not UnicodeString::~ (0x005EEA0).
template <typename T>
class StringBase
{
protected:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	void *m_data;

private:
	void releaseBuffer();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<char>
{
public:
	UnicodeString() {}
	~UnicodeString() {}
	void set(const UnicodeString &other);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class Script
{
public:
	Script *duplicate(void) const;					// ILT 0x0004589F

	UnsignedInt getFrameToEvaluate(void) const { return m_frameToEvaluateAt; }
	void setFrameToEvaluate(UnsignedInt frame) { m_frameToEvaluateAt = frame; }
	Int getDelayEvalSeconds(void) const { return m_delayEvaluationSeconds; }
	Bool isEasy(void) const { return m_easy; }
	Bool isNormal(void) const { return m_normal; }
	Bool isHard(void) const { return m_hard; }

private:
	void *m_vptr;							// +0x00
	char m_pad04[0x0C];						// +0x04
	Int m_delayEvaluationSeconds;					// +0x10
	char m_pad14[0x04];						// +0x14
	Bool m_easy;							// +0x18
	Bool m_normal;							// +0x19
	Bool m_hard;							// +0x1A
	char m_pad1b[0x0D];						// +0x1B
	UnsignedInt m_frameToEvaluateAt;				// +0x28
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	GameDifficulty getPlayerDifficulty(void) const;			// ILT 0x000217D8
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }

private:
	char m_pad[0x3C];
	UnsignedInt m_frame;						// +0x3C
};

class Team;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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

enum { MAX_GENERIC_SCRIPTS = 32 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	Script *getGenericScript(Int scriptToRetrieve, UnicodeString *outName);
	Bool evaluateProductionCondition(void);

private:
	void *m_vptr;							// +0x00
	void *m_factory;						// +0x04
	Player *m_owningPlayer;						// +0x08
	int m_id;							// +0x0C
	AsciiString m_name;						// +0x10
	int m_flags;							// +0x14
	int m_pad18;							// +0x18
	Bool m_productionConditionAlwaysFalse;				// +0x1C
	char m_pad1d[3];
	UnicodeString m_scriptNameOut;					// +0x20
	Script *m_productionConditionScript;				// +0x24
	Bool m_retrievedGenericScripts;					// +0x28
	char m_pad29[3];
	Script *m_genericScriptsToRun[MAX_GENERIC_SCRIPTS];		// +0x2C
	UnicodeString m_genericScriptNames[MAX_GENERIC_SCRIPTS];	// +0xAC
	char m_pad12c[0x1E8 - 0x12C];					// +0x12C -> +0x1E8
	AsciiString m_productionCondition;				// +0x1E8
	char m_pad1ec[0x1F0 - 0x1EC];					// +0x1EC -> +0x1F0
	AsciiString m_teamGenericScripts[MAX_GENERIC_SCRIPTS];		// +0x1F0
};

// ?getGenericScript@TeamPrototype@@QAEPAVScript@@HPAVUnicodeString@@@Z
Script *TeamPrototype::getGenericScript(Int scriptToRetrieve, UnicodeString *outName)
{
	if (!m_retrievedGenericScripts)
	{
		m_retrievedGenericScripts = true;
		for (Int i = 0; i < MAX_GENERIC_SCRIPTS; ++i)
		{
			Script *scriptToSave = 0;
			UnicodeString tmp;
			if (!m_teamGenericScripts[i].isEmpty())
			{
				Script *tmpScript = TheScriptEngine->findScriptByName(&m_name, &m_teamGenericScripts[i], &tmp);
				if (tmpScript)
					scriptToSave = tmpScript->duplicate();
			}
			m_genericScriptsToRun[i] = scriptToSave;
			if (scriptToSave)
				m_genericScriptNames[i].set(tmp);
		}
	}

	Script *script = m_genericScriptsToRun[scriptToRetrieve];
	if (script && outName)
		outName->set(m_genericScriptNames[scriptToRetrieve]);
	return script;
}

// ?evaluateProductionCondition@TeamPrototype@@QAE_NXZ
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
