// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef void *HMODULE;
typedef int (__stdcall *FARPROC)();

extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(
	HMODULE module, const char *procName);

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

	void __cdecl format(AsciiString format, ...);
	void concat(const AsciiString &suffix)
	{
		((StringBase<char> *)this)->StringBase<char>::concat(
			*(const StringBase<char> *)&suffix);
	}
	const char *str() const
	{
		static const char TheNullChr = 0;
		return m_data ? m_data->m_text : &TheNullChr;
	}

private:
	AsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Int getFrame() const { return m_frame; }

private:
	unsigned char m_unreconstructed[0x3c];
	Int m_frame;
};

extern Bool ScriptDebugMessagesDisabled;
extern HMODULE TheScriptDebugWindowDLL;
extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause);
};

void ScriptEngine::AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause)
{
	if (ScriptDebugMessagesDisabled || !TheScriptDebugWindowDLL)
		return;

	FARPROC proc = GetProcAddress(TheScriptDebugWindowDLL, "AppendMessage");
	if (!proc)
		return;

	AsciiString msg;
	msg.format("%d ", TheGameLogic->getFrame());
	msg.concat(strToAdd);
	((void (__cdecl *)(const char *))proc)(msg.str());
}
