// ?Rva0033E880@ScriptEngine@@QAEXXZ
// partial score=0.249 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x0033E880 (229 bytes). No named caller, vtable slot, or
// canonical BFME method name identifies this body (tools/callers_of.py finds
// no reaching caller; tools/vtable_lookup.py finds no slot). Its this-
// relative field at +0x17638 is the same byte tools/dis_retail.py shows
// ScriptEngine::isTimeFrozenDebug / _bfme_isClientFrameFrozen read and write
// as m_useLogicDebugFrame in Code/GameEngine/Source/GameLogic/ScriptEngine/
// ScriptEngineDebugFrame.cpp, so the class is proven even though the method
// name is not; it keeps the address-derived ScriptEngine::Rva0033E880 name
// used for other unidentified ScriptEngine members in this directory (see
// ScriptEngineRva0033D8B0TemplateKeys.cpp).
//
// WHAT THE BYTES SHOW. The old m_useLogicDebugFrame value gates a
// forcePause test against LogicCanAppContinue/ClientCanAppContinue (reading
// TheScriptDebugWindowDLL once, up front, before the flag test -- both
// branches share that one read). The flag is then TOGGLED (stored value is
// the logical NOT of the value just tested) and the new value picks which
// of two literal strings -- "Stepping logic frames." at 0x010E7894 or
// "Stepping client frames." at 0x010E7878 -- gets reported through
// AppendDebugMessage with the forcePause computed above. The two temporary
// AsciiStrings sit in mutually exclusive if/else arms, which is why retail's
// EH unwind state differs (0 vs 1) between them.

typedef bool Bool;
typedef int Int;
typedef void *HMODULE;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	unsigned char m_header[8];
	char m_text[1];
};

template <class T> class StringBase
{
	friend class AsciiString;

public:
	void concat(const StringBase &suffix);

private:
	StringBase(const char *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	~AsciiString();

private:
	AsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void Rva0033E880();
	void AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause);

private:
	unsigned char m_unknown00[0x17638];
	Bool m_useLogicDebugFrame;
};

#define TheScriptDebugWindowDLLRef (*(HMODULE *)0x012F0758)
#define LogicCanAppContinueRef (*(Bool *)0x012F075D)
#define ClientCanAppContinueRef (*(Bool *)0x012F075C)

// ?Rva0033E880@ScriptEngine@@QAEXXZ
void ScriptEngine::Rva0033E880()
{
	Bool wasLogic = m_useLogicDebugFrame;
	HMODULE dll = TheScriptDebugWindowDLLRef;
	Bool forcePause;
	if (wasLogic)
		forcePause = dll && !LogicCanAppContinueRef;
	else
		forcePause = dll && !ClientCanAppContinueRef;

	Bool newLogic = !wasLogic;
	m_useLogicDebugFrame = newLogic;

	if (newLogic)
		AppendDebugMessage(AsciiString("Stepping logic frames."), forcePause);
	else
		AppendDebugMessage(AsciiString("Stepping client frames."), forcePause);
}
