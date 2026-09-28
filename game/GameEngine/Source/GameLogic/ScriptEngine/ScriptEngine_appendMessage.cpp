// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
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
// is why it stays `static` here, beside its retail callers: without a call in
// the TU the helper is neither emitted nor given the register-passed first
// argument.  ScriptEngine::applyNamed (0x00340F10, BFME's executeScript)
// reaches _appendMessage four times, which gives it retail's `mov edi,eax` and
// two-push call shape; ScriptEngine::update (0x0034B9A0) calls _adjustVariable.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <map>

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
	void set(const StringBase<T> &other);			// 0x00887C90
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

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}

	void concat(const char *text, Int length)
	{
		StringBase<char>::concat(text, length);
	}

	void concat(char c)
	{
		concat(&c, 1);
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

#include "Common/LatchRestore.h"

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

enum NameKeyType;

class Player
{
public:
	GameDifficulty getPlayerDifficulty() const;		// ILT 0x000217D8
	NameKeyType getNameKey() const { return at20; }

	char at0[0x20];
	NameKeyType at20;
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


// Types used by ScriptEngine::update (0x0034B9A0).
extern AsciiString KEYNAME(NameKeyType);
struct Update0034B9A0Counter { AsciiString at10,at14; int at18; bool at1c,at1d; };
struct Update0034B9A0Flag { AsciiString at10,at14; bool at18; };
typedef _STL::_Rb_tree_node<Update0034B9A0Counter> CounterNode;
typedef _STL::_Rb_tree_node<Update0034B9A0Flag> FlagNode;
typedef _STL::_Rb_tree_iterator<Update0034B9A0Counter,_STL::_Nonconst_traits<Update0034B9A0Counter> > CounterIterator;
typedef _STL::_Rb_tree_iterator<Update0034B9A0Flag,_STL::_Nonconst_traits<Update0034B9A0Flag> > FlagIterator;
struct Update0034B9A0List { Update0034B9A0List *next,*prev; AsciiString value; };
class ScriptActionsInterface {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void update();
 virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
 virtual void closeWindows(bool);
};
class ScriptConditionsInterface {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void update();
 virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
 virtual void closeWindows(bool);
};
struct Rva003412E0Node;
class Rva00355950Arr;
class Rva003558C0Arr;
struct Update0034B9A0ScriptList { int at0; Rva003412E0Node *at4,*at8;
 Rva003412E0Node *getScript() { return at8; } Rva003412E0Node *getScriptGroup() { return at4; } };
struct Update0034B9A0Side { char at0[8]; Update0034B9A0ScriptList *at8; char atc[12];
 Update0034B9A0ScriptList *getScriptList() { return at8; } };
class SidesList {
public:
 char at0[0x28]; int at28; Update0034B9A0Side at2c[1];
 int getNumSides() const { return at28; }
 Update0034B9A0Side *at(int i) { return i>=0 && i<at28 ? &at2c[i] : 0; }
};
class PlayerList { public: Player *getNthPlayer(int); void updateTeamStates(); };

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
	virtual void slot03(); virtual void slot04(); virtual void update();
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
	void createNamedCache(); void _bfme_finishEndGame();
	void walkNamed(Rva00355950Arr*,Rva003412E0Node*,bool);
	void walkChild(Rva003558C0Arr*,Rva003412E0Node*);
	// Layout offsets read directly from the retail update and corroborated by newMap.
	char at00004[0x16040-4];
	_STL::_Rb_tree_node_base *at16040; char at16044[8];
	_STL::_Rb_tree_node_base *at1604c; char at16050[0x17080-0x16050];
	int at17080,at17084; AsciiString at17088; char at1708c[0x170a8-0x1708c];
	bool at170a8; char at170a9[3]; Player *at170ac; int at170b0,at170b4;
	char at170b8[0x17270-0x170b8]; Update0034B9A0List *at17270;
	char at17274[0x17637-0x17274]; bool at17637;

protected:
	void executeActions(ScriptAction *pActionHead);		// ILT 0x0000B811
	void updateFades();

private:
	const AsciiString &scope17088() const { return *(const AsciiString *)((const char *)this + 0x17088); }
	Team *&team17094() { return *(Team **)((char *)this + 0x17094); }
	Player *player170AC() const { return *(Player *const *)((const char *)this + 0x170ac); }
	GameDifficulty difficulty17620() const { return *(const GameDifficulty *)((const char *)this + 0x17620); }
};

AsciiString Rva00195FC0JoinPath(const AsciiString &left, const AsciiString &right);

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer,
	const char *format, ...);

// File statics as in the Zero Hour ScriptEngine.cpp (st_DebugDLL, st_CurrentFrame).
static void *TheScriptDebugWindowDLL;				// 0x012F0758
static int st_CurrentFrame;					// 0x012F0760
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

// ?update@ScriptEngine@@UAEXXZ
// Retail 0x0034B9A0, 1212 bytes: ZH ScriptEngine::update; vtable 010E7A30 slot 5
// -> ILT 00025A3B. Same TU as _adjustVariable for its private EDI convention.
extern void j_0003ce98(); extern void j_0000fcbd();
static __forceinline void callUpdateMember(ScriptEngine *p, void (*raw)()) {
 union {void (*raw)(); void (ScriptEngine::*member)();} u;
 u.raw=raw; (p->*u.member)();
}
extern ScriptActionsInterface *TheScriptActions;
extern ScriptConditionsInterface *TheScriptConditions;
extern SidesList *TheSidesList;
extern PlayerList *ThePlayerList;
#define CurrentFrame st_CurrentFrame

void ScriptEngine::update() {
 if(at170a8) {
  createNamedCache(); callUpdateMember(this,j_0003ce98); at170a8=false;
 } else callUpdateMember(this,j_0003ce98);
 if(at17084>0) { --at17084; if(at17084<1) TheScriptActions->closeWindows(false); }
 if(at17080>0) { --at17080; if(at17080<1) _bfme_finishEndGame(); }
 if(at170b4) updateFades();
 if(at17080>=0) return;
 if(TheScriptActions) TheScriptActions->update();
 if(TheScriptConditions) TheScriptConditions->update();
 // BFME uses ordered trees instead of the ZH fixed counter/flag arrays.
 _STL::_Rb_tree_node_base *end=at16040;
 for(CounterIterator it((CounterNode*)end->_M_left), e((CounterNode*)end); it!=e; ++it) {
  Update0034B9A0Counter *c=&*it;
  if(c->at1c && c->at18>=0) --c->at18;
 }
 // Each player temporarily overrides the current script-name scope.
 for(int i=0; i<TheSidesList->getNumSides(); i++) {
  at170ac=ThePlayerList->getNthPlayer(i);
  LatchRestore<AsciiString> latch(at17088,KEYNAME(at170ac->getNameKey()));
  Update0034B9A0Side *side=TheSidesList->at(i);
  Update0034B9A0ScriptList *sl=side->getScriptList();
  if(sl) { walkNamed((Rva00355950Arr*)sl,sl->getScript(),true); walkChild((Rva003558C0Arr*)sl,sl->getScriptGroup()); }
  at170ac=0;
 }
 // UI interaction strings are STLport 12-byte list nodes.
 ThePlayerList->updateTeamStates();
 Update0034B9A0List *node=at17270->next;
 while(node!=at17270) {
  Update0034B9A0List *old=node; node=node->next;
  old->value.~AsciiString(); _STL::__node_alloc<true,0>::deallocate(old,12);
 }
 at17270->next=at17270; at17270->prev=at17270;
 at17637=true; callUpdateMember(this,j_0000fcbd);
 at17637=false; CurrentFrame=(CurrentFrame+1);
 // Preserve the three separate temporary AsciiString lifetimes/EH states.
 if(TheScriptDebugWindowDLL && !isTimeFast()) {
  if(TheScriptDebugWindowDLL) {
   FARPROC proc=GetProcAddress(TheScriptDebugWindowDLL,"SetTheSidesList");
   if(proc) ((void (__cdecl*)(void*,void*,void*,void*,void*,void*,void*,void*,void*,void*,void*))proc)(
    TheSidesList,TheScriptEngine,*(void**)0x012ed668,TheWritableGlobalData,*(void**)0x012ed600,0,0,
    *(void**)0x012f1600,*(void**)0x012ef4cc,*(void**)0x012ef1d8,*(void**)0x012f0898);
  }
  end=at16040;
  for(CounterIterator it((CounterNode*)end->_M_left), e((CounterNode*)end); it!=e; ++it) {
   AsciiString name=it->at10; name.concat('/'); name.concat(it->at14);
   if(it->at1d) _adjustVariable(name.str(),it->at18,false,true);
   else _adjustVariable(name.str(),it->at18,false,false);
  }
  end=at1604c;
  for(FlagIterator it((FlagNode*)end->_M_left), e((FlagNode*)end); it!=e; ++it) {
   AsciiString name=it->at10; name.concat('/'); name.concat(it->at14);
   _adjustVariable(name.str(),it->at18,false,false);
  }
 }
}

