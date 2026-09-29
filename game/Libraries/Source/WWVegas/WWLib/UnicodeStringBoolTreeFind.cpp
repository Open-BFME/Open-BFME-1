// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<UnicodeString, pair<const UnicodeString,Bool>,
// _Select1st<...>, UnicodeStringLessThan, allocator<...>>::_M_find -- the
// LangMap tree of LanguageFilter, same UnicodeString/StringBase/
// UnicodeStringLessThan definitions as the already-matched
// UnicodeStringBoolTreeLowerBoundThunk.cpp (_M_lower_bound, 0x0044D370) and
// LanguageFilter_LangMap_M_insert.cpp, both verified against retail. The
// in-loop comparison is the same already-matched StringBase<wchar_t>::
// compareNoCaseRaw at 0x0009ECA0 through the same zero-sized traits shim those
// siblings use; the post-loop _M_key_compare goes out of line to the matched
// UnicodeStringLessThan body at 0x0044D2A0.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;

extern const unsigned short BFMEEmptyUnicodeString;

struct Rva0009ECA0NoCaseTraits
{
	int compareNoCaseRaw(const WideChar *a, const WideChar *b, int n) const throw();
};

class UnicodeString;

template <typename T>
class StringBase
{
	friend class UnicodeString;

public:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};

	StringBase(const StringBase<T> &);
	~StringBase() throw();

private:
	Header *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(
			*(const StringBase<WideChar> *)&other);
	}
	~UnicodeString();

	int compareNoCase(const UnicodeString &other) const throw()
	{
		const int otherLength = other.m_data ? other.m_data->length : 0;
		const WideChar *otherText = other.m_data ? other.m_data->text : &BFMEEmptyUnicodeString;
		const int thisLength = m_data ? m_data->length : 0;
		const WideChar *thisText = m_data ? m_data->text : &BFMEEmptyUnicodeString;
		const int commonLength = thisLength < otherLength ? thisLength : otherLength;
		// the receiver base is 8 pointers above the string object in this body
		// (retail `lea ecx, [esp + 0x40]`); the _M_lower_bound TU at 0x0044D370
		// needs 7 for the identical compareNoCase call.  Same zero-sized traits
		// shim, one pointer apart, both byte-verified.
		int result = ((const Rva0009ECA0NoCaseTraits *)(this + 8))->compareNoCaseRaw(thisText, otherText, commonLength);
		if (result == 0)
			result = thisLength - otherLength;
		return result;
	}

private:
	StringBase<WideChar>::Header *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LanguageFilter.h
struct UnicodeStringLessThan
{
	Bool operator()(UnicodeString a, UnicodeString b) const
	{
		return a.compareNoCase(b) < 0;
	}
};

typedef _STL::pair<const UnicodeString, Bool> LangMapPair;
typedef _STL::_Rb_tree<UnicodeString, LangMapPair, _STL::_Select1st<LangMapPair>,
	UnicodeStringLessThan, _STL::allocator<LangMapPair> > LangMapTree;

// find is public; the _M_find helper it calls is not, so reaching the tree
// through the public member is what emits it.
// ??$_M_find@VUnicodeString@@@?$_Rb_tree@VUnicodeString@@U?$pair@$$CBVUnicodeString@@_N@_STL@@U?$_Select1st@U?$pair@$$CBVUnicodeString@@_N@_STL@@@3@UUnicodeStringLessThan@@V?$allocator@U?$pair@$$CBVUnicodeString@@_N@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVUnicodeString@@_N@_STL@@@1@ABVUnicodeString@@@Z
void BfmeLangMapFindAnchor(const LangMapTree &tree, const UnicodeString &key)
{
	tree.find(key);
}
