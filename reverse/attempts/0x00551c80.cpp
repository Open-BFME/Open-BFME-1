// ?rva00551c80@BfmeAptScreenOnlineLogin@@QAEX_N@Z
// partial score=0.35 date=2026-09-22
// ?rva00551c80@BfmeAptScreenOnlineLogin@@QAEX_N@Z
// Retail BFME RVA 0x00551C80 (240 bytes), dump d_0054e1e0.asm.
// Identity from prior verdicts (reverse/re_attempts.log): BfmeAptScreenOnlineLogin
// nickname write/refresh/clear. If the embedded m_nickname UnicodeString is
// already empty, the body does nothing. Otherwise, when refresh is true, it
// fetches bfmeGetTextAt74(), translates it into a default-constructed
// AsciiString, hands that plus a fresh copy of the shared empty-string
// constant to the m_state object's bfmeSetRT(), calls an unresolved virtual
// slot on m_state (vtable slot 3 / offset 0xc, no extra args), and forwards
// both AsciiString locals to the still-dump helper at 0x0054FF80. Either way
// (refresh true or false, as long as the initial not-empty check passed) it
// finishes by resetting m_nickname to the shared empty-string constant via
// UnicodeString::set().
// String shape follows reference/shims/stringinline/StringInline.h: the
// by-value canonical model (inline ctor/dtor forwarders to an out-of-line
// StringBase<T>), which documents the exact retail copy-ctor (0x00887B60)
// and dtor (0x00887940) callees this body also calls.
// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef unsigned short UnsignedShort;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

public:
	void set(const StringBase<T> &other);
	void releaseBuffer();

	StringInlineData<T> *m_data;
};

class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() : StringBase<UnsignedShort>() {}
	UnicodeString(const UnicodeString &other) : StringBase<UnsignedShort>(other) {}
	~UnicodeString() {}
	void set(const UnicodeString &other) { StringBase<UnsignedShort>::set(other); }
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	void translate(const UnicodeString &other);
};

// still a dump: 0x0001F91F/0x00025144-class thunk chain; virtual slot ABI
// on this object is unresolved (see re_attempts.log), so only the two
// members this body actually reaches are declared.
class BfmeThingRT
{
public:
	void bfmeSetRT(void *a, void *b);
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
};

extern const unsigned char Rva01336E50Str[];

class BfmeAptScreenOnlineLogin
{
public:
	void rva00551c80(bool refresh);
	UnicodeString bfmeGetTextAt74() const;
	void rva0054ff80(void *a, void *b);

private:
	unsigned char m_pad000[0x3c];
	BfmeThingRT m_state;
	unsigned char m_pad040[0xa8 - 0x3c - sizeof(BfmeThingRT)];
	UnicodeString m_nickname;
};

void BfmeAptScreenOnlineLogin::rva00551c80(bool refresh)
{
	void *data = *(void **)&m_nickname;
	if (data == 0 || *(UnsignedShort *)((char *)data + 4) == 0)
		goto done;

	if (!refresh)
		goto clear;

	{
		UnicodeString text = bfmeGetTextAt74();
		AsciiString ascii;
		ascii.translate(text);

		AsciiString copy(*(const AsciiString *)Rva01336E50Str);

		m_state.bfmeSetRT(&ascii, &m_nickname);
		m_state.slot3();

		rva0054ff80(&ascii, &copy);
	}

clear:
	m_nickname.set(*(const UnicodeString *)Rva01336E50Str);

done:
	return;
}
