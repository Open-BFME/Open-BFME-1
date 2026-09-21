// ?d_0033e9a0@@YAXXZ
// partial score=0.96 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0033E9A0, 360 bytes.  This is the BFME extension of the Zero Hour
// ScriptEngine::_appendMessage helper: the debug-window message is suppressed
// when the script-name prefix is already present in GlobalData's script list.

typedef int Int;
typedef bool Bool;
typedef void *HMODULE;
typedef int (__stdcall *FARPROC)();

extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(
	HMODULE module, const char *procName);

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
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

	public:
	void concat(const T *text, Int length);
	Bool startsWith(const T *text, Int length) const;

	Data *m_data;
};

class BFMERetailAsciiString : public StringBase<char>
{
	friend class AsciiString;

public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}

	private:
	void releaseBuffer();
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

	void __cdecl format(AsciiString format, ...);

	void concat(const char *text, Int length)
	{
		StringBase<char>::concat(text, length);
	}

	Bool startsWith(const char *text, Int length) const
	{
		return StringBase<char>::startsWith(text, length);
	}

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}

	Int length() const
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
	Int m_frame;
};

class Rva00026AB2Vec12
{
	public:
	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;
};

class GlobalData
{
	public:
	unsigned char m_unknown00[0x11e0];
	Rva00026AB2Vec12 m_vec11e0;
};

#define TheScriptDebugWindowDLL (*(HMODULE *)0x012F0758)
#define TheWritableGlobalData (*(GlobalData **)0x012ED5C8)

extern Bool ScriptDebugMessagesDisabled;
#define TheGameLogic (*(GameLogic **)0x012F0898)

static void _appendMessage(const AsciiString &str, Bool isTrueMessage,
	Bool shouldPause)
{
	if (ScriptDebugMessagesDisabled)
		return;
	if (!TheScriptDebugWindowDLL)
		return;

	for (AsciiString *name = TheWritableGlobalData->m_vec11e0.m_start;
		 name != TheWritableGlobalData->m_vec11e0.m_finish;
		 ++name)
	{
		if (str.startsWith(name->str(), name->length()))
			return;
	}

	{
		AsciiString msg;
		msg.format("%d ", TheGameLogic->getFrame());
		if (isTrueMessage)
			msg.concat("Run script - ", 13);
		else
			msg.concat("Run script false -", 18);
		msg.concat(str.str(), str.length());

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

		((void (__cdecl *)(const char *))proc)(msg.str());
	}
}

// The real caller is still a generated body at 0x00340F10.  Keeping one
// source-level caller here makes MSVC 7.1 retain the internal helper's private
// register-passed first argument convention while the caller is reconstructed.
void Rva0033E9A0AppendRunScriptMessage(const AsciiString &str)
{
	_appendMessage(str, true, false);
}
