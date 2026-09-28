// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0033E9A0, 360 bytes: BFME's copy of the ScriptEngine.cpp file-scope
// helper _appendMessage.  The identity is the Zero Hour twin at
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/
// ScriptEngine/ScriptEngine.cpp:9356 -- same name, same
// (const AsciiString &, Bool, Bool) signature, same "Run script - " /
// "Run script false -" pair, same "%d " frame prefix, and the same
// GetProcAddress("AppendMessageAndPause")/("AppendMessage") tail.  BFME adds
// two early-outs (the byte at 0x012ED4D8 and the debug-window module) and a
// prefix filter over the AsciiString vector at TheWritableGlobalData+0x11E0;
// the recorder pins at 0x012ED620/0x012ED624 independently place scalars at
// GlobalData+0x11EC and +0x11F0, which brackets that vector to 0x11E0..0x11E8.
//
// The retail body takes `str` live in EDI, saves only ESI and returns without
// popping arguments: MSVC 7.1's private convention for a static helper.  That
// is why it stays `static` here and why one source-level call site is kept at
// the bottom -- without a call in the TU the helper is neither emitted nor
// given the register-passed first argument.  ScriptEngine::applyNamed
// (0x00340F10, BFME's executeScript) below reaches it four times; placing
// that caller in this TU is what gives it retail's `mov edi,eax` and
// two-push call shape.

typedef int Int;
typedef bool Bool;
typedef void *HMODULE;
typedef int(__stdcall *FARPROC)();

extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(
	HMODULE module, const char *procName);

// The shared empty string retail substitutes for a null buffer.
extern const char Rva006A16B0Empty[];

template <class T> class StringBase
{
	friend class BFMERetailAsciiString;
	friend class AsciiString;

protected:
	struct Data
	{
		Int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data(0) {}

private:
	StringBase(const T *text);				// 0x00888BC0
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

public:
	void concat(const T *text, Int length);			// 0x00887D60
	Bool startsWith(const T *text, Int length) const;	// 0x008875A0

	Data *m_data;
};

template <class T> class BFMERetailStringBase;

class BFMERetailAsciiString : public StringBase<char>
{
	friend class AsciiString;
	friend class BFMERetailStringBase<char>;

public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}

private:
	void releaseBuffer();					// 0x00887940
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString()
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}

	void __cdecl format(AsciiString format, ...);		// 0x00888FF0

	void concat(const char *text, Int length)
	{
		StringBase<char>::concat(text, length);
	}

	void concat(const AsciiString &other)
	{
		StringBase<char>::concat(other.str(), other.getLength());
	}

	Bool startsWith(const AsciiString &other) const
	{
		return StringBase<char>::startsWith(other.str(), other.getLength());
	}

	const char *str() const
	{
		return m_data ? m_data->m_text : Rva006A16B0Empty;
	}

	Int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}
};

class GameLogic
{
public:
	Int getFrame() const { return m_frame; }

private:
	unsigned char m_unknown00[0x3c];
	Int m_frame;						// +0x3C
};

// The three-pointer vector living at GlobalData+0x11E0.  Only begin/end are
// witnessed here, so the members keep offset-derived names.
class GlobalData11E0StringVec
{
public:
	AsciiString *begin() const { return m_start; }
	AsciiString *end() const { return m_finish; }

private:
	AsciiString *m_start;					// +0x00
	AsciiString *m_finish;					// +0x04
	AsciiString *m_endOfStorage;				// +0x08
};

class GlobalData
{
public:
	unsigned char m_unknown00[0x11e0];
	GlobalData11E0StringVec m_stringVec11E0;		// +0x11E0
};

class Script;
class ScriptAction;
class Team;
class Player;

enum GameDifficulty
{
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD
};

class Player
{
public:
	GameDifficulty getPlayerDifficulty() const;		// ILT 0x000217D8
};

// Zero Hour's DLINK_ITERATOR (GameCommon.h): the next-function member pointer
// is a second iterator word, which is why the walk's frame holds eight bytes
// for it although the pointer folds into a direct call.
template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	Team *_bfme_nextInInstanceList() const;			// ILT 0x00022A70
};

class TeamPrototype
{
public:
	Int countTeamInstances();				// ILT 0x0003DE8D

	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_teamInstanceList, &Team::_bfme_nextInInstanceList);
	}

private:
	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;				// +0x274
};

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &name,
		const AsciiString &ownerName);			// ILT 0x00040A39
};

// The by-value string accessor at 0x00338EF0 (ILT 0x00012378) returns the
// retail StringBase<char> copy of the string at Script+0x30.
template <class T> class BFMERetailStringBase
{
public:
	~BFMERetailStringBase()
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}

	Bool isEmpty() const { return !m_data || m_data->m_length == 0; }

	typename StringBase<T>::Data *m_data;
};

class Rva00338EF0Host
{
public:
	BFMERetailStringBase<char> copyStringAt30();		// ILT 0x00012378
};

class ScriptEngine;

class BFMEScriptEngineFlagLookup
{
	friend class ScriptEngine;

private:
	AsciiString canonicalFlagName(const AsciiString &name);	// ILT 0x00036336
};

class Script
{
public:
	Int getDelayEvalSeconds() const { return *(const Int *)((const char *)this + 0x10); }
	Bool isActive() const { return *(const Bool *)((const char *)this + 0x14); }
	void setActive(Bool active) { *(Bool *)((char *)this + 0x14) = active; }
	Bool isOneShot() const { return *(const Bool *)((const char *)this + 0x16); }
	Bool isEasy() const { return *(const Bool *)((const char *)this + 0x18); }
	Bool isNormal() const { return *(const Bool *)((const char *)this + 0x19); }
	Bool isHard() const { return *(const Bool *)((const char *)this + 0x1a); }
	ScriptAction *getAction() const { return *(ScriptAction *const *)((const char *)this + 0x20); }
	ScriptAction *getFalseAction() const { return *(ScriptAction *const *)((const char *)this + 0x24); }
	unsigned int getFrameToEvaluate() const { return *(const unsigned int *)((const char *)this + 0x28); }
	void setFrameToEvaluate(unsigned int frame) { *(unsigned int *)((char *)this + 0x28) = frame; }
	void setCurTime(float t) { *(float *)((char *)this + 0x38) = t; }
};

class ScriptEngine
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
	virtual Bool evaluateConditions(Script *pScript, Team *thisTeam = 0,
		Player *player = 0);				// vtable +0x5C

	Bool isTimeFast();					// ILT 0x0000A8A8 -> 0x00336FB0
	void applyNamed(void *object, void *slot);

protected:
	void executeActions(ScriptAction *pActionHead);		// ILT 0x0000B811

private:
	const AsciiString &scope17088() const { return *(const AsciiString *)((const char *)this + 0x17088); }
	Team *&team17094() { return *(Team **)((char *)this + 0x17094); }
	Player *player170AC() const { return *(Player *const *)((const char *)this + 0x170ac); }
	GameDifficulty difficulty17620() const { return *(const GameDifficulty *)((const char *)this + 0x17620); }
};

AsciiString Rva00195FC0JoinPath(const AsciiString &left, const AsciiString &right);

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer,
	const char *format, ...);

extern void *TheScriptDebugWindowDLL;				// 0x012F0758
extern GlobalData *TheWritableGlobalData;			// 0x012ED5C8
extern GameLogic *TheGameLogic;					// 0x012F0898
extern ScriptEngine *TheScriptEngine;				// 0x012F076C
extern TeamFactory *TheTeamFactory;				// 0x012ED810

// 0x012ED4D8 carries no ledger pin; the address-derived spelling already used
// by game/GameEngine/Source/Common/T3CommandLineParsers.cpp is kept.
extern Bool g_flag12ED4D8;					// 0x012ED4D8

// ?_appendMessage@@YAXABVAsciiString@@_N1@Z
static void _appendMessage(const AsciiString &str, Bool isTrueMessage,
	Bool shouldPause)
{
	if (g_flag12ED4D8)
		return;
	if (!TheScriptDebugWindowDLL)
		return;

	// begin()/end() rather than the raw fields: retail materialises the end
	// pointer into a register before the compare, which the direct field
	// read folds into `cmp esi,[reg+0x11E4]` instead.
	for (AsciiString *name = TheWritableGlobalData->m_stringVec11E0.begin();
		 name != TheWritableGlobalData->m_stringVec11E0.end();
		 ++name)
	{
		if (str.startsWith(*name))
			return;
	}

	{
		AsciiString msg;
		msg.format("%d ", TheGameLogic->getFrame());
		// Retail passes both lengths as immediates; Zero Hour's
		// concat(const char *) folds strlen to the same 13 and 18.
		if (isTrueMessage)
			msg.concat("Run script - ", 13);
		else
			msg.concat("Run script false -", 18);
		msg.concat(str);

		HMODULE module = TheScriptDebugWindowDLL;
		if (!module)
			return;

		FARPROC proc;
		if (shouldPause)
			proc = GetProcAddress(module, "AppendMessageAndPause");
		else
			proc = GetProcAddress(module, "AppendMessage");
		if (!proc)
			return;

		((void(__cdecl *)(const char *))proc)(msg.str());
	}
}

// ?_adjustVariable@@YAXABVAsciiString@@H_N1@Z
// Retail 0x0033EB70, 297 bytes: the Zero Hour twin at ScriptEngine.cpp:9389
// (same "AdjustVariableAndPause"/"AdjustVariable" GetProcAddress pair and
// "%d" formatting of the value).  BFME adds the same early-outs as
// _appendMessage plus a TheScriptEngine->isTimeFast() guard, and a trailing
// flag selecting "%d (%0.2f secs)" with the value scaled by 0.2.  Same private
// convention: str live in EDI and no argument pop.
static void _adjustVariable(const AsciiString &str, Int value,
	Bool shouldPause, Bool showSeconds)
{
	if (g_flag12ED4D8)
		return;
	if (TheScriptEngine->isTimeFast())
		return;
	if (!TheScriptDebugWindowDLL)
		return;

	for (AsciiString *name = TheWritableGlobalData->m_stringVec11E0.begin();
		 name != TheWritableGlobalData->m_stringVec11E0.end();
		 ++name)
	{
		if (str.startsWith(*name))
			return;
	}

	char buff[32];
	if (showSeconds)
		sprintf(buff, "%d (%0.2f secs)", value, value * 0.2f);
	else
		sprintf(buff, "%d ", value);

	HMODULE module = TheScriptDebugWindowDLL;
	if (!module)
		return;

	FARPROC proc;
	if (shouldPause)
		proc = GetProcAddress(module, "AdjustVariableAndPause");
	else
		proc = GetProcAddress(module, "AdjustVariable");
	if (!proc)
		return;

	((void(__cdecl *)(const char *, const char *))proc)(str.str(), buff);
}

// ?applyNamed@ScriptEngine@@QAEXPAX0@Z
// Retail 0x00340F10, 779 bytes: BFME's ScriptEngine::executeScript (the Zero
// Hour twin at ScriptEngine.cpp:6950) with a second argument, the qualified
// script name the debug messages join onto the scope at this+0x17088.
void ScriptEngine::applyNamed(void *object, void *slot)
{
	Script *pScript = (Script *)object;
	const AsciiString &scriptName = *(const AsciiString *)slot;

	pScript->setCurTime(0);
	if (!pScript->isActive())
		return;
	GameDifficulty difficulty = difficulty17620();
	if (player170AC())
		difficulty = player170AC()->getPlayerDifficulty();
	switch (difficulty)
	{
		case DIFFICULTY_EASY: if (!pScript->isEasy()) return; break;
		case DIFFICULTY_NORMAL: if (!pScript->isNormal()) return; break;
		case DIFFICULTY_HARD: if (!pScript->isHard()) return; break;
	}
	if ((unsigned int)TheGameLogic->getFrame() < pScript->getFrameToEvaluate())
		return;
	Int delaySeconds = pScript->getDelayEvalSeconds();
	if (delaySeconds > 0)
		pScript->setFrameToEvaluate(TheGameLogic->getFrame() + delaySeconds * 5);

	Team *pSavConditionTeam = team17094();
	TeamPrototype *pProto = 0;

	if (!((Rva00338EF0Host *)pScript)->copyStringAt30().isEmpty())
	{
		BFMERetailStringBase<char> teamName = ((Rva00338EF0Host *)pScript)->copyStringAt30();
		AsciiString canonical = ((BFMEScriptEngineFlagLookup *)this)->canonicalFlagName(
			*(const AsciiString *)&teamName);
		pProto = TheTeamFactory->findTeamPrototype(canonical, *(const AsciiString *)&teamName);
	}

	if (pProto && pProto->countTeamInstances() > 0)
	{
		for (DLINK_ITERATOR<Team> iter = pProto->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			team17094() = iter.cur();
			if (evaluateConditions(pScript))
			{
				if (pScript->getAction())
				{
					_appendMessage(Rva00195FC0JoinPath(scope17088(), scriptName), true, false);
					executeActions(pScript->getAction());
				}
				if (pScript->isOneShot())
					pScript->setActive(false);
			}
			else if (pScript->getFalseAction())
			{
				_appendMessage(Rva00195FC0JoinPath(scope17088(), scriptName), false, false);
				executeActions(pScript->getFalseAction());
			}
		}
	}
	else
	{
		team17094() = 0;
		if (evaluateConditions(pScript))
		{
			if (pScript->getAction())
			{
				_appendMessage(Rva00195FC0JoinPath(scope17088(), scriptName), true, false);
				executeActions(pScript->getAction());
			}
			if (pScript->isOneShot())
				pScript->setActive(false);
		}
		else if (pScript->getFalseAction())
		{
			_appendMessage(Rva00195FC0JoinPath(scope17088(), scriptName), false, false);
			executeActions(pScript->getFalseAction());
			if (pScript->isOneShot())
				pScript->setActive(false);
		}
	}

	team17094() = pSavConditionTeam;
}

// Scaffold, not a retail body: the only call site of _adjustVariable inside
// this TU, which is what makes MSVC emit it at all and keep its private
// register-passed first argument.  It goes away when the callers at
// 0x00341350 and 0x0034B9A0 are converted; applyNamed above already calls
// _appendMessage from retail's own TU.
void Rva0033E9A0AppendMessageCallSite(const AsciiString &str)
{
	_appendMessage(str, true, false);
	_adjustVariable(str, 0, false, false);
}
