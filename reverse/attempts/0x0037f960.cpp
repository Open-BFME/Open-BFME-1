// ??$_S_sort@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@U?$less@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@_STL@@YAXAAV?$list@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@0@U?$less@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@0@@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: STLport list<basic_string>::sort helper, retail 0x0037F960.
// The W3D dependency scanner calls the same list member at 0x0037FCB0.

#include <list>

namespace _STL
{

template <class CharT>
class char_traits
{
};

// Retail's string object occupies 0xd8 bytes in this list node.  The sort
// helper only constructs and destroys the object, so its character operations
// stay outside this body.
template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string(const basic_string &other);
	~basic_string();

	bool operator<(const basic_string &other) const;

private:
	char *m_start;
	char *m_finish;
	char *m_end_of_storage;
	unsigned char m_padding[0xcc];
};

}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	BfmeStdString;
typedef _STL::list<BfmeStdString, _STL::allocator<BfmeStdString> > BfmeStringList;

void BfmeStdStringListSort(BfmeStringList &files)
{
	files.sort();
}
