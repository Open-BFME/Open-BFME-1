// ?first@Rva005187E0@@QAEXXZ
// partial score=0.65 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva005187E0
{
public:
	void first();
	void wrap(int a);

private:
	char m_unmodelled[0x390];
	char m_userNamePrefs[0x18];
	char m_gap3a8[0x14];
	class GameWindow *m_chatEntry;
};

template <typename T> struct Rva005187E0StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void set(const StringBase<T> &other);
	void releaseBuffer();
	bool nextToken(StringBase<T> *out, const T *separators);

	Rva005187E0StringData<T> *m_data;
};

extern const char g_bfmeEmptyUnicode[];

class UnicodeString
{
public:
	static const UnicodeString TheEmptyString;

	UnicodeString() { m_data = 0; }
	UnicodeString(const unsigned short *text)
	{
		((StringBase<unsigned short> *)this)->
			StringBase<unsigned short>::StringBase(text);
	}
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->
			StringBase<unsigned short>::StringBase(
				*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString()
	{
		((StringBase<unsigned short> *)this)->releaseBuffer();
	}

	void set(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&other);
	}

	bool nextToken(UnicodeString *out, const unsigned short *separators)
	{
		return ((StringBase<unsigned short> *)this)->nextToken(
			(StringBase<unsigned short> *)out, separators);
	}

	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	unsigned short getCharAt(int index) const
	{
		return m_data->m_text[index];
	}

	const unsigned short *str() const
	{
		return m_data ? m_data->m_text
			: (const unsigned short *)g_bfmeEmptyUnicode;
	}

	int compareNoCase(const unsigned short *text) const;
	UnicodeString &append(const unsigned short *text);

private:
	Rva005187E0StringData<unsigned short> *m_data;
};

class GameWindow;
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);

class LanLobbyUserNamePrefs
{
};

extern void j_000351c5();
extern void j_00041f3d();
extern void j_0002d790();

class LANAPI
{
public:
#define LANAPI_SLOT(N) virtual void slot##N();
	LANAPI_SLOT(00) LANAPI_SLOT(01) LANAPI_SLOT(02)
	LANAPI_SLOT(03) LANAPI_SLOT(04) LANAPI_SLOT(05)
	LANAPI_SLOT(06) LANAPI_SLOT(07) LANAPI_SLOT(08)
	LANAPI_SLOT(09) LANAPI_SLOT(10) LANAPI_SLOT(11)
	LANAPI_SLOT(12) LANAPI_SLOT(13) LANAPI_SLOT(14)
	LANAPI_SLOT(15)
	virtual void RequestChat(UnicodeString message, int format);
#undef LANAPI_SLOT
};

extern LANAPI *TheLAN;

extern "C" __declspec(dllimport) int __cdecl iswspace(int ch);

__forceinline int UnicodeString::compareNoCase(const unsigned short *text) const
{
	typedef int (*CompareFn)(
		const StringBase<unsigned short> *, const unsigned short *);
	return ((CompareFn)j_00041f3d)(
		(const StringBase<unsigned short> *)this, text);
}

__forceinline UnicodeString &UnicodeString::append(const unsigned short *text)
{
	typedef UnicodeString &(*AppendFn)(
		UnicodeString *, const unsigned short *);
	return ((AppendFn)j_0002d790)(this, text);
}

void Rva005187E0::wrap(int)
{
	first();
}

void Rva005187E0::first()
{
	UnicodeString text;
	UnicodeString message;
	if (m_chatEntry != 0)
	{
		text.set(GadgetTextEntryGetText(m_chatEntry));
		GadgetTextEntrySetText(m_chatEntry, UnicodeString::TheEmptyString);

		while (text.getLength() && iswspace(text.getCharAt(0)))
			text.set(UnicodeString(text.str() + 1));

		if (text.getLength())
		{
			message.set(text);
			if (message.getCharAt(0) == '/')
			{
				UnicodeString remainder(message.str() + 1);
				UnicodeString token;
				if (remainder.nextToken(&token, 0)
					&& token.compareNoCase(L"me") == 0
					&& text.getLength() >= 3)
				{
						typedef UnicodeString (*GetNameFn)(
						char *);
					message.set(((GetNameFn)j_000351c5)(m_userNamePrefs));
					message.append(remainder.str());
					TheLAN->RequestChat(message, 0);
				}
			}
		}
	}
}
