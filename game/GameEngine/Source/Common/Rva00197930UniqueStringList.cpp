// Retail RVA 0x00197930, full 294-byte list append-if-absent body.
// The original owner/method names are unknown. Retail reads the sentinel
// at this+0x0C, traverses two-link nodes, compares four-byte AsciiStrings,
// and allocates a 12-byte node only if no equal string was found.
// The misleading legacy GameSpyGroupRoom copy alias at 0x00887B60 is
// really the already-verified StringBase<char> copy constructor used here.
// Increment precedes the temporary string destructor, as in retail.
// STLport node construction has no catch wrapper; ordinary /EHsc remains.
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <list>
#include "ascii_string.h"
typedef char CheckStringSize[(sizeof(AsciiString) == 4) ? 1 : -1];
typedef char CheckListSize[(sizeof(_STL::list<AsciiString>) == 4) ? 1 : -1];
typedef char CheckNodeSize[(sizeof(_STL::_List_node<AsciiString>) == 12) ? 1 : -1];
inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}
class Rva00197930StringListOwner {
public:
    void appendUnique(const AsciiString &name);
private:
    char m_prefix[0xc];
    _STL::list<AsciiString> m_names;
};
void Rva00197930StringListOwner::appendUnique(const AsciiString &name)
{
    _STL::list<AsciiString>::iterator i=m_names.begin();
    while(i!=m_names.end()) {
        AsciiString current=*i;
        if(name.compare(current)==0)
            return;
        ++i;
    }
    m_names.push_back(name);
}
