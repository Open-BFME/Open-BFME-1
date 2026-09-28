// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME5: retail 0x0044DB90 (410 bytes), reached through the ILT thunk
// 0x00034EF0 from Drawable::setCaptionText, GameTextManager::parseMapStringFile
// and DisconnectMenu::sendChat.
//
// The class, the map typedef and the comparator are the ones
// UnicodeStringBoolTreeFind.cpp (LangMap _M_find, 0x0044D4C0) and
// LanguageFilter_unHaxor.cpp (0x0044CED0) already carry, so the
// _Rb_tree<UnicodeString, ...> instantiation and the m_wordList offset are the
// byte-verified ones.  Only the string halves are declared here: retail's
// UnicodeString is a StringBase<wchar_t> wrapper whose Header keeps the
// 16-bit length at +4 and the characters at +8 (inputs/reference/shims/
// stringbaseunicode spells the same layout), so getLength() and str() are
// inlined locally to keep the null-data guard and the m_data->data read.
//
// Retail's nextToken takes the separator set as a raw const wchar_t*
// (?nextToken@?$StringBase@G@@QAE_NPAV1@PBG@Z), not a by-value UnicodeString as
// in the ZH header, so the while condition builds the temporary and hands
// nextToken its str() -- which is what puts a construct/destroy pair on every
// iteration of the loop (the jmp at retail +0x13B targets +0x081, inside the
// temporary's constructor).

#include <map>
#include <string.h>

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) WideChar *__cdecl wcscpy(WideChar *dest, const WideChar *src);
extern "C" __declspec(dllimport) WideChar *__cdecl wcsstr(const WideChar *haystack, const WideChar *needle);
__declspec(dllimport) unsigned __cdecl bfmeLenVGI(const unsigned short *s);

// BFME's StringBase keeps the 2-argument set (retail 0x008885C0) and the
// raw-separator nextToken (retail 0x008889B0) out of line; string_base.h
// already declares both with retail's shapes.
#include "string_base.h"

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	explicit UnicodeString(const WideChar *text)
		: StringBase<WideChar>(text) {}
	// The base destructor IS the wide releaseBuffer (the ledger pins
	// ??1?$StringBase@G@@AAE@XZ at retail's 0x008881D0), so retail's three
	// call sites are this one call each -- a body here would double them.
	~UnicodeString() throw() {}

	// retail +0x01E: m_data ? m_data->length : 0, as a 16-bit load
	Int getLength() const
	{
		return m_data ? m_data->length : 0;
	}

	// retail +0x03C: m_data ? m_data->data : the shared empty text
	const WideChar *str() const
	{
		return m_data ? &m_data->data[0] : (const WideChar *)0x0107388C;
	}

	// retail +0x147: the length is fetched through the same null guard, then
	// handed to the out-of-line two-argument set.
	void set(const WideChar *text)
	{
		set(text, text ? (Int)bfmeLenVGI(text) : 0);
	}

	void set(const WideChar *text, Int len)
	{
		StringBase<WideChar>::set(text, len);
	}

	Bool nextToken(UnicodeString *token, const WideChar *delimiters)
	{
		return StringBase<WideChar>::nextToken(token, delimiters);
	}
};

// The DEBUG_LOG / DEBUG_CRASH calls the upstream ZH body wraps the "found in
// bad word list" and "token not found in its own string" cases are compiled out
// here (/DNDEBUG), which is why retail carries no string reference for either.
struct UnicodeStringLessThan
{
	Bool operator()(UnicodeString a, UnicodeString b) const
	{
		return a.compareNoCase(b) < 0;
	}
};

typedef _STL::pair<const UnicodeString, Bool> LangMapPair;
typedef _STL::_Rb_tree<UnicodeString, LangMapPair, _STL::_Select1st<LangMapPair>,
	UnicodeStringLessThan, _STL::allocator<LangMapPair> > LangMap;
typedef LangMap::iterator LangMapIter;

// BFME's SubsystemInterface is a vptr plus one 4-byte member -- retail's
// ??0SubsystemInterface@@QAE@XZ (0x009A1A2B) writes exactly those two words --
// and that 8-byte base is what puts LanguageFilter::m_wordList at this+8, the
// offset retail's own ctor (0x0044E540) and dtor (0x0044E400) both use.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface() {}
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

protected:
	// The member name is the layout witness's (tools/name_oracle.py --class
	// SubsystemInterface --offset 4 -> m_name).  Its type is BFME's 4-byte
	// AsciiString, which no header reachable from this TU declares without
	// redeclaring a covered type, so the slot stays opaque: only its size is
	// load-bearing here.
	struct NameSlot
	{
		void *data;
	} m_name;
};

class LanguageFilter : public SubsystemInterface
{
public:
	void filterLine(UnicodeString &line);

protected:
	// unHaxor is the virtual retail reaches at +0x107 through the ILT thunk
	// 0x0003FC1A; it is declared, not defined, so this body only calls it.
	// (Declared non-virtual: a virtual declaration makes MSVC 7.1 dispatch
	// the call through the vtable and the body stops matching.)
	void unHaxor(UnicodeString &word);

	LangMap m_wordList;
	LangMap m_subWordList;
};

void *__cdecl operator new[](size_t count);
void __cdecl operator delete[](void *memory);

// ?filterLine@LanguageFilter@@QAEXAAVUnicodeString@@@Z
void LanguageFilter::filterLine(UnicodeString &line)
{
	WideChar *buf = new WideChar[line.getLength() + 1];
	wcscpy(buf, line.str());

	UnicodeString newLine(line);
	UnicodeString token(L"");

	while (newLine.nextToken(&token, UnicodeString(L" ;,.!?:=\\/><`~()&^%#\n\t").str())) {
		WideChar *pos = wcsstr(buf, token.str());
		if (pos == NULL) {
			continue;
		}

		Int len = token.getLength();

		unHaxor(token);
		LangMapIter iter = m_wordList.find(token);
		if (iter != m_wordList.end()) {
			for (Int i = 0; i < len; ++i) {
				*pos = L'*';
				++pos;
			}
		}
	}

	line.set(buf);
	delete[] buf;
}
