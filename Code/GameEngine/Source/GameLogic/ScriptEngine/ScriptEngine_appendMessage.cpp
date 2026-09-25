// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0033E9A0, 360 bytes: BFME's copy of the ScriptEngine.cpp file-scope
// helper _appendMessage.  The identity is the Zero Hour twin at
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/
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
// given the register-passed first argument.  The real caller is still the
// generated body at 0x00340F10, which reaches it four times.

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

class BFMERetailAsciiString : public StringBase<char>
{
	friend class AsciiString;

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

class ScriptEngine
{
public:
	Bool isTimeFast();					// ILT 0x0000A8A8 -> 0x00336FB0
};

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer,
	const char *format, ...);

extern void *TheScriptDebugWindowDLL;				// 0x012F0758
extern GlobalData *TheWritableGlobalData;			// 0x012ED5C8
extern GameLogic *TheGameLogic;					// 0x012F0898
extern ScriptEngine *TheScriptEngine;				// 0x012F076C

// 0x012ED4D8 carries no ledger pin; the address-derived spelling already used
// by Code/GameEngine/Source/Common/T3CommandLineParsers.cpp is kept.
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

// Scaffold, not a retail body: the only call sites of the helpers inside this
// TU, which is what makes MSVC emit them at all and keep their private
// register-passed first argument.  They go away when the callers at
// 0x00340F10, 0x00341350 and 0x0034B9A0 are converted.
void Rva0033E9A0AppendMessageCallSite(const AsciiString &str)
{
	_appendMessage(str, true, false);
	_adjustVariable(str, 0, false, false);
}
