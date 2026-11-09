// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

// Open-BFME5: Glo012F1024Entry::select, retail 0x003A9710, 262 bytes.
// The entry owns a vector of 0xDC-byte items. Each item returns its name by
// value, and the selector returns the first item whose name matches the key.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

template <typename T> struct BfmeStringData
{
	char m_pad00[4];
	unsigned short m_length;
	unsigned short m_pad06;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();

	BfmeStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	Int len(void) const { return m_data ? m_data->m_length : 0; }
	const char *str(void) const { return m_data ? m_data->m_text : g_bfmeEmptyAscii; }
	Int compare(const AsciiString &other) const;
};

// Retail reaches the item's name getter (body at 0x003A72F0) through the ILT
// thunk at 0x0000CA95, a defined ?j_0000ca95 row; the body has no name here.
extern void j_0000ca95();

class Glo012F1024Item
{
public:
	char m_bfmeBody[0xDC];
};

class BfmeItemVector
{
public:
	UnsignedInt size(void) const
	{
		Glo012F1024Item *finish = m_bfmeFinish;
		Glo012F1024Item *start = m_bfmeStart;
		return (UnsignedInt)(finish - start);
	}

	Glo012F1024Item *m_bfmeStart;
	Glo012F1024Item *m_bfmeFinish;
};

inline Int AsciiString::compare(const AsciiString &other) const
{
	Int otherLength = other.len();
	const char *otherText = other.str();
	Int thisLength = len();
	const char *thisText = str();
	Int length = thisLength < otherLength ? thisLength : otherLength;
	Int result = memcmp(thisText, otherText, length);
	if (result != 0)
		return result;
	return thisLength - otherLength;
}

class Glo012F1024Entry
{
public:
	Glo012F1024Item *select(AsciiString *key);

private:
	char m_pad00[0x0C];
	BfmeItemVector m_bfmeItems;
};

// ?select@Glo012F1024Entry@@QAEPAVGlo012F1024Item@@PAVAsciiString@@@Z
Glo012F1024Item *Glo012F1024Entry::select(AsciiString *key)
{
	UnsignedInt i = 0;
	for (; i < m_bfmeItems.size(); ++i)
	{
		union { void (*raw)(); AsciiString (Glo012F1024Item::*member)(void); } nameCall;
		nameCall.raw = j_0000ca95;
		if ((m_bfmeItems.m_bfmeStart[i].*nameCall.member)().compare(*key) == 0)
			return m_bfmeItems.m_bfmeStart + i;
	}
	return 0;
}
