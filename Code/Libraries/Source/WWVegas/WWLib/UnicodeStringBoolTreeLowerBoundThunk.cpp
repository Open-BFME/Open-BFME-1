// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<UnicodeString, pair<const UnicodeString,Bool>,
// _Select1st<...>, UnicodeStringLessThan, allocator<...>>::_M_lower_bound --
// the LangMap tree also used by LanguageFilter_InsertUnique_0044D960.cpp and
// LanguageFilter_LangMap_M_insert.cpp (same UnicodeString/StringBase/
// UnicodeStringLessThan definitions, verified matching there). The comparator
// calls the already-matched StringBase<wchar_t>::compareNoCaseRaw at
// 0x0009ECA0 through the same zero-sized traits shim those siblings use.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
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
		const WideChar *otherText = other.m_data ? other.m_data->text : (const WideChar *)0x0107388C;
		const int thisLength = m_data ? m_data->length : 0;
		const WideChar *thisText = m_data ? m_data->text : (const WideChar *)0x0107388C;
		const int commonLength = thisLength < otherLength ? thisLength : otherLength;
		int result = ((const Rva0009ECA0NoCaseTraits *)(this + 7))->compareNoCaseRaw(thisText, otherText, commonLength);
		if (result == 0)
			result = thisLength - otherLength;
		return result;
	}

private:
	StringBase<WideChar>::Header *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LanguageFilter.h
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

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
// ?_M_lower_bound@?$_Rb_tree@VUnicodeString@@U?$pair@$$CBVUnicodeString@@_N@_STL@@U?$_Select1st@U?$pair@$$CBVUnicodeString@@_N@_STL@@@3@UUnicodeStringLessThan@@V?$allocator@U?$pair@$$CBVUnicodeString@@_N@_STL@@@3@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBVUnicodeString@@_N@_STL@@@2@ABVUnicodeString@@@Z
Bool BfmeLangMapBoundsAnchor(const LangMapTree &tree, const UnicodeString &key)
{
	return tree.lower_bound(key) != tree.upper_bound(key);
}
