// ?insert_unique@?$_Rb_tree@VUnicodeString@@U?$pair@$$CBVUnicodeString@@_N@_STL@@U?$_Select1st@U?$pair@$$CBVUnicodeString@@_N@_STL@@@3@UUnicodeStringLessThan@@V?$allocator@U?$pair@$$CBVUnicodeString@@_N@_STL@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBVUnicodeString@@_N@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVUnicodeString@@_N@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBVUnicodeString@@_N@2@@Z
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob1 /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/languagefilter /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport

#define Matrix4x4 Matrix4
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>

typedef bool Bool;

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
    ~StringBase();
    void releaseBuffer();

    __forceinline int compareNoCase(const StringBase<T> &other) const throw()
    {
        const int otherLength = other.m_data ? other.m_data->length : 0;
        const T *otherText = other.m_data ? other.m_data->text : (const T *)L"";
        const int thisLength = m_data ? m_data->length : 0;
        const T *thisText = m_data ? m_data->text : (const T *)L"";
        const int commonLength = thisLength < otherLength ? thisLength : otherLength;
        const int result = compareNoCaseRaw(thisText, otherText, commonLength);
        return result == 0 ? thisLength - otherLength : result;
    }

private:
    int compareNoCaseRaw(const T *, const T *, int) const throw();
    Header *m_data;
};

class UnicodeString : private StringBase<wchar_t>
{
public:
    UnicodeString(const UnicodeString &other) : StringBase<wchar_t>(other) {}
    ~UnicodeString() { StringBase<wchar_t>::releaseBuffer(); }

    int compareNoCase(const UnicodeString &other) const throw()
    {
        return StringBase<wchar_t>::compareNoCase(other);
    }
};

// The caller-facing LangMap declaration uses this exact comparator ABI.  Its
// out-of-line operator is the second comparison in retail; the first comparison
// is the same operation inlined at the tree walk site below.
struct UnicodeStringLessThan
{
    Bool operator()(UnicodeString a, UnicodeString b) const;
};

static __forceinline Bool BfmeLanguageFilterFirstCompare(
    UnicodeString left, UnicodeString right)
{
    return left.compareNoCase(right) < 0;
}

typedef _STL::pair<const UnicodeString, Bool> BfmeLanguageFilterPair;
typedef _STL::_Rb_tree<UnicodeString, BfmeLanguageFilterPair,
    _STL::_Select1st<BfmeLanguageFilterPair>, UnicodeStringLessThan,
    _STL::allocator<BfmeLanguageFilterPair> > BfmeLanguageFilterTree;

// LanguageFilter::init uses m_wordList[uniword], whose STLport map path reaches
// this plain insert_unique specialization.  Keep the vendor tree algorithm and
// its protected layout; only the first comparator is spelled inline so the
// retail raw-compare/second-comparator split remains visible in the source.
template <>
_STL::pair<BfmeLanguageFilterTree::iterator, Bool>
BfmeLanguageFilterTree::insert_unique(const BfmeLanguageFilterPair &value)
{
    _Link_type __y = this->_M_header._M_data;
    _Link_type __x = (_Link_type)__y->_M_parent;
    bool __comp = true;
    while (__x != 0) {
        __y = __x;
        __comp = BfmeLanguageFilterFirstCompare(value.first,
            this->_S_key(__x));
        __x = __comp ? this->_S_left(__x) : this->_S_right(__x);
    }

    iterator __j(__y);
    if (__comp && __j == this->begin())
        return _STL::pair<iterator, Bool>(
            this->_M_insert(__y, __y, value), true);
    if (__comp)
        --__j;
    if (this->_M_key_compare(this->_S_key(__j._M_node), value.first))
        return _STL::pair<iterator, Bool>(
            this->_M_insert(__x, __y, value), true);
    return _STL::pair<iterator, Bool>(__j, false);
}
