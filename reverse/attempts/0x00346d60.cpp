// ?evaluateAndProgressAllSequentialScripts@ScriptEngine@@IAEXXZ
// partial score=0.4 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Open-BFME: ScriptEngine::evaluateAndProgressAllSequentialScripts, retail
// 0x00346D60.  The BFME sequential-script record carries two string members
// before the Script pointer; the offsets below are taken from the retail
// append and assignment bodies, not from the Zero Hour header.

#include <vector>
#include "Common/LatchRestore.h"

template <typename T> class StringBase;

#define ASCIISTRING_H
template <typename T> class StringBase

{
	friend class AsciiString;

	private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &that);
	~StringBase();

	public:
	void concat(const T *text, int length);
	void set(const StringBase<T> &that);
	void clear();

	private:
	Header *m_data;
};

class AsciiString
	: private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &that)
	{
		StringBase<char>::set(that);
		return *this;
	}

	int getLength() const
	{
		return m_data ? m_data->length : 0;
	}

	const char *str() const
	{
		return m_data ? m_data->data : "";
	}

	__forceinline void concat(const AsciiString &that)
	{
		int length = that.m_data ? that.m_data->length : 0;
		const char *text = that.m_data ? that.m_data->data : "";
		StringBase<char>::concat(text, length);
	}

	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}

	void clear()
	{
		StringBase<char>::clear();
	}
};

class Parameter;
class Player;
class Team;
class Object;
class AIGroup;
class ScriptAction;

class Script
{
public:
	virtual void unused();

	private:
		char m_pad[0x1c];
		ScriptAction *m_action;

	public:
		ScriptAction *getAction() const { return m_action; }
};

class ScriptAction
{
public:
	virtual void unused();

	int m_actionType;
	int m_numParms;
	Parameter *m_parms[3];
	char m_pad18[0x24];
	ScriptAction *m_next;

	ScriptAction *getNext() { return m_next; }
	void setNextAction(ScriptAction *next) { m_next = next; }
	int getActionType() { return m_actionType; }
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_numParms)
			return m_parms[index];
		return 0;
	}

	AsciiString getUiText();
};

class SequentialScript
{
public:
	virtual ~SequentialScript();

	Team *m_teamToExecOn;
	int m_objectID;
	AsciiString m_latchedString;
	AsciiString m_displayString;
	Script *m_scriptToExecuteSequentially;
	int m_currentInstruction;
	int m_timesToLoop;
	int m_framesToWait;
	bool m_dontAdvanceInstruction;
	SequentialScript *m_nextScriptInSequence;

	void deleteInstance() { delete this; }
};

class TeamPrototype
{
public:
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x14);
	}
};

class Team
{
public:
	virtual void unused();

	Player *getControllingPlayer() const;
	void getTeamAsAIGroup(AIGroup *group);

	const AsciiString &getName() const
	{
		TeamPrototype *prototype = *(TeamPrototype **)((char *)this + 4);
		if (!prototype)
			return *(const AsciiString *)0x01336E50;
		return prototype->getName();
	}
};

class Object
{
public:
	Player *getControllingPlayer() const;

	AIGroup *unusedGroup() const;
	AIGroup *getAIGroup() const { return 0; }
	
	AIGroup *unusedGroup2() const;
	
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x84);
	}

	bool isEffectivelyDead() const
	{
		return (*(const unsigned char *)((const char *)this + 0x344) & 1) != 0;
	}

	class AIUpdateInterface *getAIUpdateInterface();
	const class AIUpdateInterface *getAIUpdateInterface() const;
};

class AIUpdateInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void unused62();
	virtual void unused63();
	virtual void unused64();
	virtual void unused65();
	virtual void unused66();
	virtual void unused67();
	virtual void unused68();
	virtual void unused69();
	virtual void unused70();
	virtual void unused71();
	virtual void unused72();
	virtual void unused73();
	virtual void unused74();
	virtual void unused75();
	virtual void unused76();
	virtual void unused77();
	virtual void unused78();
	virtual void unused79();
	virtual void unused80();
	virtual void unused81();
	virtual void unused82();
	virtual void unused83();
	virtual void unused84();
	virtual void unused85();
	virtual void unused86();
	virtual void unused87();
	virtual void unused88();
	virtual void unused89();
	virtual void unused90();
	virtual void unused91();
	virtual void unused92();
	virtual void unused93();
	virtual void unused94();
	virtual void unused95();
	virtual bool isIdle() const;

	bool isBusy() const
	{
		return *(const unsigned char *)((const char *)this + 0x338) != 0;
	}
};

AIUpdateInterface *Object::getAIUpdateInterface()
{
	return *(AIUpdateInterface **)((const char *)this + 0x204);
}

const AIUpdateInterface *Object::getAIUpdateInterface() const
{
	return *(const AIUpdateInterface **)((const char *)this + 0x204);
}

class AIGroup
{
public:
	bool isIdle() const;
	bool isGroupAiDead() const;
};

class Gen_00151340
{
public:
	bool bfmeAnyBusy() const;
};

class Player
{
public:
	Team *getTeam() const
	{
		return *(Team **)((const char *)this + 0x230);
	}
};

class GameLogic
{
public:
	Object *findObjectByID(int objectID);
};

class AI
{
public:
	AIGroup *createGroup();
};

class ScriptConditionsInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual bool evaluateSkirmishCommandButtonIsReady(Parameter *, Parameter *, Parameter *, bool);
	virtual bool evaluateTeamIsContained(Parameter *, bool);
	virtual bool evaluateBfmeSequentialWait(Parameter *);
};

#define TheGameLogic (*(GameLogic **)0x012F0898)
#define TheAI (*(AI **)0x012EF214)
#define TheScriptConditions (*(ScriptConditionsInterface **)0x012F06B0)

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	AsciiString m_name;
};

class Snapshot
{
public:
	virtual void unusedSnapshot();
};

class ScriptEngine : public SubsystemInterface, public Snapshot
{
public:
	void appendSequentialScript(SequentialScript *script);
	void executeActions(ScriptAction *action);
	void AppendDebugMessage(const AsciiString &message, bool forcePause);

protected:
	typedef std::vector<SequentialScript *> VecSequentialScriptPtr;
	typedef VecSequentialScriptPtr::iterator VecSequentialScriptPtrIt;

	VecSequentialScriptPtr m_sequentialScripts;
	int m_updateCount;
	char m_pad001c[0x17088 - 0x1c];
	AsciiString m_17088;
	char m_pad1708c[8];
	Team *m_conditionTeam;
	Object *m_conditionObject;
	char m_pad1709c[0x10];
	Player *m_currentPlayer;

	void evaluateAndProgressAllSequentialScripts();
	__forceinline VecSequentialScriptPtrIt cleanupSequentialScript(
		VecSequentialScriptPtrIt it, bool cleanDanglers);
};

__forceinline ScriptEngine::VecSequentialScriptPtrIt ScriptEngine::cleanupSequentialScript(
	VecSequentialScriptPtrIt it, bool cleanDanglers)
{
	--m_updateCount;
	SequentialScript *seqScript = *it;
	if (!seqScript) {
		it = m_sequentialScripts.erase(it);
	} else if (cleanDanglers) {
		while (seqScript) {
			SequentialScript *scriptToDelete = seqScript;
			seqScript = seqScript->m_nextScriptInSequence;
			scriptToDelete->deleteInstance();
		}
		*it = 0;
		it = m_sequentialScripts.erase(it);
	} else {
		*it = seqScript->m_nextScriptInSequence;
		seqScript->deleteInstance();
		if (!*it)
			it = m_sequentialScripts.erase(it);
	}
	++m_updateCount;
	return it;
}

// ?evaluateAndProgressAllSequentialScripts@ScriptEngine@@IAEXXZ
void ScriptEngine::evaluateAndProgressAllSequentialScripts(void)
{
	VecSequentialScriptPtrIt it, lastIt;
	lastIt = m_sequentialScripts.end();

	++m_updateCount;
	int spinCount = 0;
	for (it = m_sequentialScripts.begin(); it != m_sequentialScripts.end(); ) {
		if (it == lastIt) {
			++spinCount;
		} else {
			spinCount = 0;
		}

		if (spinCount > 0x14) {
			++it;
			continue;
		}

		lastIt = it;
		bool itAdvanced = false;
		SequentialScript *seqScript = *it;
		if (!seqScript) {
			it = cleanupSequentialScript(it, false);
			lastIt = m_sequentialScripts.end();
			continue;
		}

		Team *team = seqScript->m_teamToExecOn;
		Object *obj = TheGameLogic->findObjectByID(seqScript->m_objectID);
		if (!(obj || team)) {
			it = cleanupSequentialScript(it, false);
			lastIt = m_sequentialScripts.end();
			continue;
		}

		m_currentPlayer = 0;
		if (obj) {
			m_currentPlayer = obj->getControllingPlayer();
		} else if (team) {
			m_currentPlayer = team->getControllingPlayer();
		}
		AIUpdateInterface *ai = obj ? obj->getAIUpdateInterface() : 0;

		AIGroup *aigroup = team ? TheAI->createGroup() : 0;
		if (aigroup)
			team->getTeamAsAIGroup(aigroup);

		if (ai || aigroup) {
			bool canAdvance = true;
			if (seqScript->m_framesToWait <= 0) {
				if (seqScript->m_framesToWait < 0) {
					if (ai && ai->isIdle() && ai->isBusy())
						canAdvance = false;
					if (aigroup) {
						if (!aigroup->isIdle())
							canAdvance = false;
						else if (((Gen_00151340 *)aigroup)->bfmeAnyBusy())
							canAdvance = false;
					}
				}

				if (canAdvance) {
					bool displayMessage = true;
					if (seqScript->m_dontAdvanceInstruction) {
						seqScript->m_dontAdvanceInstruction = false;
						displayMessage = false;
					} else {
						++seqScript->m_currentInstruction;
					}

					AsciiString msg = "Advancing SeqScript '";
					msg.concat(seqScript->m_displayString);
					msg.concat("' on ", 5);
					AsciiString name;
					if (team)
						name = team->getName();
					if (obj)
						name = obj->getName();
					msg.concat(name);
					msg.concat(" -- ", 4);

					int instruction = seqScript->m_currentInstruction;
					ScriptAction *action = seqScript->m_scriptToExecuteSequentially->getAction();
					while (action && instruction) {
						--instruction;
						action = action->getNext();
					}

					if (action) {
						Team *actionTeam = team;
						LatchRestore<AsciiString> latch(m_17088, seqScript->m_latchedString);
						m_conditionTeam = actionTeam;
						m_conditionObject = obj;
						seqScript->m_framesToWait = -1;

						ScriptAction *nextAction = action->getNext();
						action->setNextAction(0);
						if (action->getActionType() == 0x107) {
							if (!TheScriptConditions->evaluateSkirmishCommandButtonIsReady(
								0, action->getParameter(1), action->getParameter(2), true))
								seqScript->m_dontAdvanceInstruction = true;
						} else if (action->getActionType() == 0x108) {
							if (!TheScriptConditions->evaluateSkirmishCommandButtonIsReady(
								0, action->getParameter(1), action->getParameter(2), false))
								seqScript->m_dontAdvanceInstruction = true;
						} else if (action->getActionType() == 0x11b) {
							if (TheScriptConditions->evaluateTeamIsContained(
								action->getParameter(0), true))
								seqScript->m_dontAdvanceInstruction = true;
						} else if (action->getActionType() == 0x11c) {
							if (TheScriptConditions->evaluateTeamIsContained(
								action->getParameter(0), false))
								seqScript->m_dontAdvanceInstruction = true;
						} else if (action->getActionType() == 0x1f0) {
							if (!TheScriptConditions->evaluateBfmeSequentialWait(
								action->getParameter(0)))
								seqScript->m_dontAdvanceInstruction = true;
						} else {
							executeActions(action);
						}

						if (displayMessage) {
							msg.concat(action->getUiText());
							AppendDebugMessage(msg, false);
						} else {
							msg.clear();
						}

						action->setNextAction(nextAction);
						if (seqScript->m_dontAdvanceInstruction) {
							++it;
							itAdvanced = true;
							continue;
						}

						if (ai && ai->isIdle()) {
							itAdvanced = true;
						} else if (actionTeam) {
							aigroup = TheAI->createGroup();
							actionTeam->getTeamAsAIGroup(aigroup);
						}

						if (aigroup && aigroup->isIdle())
							itAdvanced = true;

						if (itAdvanced) {
							if (obj && obj->isEffectivelyDead()) {
								it = cleanupSequentialScript(it, true);
								lastIt = m_sequentialScripts.end();
								continue;
							}

							if (aigroup && aigroup->isGroupAiDead()) {
								if (!(actionTeam && m_currentPlayer && actionTeam == m_currentPlayer->getTeam())) {
									it = cleanupSequentialScript(it, true);
									lastIt = m_sequentialScripts.end();
									continue;
								}
							}
						}
					} else {
						if (seqScript->m_timesToLoop != 0) {
							if (seqScript->m_timesToLoop != -1)
								--seqScript->m_timesToLoop;
							seqScript->m_framesToWait = -1;

							int index = it - m_sequentialScripts.begin();
							--m_updateCount;
							appendSequentialScript(seqScript);
							++m_updateCount;
							it = m_sequentialScripts.begin() + index;
						}

						it = cleanupSequentialScript(it, false);
						lastIt = m_sequentialScripts.end();
						itAdvanced = true;
					}
					}
				}

			if (seqScript->m_framesToWait > 0)
				--seqScript->m_framesToWait;
		}

		if (!itAdvanced)
			++it;
	}

	m_currentPlayer = 0;
	--m_updateCount;
}
