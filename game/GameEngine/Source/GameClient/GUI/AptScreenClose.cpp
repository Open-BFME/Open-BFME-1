// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x004629A0, 97 bytes: _bfme_closeAptScreen.  Named APT screen
// destructors reach it through ILT 0x00036485.  It walks the window table at
// 0x012F19A4 with for_each (0x00462540 through ILT 0x00042591), clearing the
// name of every record that carries this screen name, then erases the name
// from the screen-reference table at 0x012F1990 (hashtable::erase 0x00461040
// through ILT 0x0000F547).  Both tables use the types their matched siblings
// witness: WindowTable in Rva00462B40WindowTable.cpp (begin 0x0045FA00) and
// the Rva00461A00 hash in AsciiStringHashErase00461040.cpp.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <algorithm>
#include "ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

namespace rts {
template <class T> struct hash {
    unsigned int operator()(T value) const;
};
template <class T> struct equal_to {
    bool operator()(const T &, const T &) const;
};
}

struct WindowRecord {
    unsigned char m_pad00[0x28];
    AsciiString m_name;
};

typedef _STL::hash_map<AsciiString, WindowRecord, rts::hash<AsciiString>,
    rts::equal_to<AsciiString> > WindowTable;

class Rva00461A00Counted {
public:
    virtual void release(unsigned int deleting);
    int m_references;
};

struct Rva00461A00Mapped {
    Rva00461A00Mapped() : m_counted(0) {}
    Rva00461A00Mapped(const Rva00461A00Mapped &other) : m_counted(other.m_counted)
    {
        if (m_counted)
            ++m_counted->m_references;
    }
    ~Rva00461A00Mapped()
    {
        if (m_counted && --m_counted->m_references <= 0)
            m_counted->release(1);
    }

    Rva00461A00Counted *m_counted;
};

typedef _STL::hash_map<AsciiString, Rva00461A00Mapped, rts::hash<AsciiString>,
    _STL::equal_to<AsciiString> > AptScreenRefTable;

// The for_each functor at 0x00462540: clears the name of each record whose
// name equals the closed screen's.
struct NameClearFunctor00462540 {
    NameClearFunctor00462540(const AsciiString &name) : m_name(name) {}
    void operator()(_STL::pair<const AsciiString, WindowRecord> &record)
    {
        if (record.second.m_name == m_name)
            record.second.m_name.clear();
    }
    AsciiString m_name;
};

WindowTable *const g_windowTable = (WindowTable *)0x012F19A4;
AptScreenRefTable *const g_theAptScreenRefMap = (AptScreenRefTable *)0x012F1990;

void _bfme_closeAptScreen(const AsciiString &name)
{
    _STL::for_each(g_windowTable->begin(), g_windowTable->end(), NameClearFunctor00462540(name));
    g_theAptScreenRefMap->erase(name);
}
