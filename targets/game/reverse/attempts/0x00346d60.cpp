// ?evaluateAndProgressAllSequentialScripts@ScriptEngine@@IAEXXZ
// partial score=0.86 date=2026-09-28
// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ScriptEngine::evaluateAndProgressAllSequentialScripts, retail 0x00346D60 (1950 B).
// Banked 2026-09-28 (opus-5.5): probe shape 0.862, 1856/1950 B, 1227 differing bytes
// (previous stash re-probed today: shape 0.777, 1906 B, 1616 differing).
// Levers that moved it: cleanupSequentialScript takes the iterator BY REFERENCE (retail
// keeps `it` in memory at [esp+0x14] and reloads it at the loop top); the update-count
// guard (--/++ at +0x18) wraps each cleanup call in the caller with `lastIt = end()` before
// the ++; nested spin test; extern globals; Bfme5CtorA0 as the record type.
// Open: this/seqScript registers swapped (retail ebp/edi); the 0x107/0x108 tails do not
// cross-jump (ours loads TheScriptConditions before `push 1`); fw readiness block shape.
// Link needs a pin for vector<Bfme5CtorA0*>::erase at 0x00339D10 (ILT 0x0003F99F).

#include <vector>

typedef bool Bool;
typedef int Int;

extern const char Rva006A16B0Empty[]; // retail 0x0107388B

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	void concat(const T *text, int length);
	void set(const StringBase<T> &that);

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
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &that)
	{
		StringBase<char>::set(that);
		return *this;
	}

	void concat(const AsciiString &that)
	{
		int length = that.m_data ? that.m_data->length : 0;
		const char *text = that.m_data ? that.m_data->data : Rva006A16B0Empty;
		StringBase<char>::concat(text, length);
	}

	void concat(const char *text, int length) { StringBase<char>::concat(text, length); }
	void clear() { releaseBuffer(); }
};

extern AsciiString Rva01336E50EmptyString; // retail 0x01336E50

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LatchRestore.h
template <typename T> class LatchRestore
{
public:
	LatchRestore(T &dest, const T &src);
	virtual ~LatchRestore();

protected:
	T valueToRestore;
	T &whereToStore;
};

class Parameter;

class ScriptAction
{
public:
	Int getActionType() const { return m_actionType; }
	Parameter *getParameter(Int index) const
	{
		return index >= 0 && index < m_parameterCount ? m_parameters[index] : 0;
	}
	ScriptAction *getNext() const { return m_nextAction; }
	void setNextAction(ScriptAction *next) { m_nextAction = next; }
	AsciiString getUiText();

private:
	void *m_vtable;
	Int m_actionType;
	Int m_parameterCount;
	Parameter *m_parameters[12];
	ScriptAction *m_nextAction;
};

class Script
{
public:
	ScriptAction *getAction() const { return m_action; }

private:
	unsigned char m_unmodelled00[0x20];
	ScriptAction *m_action;
};

class Team;
class Player;
class AIGroup;

// The sequential-script record, under the class name its matched
// appendSequentialScript row uses (ScriptEngine_appendSequentialScript.cpp).
class Bfme5CtorA0
{
public:
	virtual ~Bfme5CtorA0();

	Team *m_base;
	Int m_objectID;
	AsciiString m_nameA;
	AsciiString m_nameB;
	Script *m_scriptToExecuteSequentially;
	Int m_currentInstruction;
	Int m_timesToLoop;
	Int m_framesToWait;
	Bool m_dontAdvanceInstruction;
	Bfme5CtorA0 *m_nextScriptInSequence;
};

class TeamPrototype
{
public:
	const AsciiString &getName() const { return m_name; }

private:
	unsigned char m_unmodelled00[0x14];
	AsciiString m_name;
};

class Team
{
public:
	Player *getControllingPlayer() const;
	void getTeamAsAIGroup(AIGroup *group);

	const AsciiString &getName() const
	{
		if (!m_proto)
			return Rva01336E50EmptyString;
		return m_proto->getName();
	}

private:
	void *m_vtable;
	TeamPrototype *m_proto;
};

class AIUpdateInterface
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual Bool isIdle() const;

	Bool isBusy338() const { return m_flag338; }

private:
	unsigned char m_unmodelled004[0x334];
	Bool m_flag338;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	const AsciiString &getName() const { return m_name; }
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	Bool isEffectivelyDead() const { return (m_status344 & 1) != 0; }

private:
	unsigned char m_unmodelled000[0x84];
	AsciiString m_name;
	unsigned char m_unmodelled088[0x17c];
	AIUpdateInterface *m_ai;
	unsigned char m_unmodelled208[0x13c];
	unsigned char m_status344;
};

class AIGroup
{
public:
	Bool isIdle() const;
	Bool isGroupAiDead() const;
};

class Gen_00151340
{
public:
	Bool bfmeAnyBusy() const;
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }

private:
	unsigned char m_unmodelled000[0x230];
	Team *m_defaultTeam;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class AI
{
public:
	AIGroup *createGroup();
};

class ScriptConditionsInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Bool evaluateSkirmishCommandButtonIsReady(Parameter *, Parameter *, Parameter *, Bool);
	virtual Bool evaluateTeamIsContained(Parameter *, Bool);
	virtual Bool slot0C(Parameter *);
};

extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern ScriptConditionsInterface *TheScriptConditions;

class ScriptEngine
{
public:
	void appendSequentialScript(Bfme5CtorA0 *script);
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);

protected:
	typedef _STL::vector<Bfme5CtorA0 *> VecSequentialScriptPtr;
	typedef VecSequentialScriptPtr::iterator VecSequentialScriptPtrIt;

	void executeActions(ScriptAction *action);
	void evaluateAndProgressAllSequentialScripts(void);
	void cleanupSequentialScript(VecSequentialScriptPtrIt &it, Bool cleanDanglers)
	{
		Bfme5CtorA0 *seqScript = *it;
		if (!seqScript)
		{
			it = m_sequentialScripts.erase(it);
		}
		else if (cleanDanglers)
		{
			while (seqScript)
			{
				Bfme5CtorA0 *scriptToDelete = seqScript;
				seqScript = seqScript->m_nextScriptInSequence;
				delete scriptToDelete;
			}
			*it = 0;
			it = m_sequentialScripts.erase(it);
		}
		else
		{
			*it = seqScript->m_nextScriptInSequence;
			delete seqScript;
			if (!*it)
				it = m_sequentialScripts.erase(it);
		}
	}

	void *m_vtable;
	unsigned char m_unmodelled004[8];
	VecSequentialScriptPtr m_sequentialScripts;
	Int m_updateCount;
	unsigned char m_unmodelled0001C[0x17088 - 0x1c];
	AsciiString m_currentScope;
	unsigned char m_unmodelled1708C[8];
	Team *m_conditionTeam;
	Object *m_conditionObject;
	unsigned char m_unmodelled1709C[0x10];
	Player *m_currentPlayer;
};

// ?evaluateAndProgressAllSequentialScripts@ScriptEngine@@IAEXXZ
void ScriptEngine::evaluateAndProgressAllSequentialScripts(void)
{
	VecSequentialScriptPtrIt it, lastIt;
	lastIt = m_sequentialScripts.end();

	++m_updateCount;
	Int spinCount = 0;
	for (it = m_sequentialScripts.begin(); it != m_sequentialScripts.end(); )
	{
		if (it == lastIt)
		{
			if (++spinCount > 20)
			{
				++it;
				continue;
			}
		}
		else
			spinCount = 0;

		lastIt = it;
		Bool itAdvanced = false;

		Bfme5CtorA0 *seqScript = *it;
		if (seqScript == 0)
		{
			--m_updateCount;
			cleanupSequentialScript(it, false);
			lastIt = m_sequentialScripts.end();
			++m_updateCount;
			continue;
		}

		Team *team = seqScript->m_base;
		Object *obj = TheGameLogic->findObjectByID(seqScript->m_objectID);
		if (!(obj || team))
		{
			--m_updateCount;
			cleanupSequentialScript(it, false);
			lastIt = m_sequentialScripts.end();
			++m_updateCount;
			continue;
		}

		m_currentPlayer = 0;
		if (obj)
			m_currentPlayer = obj->getControllingPlayer();
		else if (team)
			m_currentPlayer = team->getControllingPlayer();

		AIUpdateInterface *ai = obj ? obj->getAIUpdateInterface() : 0;
		AIGroup *aigroup = team ? TheAI->createGroup() : 0;
		if (aigroup)
			team->getTeamAsAIGroup(aigroup);

		if (ai || aigroup)
		{
			Bool ready = true;
			if (seqScript->m_framesToWait < 1 && seqScript->m_framesToWait != 0)
			{
				if (ai && (!ai->isIdle() || ai->isBusy338()))
					ready = false;
				if (aigroup && (!aigroup->isIdle() || ((Gen_00151340 *)aigroup)->bfmeAnyBusy()))
					ready = false;
			}

			if ((ready && seqScript->m_framesToWait < 1) || seqScript->m_framesToWait == 0)
			{
				Bool displayMessage = true;
				if (seqScript->m_dontAdvanceInstruction)
				{
					seqScript->m_dontAdvanceInstruction = false;
					displayMessage = false;
				}
				else
				{
					++seqScript->m_currentInstruction;
				}

				AsciiString msg = "Advancing SeqScript '";
				msg.concat(seqScript->m_nameB);
				msg.concat("' on ", 5);
				AsciiString name;
				if (team)
					name = team->getName();
				if (obj)
					name = obj->getName();
				msg.concat(name);
				msg.concat(" -- ", 4);

				Int instruction = seqScript->m_currentInstruction;
				ScriptAction *action = seqScript->m_scriptToExecuteSequentially->getAction();
				while (action && instruction)
				{
					--instruction;
					action = action->getNext();
				}

				if (action)
				{
					LatchRestore<AsciiString> latch(m_currentScope, seqScript->m_nameA);
					m_conditionTeam = team;
					m_conditionObject = obj;
					seqScript->m_framesToWait = -1;

					ScriptAction *nextAction = action->getNext();
					action->setNextAction(0);
					if (action->getActionType() == 0x107)
					{
						if (!TheScriptConditions->evaluateSkirmishCommandButtonIsReady(0,
							action->getParameter(1), action->getParameter(2), true))
							seqScript->m_dontAdvanceInstruction = true;
					}
					else if (action->getActionType() == 0x108)
					{
						if (!TheScriptConditions->evaluateSkirmishCommandButtonIsReady(0,
							action->getParameter(1), action->getParameter(2), false))
							seqScript->m_dontAdvanceInstruction = true;
					}
					else if (action->getActionType() == 0x11b)
					{
						if (TheScriptConditions->evaluateTeamIsContained(action->getParameter(0), true))
							seqScript->m_dontAdvanceInstruction = true;
					}
					else if (action->getActionType() == 0x11c)
					{
						if (TheScriptConditions->evaluateTeamIsContained(action->getParameter(0), false))
							seqScript->m_dontAdvanceInstruction = true;
					}
					else if (action->getActionType() == 0x1f0)
					{
						if (!TheScriptConditions->slot0C(action->getParameter(0)))
							seqScript->m_dontAdvanceInstruction = true;
					}
					else
					{
						executeActions(action);
					}

					if (displayMessage)
					{
						msg.concat(action->getUiText());
						AppendDebugMessage(msg, false);
					}
					else
					{
						msg.clear();
					}

					action->setNextAction(nextAction);

					if (seqScript->m_dontAdvanceInstruction)
					{
						++it;
						continue;
					}

					if (ai && ai->isIdle())
						itAdvanced = true;
					else if (team)
					{
						aigroup = TheAI->createGroup();
						team->getTeamAsAIGroup(aigroup);
					}

					if (aigroup && aigroup->isIdle())
						itAdvanced = true;

					if (itAdvanced)
					{
						if (obj && obj->isEffectivelyDead())
						{
							--m_updateCount;
							cleanupSequentialScript(it, true);
							lastIt = m_sequentialScripts.end();
							++m_updateCount;
							continue;
						}

						if (aigroup && aigroup->isGroupAiDead())
						{
							if (team && m_currentPlayer && team == m_currentPlayer->getDefaultTeam())
								continue;
							--m_updateCount;
							cleanupSequentialScript(it, true);
							lastIt = m_sequentialScripts.end();
							++m_updateCount;
							continue;
						}
					}
				}
				else
				{
					if (seqScript->m_timesToLoop != 0)
					{
						if (seqScript->m_timesToLoop != -1)
							--seqScript->m_timesToLoop;

						seqScript->m_framesToWait = -1;
						Int index = it - m_sequentialScripts.begin();
						--m_updateCount;
						appendSequentialScript(seqScript);
						++m_updateCount;
						it = m_sequentialScripts.begin() + index;
					}

					--m_updateCount;
					cleanupSequentialScript(it, false);
					lastIt = m_sequentialScripts.end();
					++m_updateCount;
					itAdvanced = true;
				}
			}
			else if (seqScript->m_framesToWait > 0)
			{
				--seqScript->m_framesToWait;
			}
		}

		if (!itAdvanced)
			++it;
	}
	m_currentPlayer = 0;
	--m_updateCount;
}
