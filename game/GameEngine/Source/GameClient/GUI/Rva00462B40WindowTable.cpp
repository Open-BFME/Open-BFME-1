// ?bfmeFinish991@@YAXXZ
// Retail00462B40: retained bfmeFinish991 name is called by matched
// BfmeA991::bfmeGo991A at00465B30. The global table is at VA012F19A4.
// Native insertion00461360 allocates a34-byte node: link4 + key4 + value2C.
// Matched value constructor0045EF90 and map index00461BF0 witness window+10,
// hidden+24 and trailing nontrivial AsciiString+28. Native pair ownership
// preserves the iterator return ABI that a trivial stand-in got wrong.
// Aligned calls independently resolve begin0045FA00 (78B), bucket0045F5C0
// (41B), winIsHidden00478410, winHide00478390 and winSetStatus00478420.
// Both native container dependencies were independently byte-verified.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include "ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

class GameWindow {
public:
    bool winIsHidden();
    int winHide(bool hide);
    unsigned int winSetStatus(unsigned int status);
};

struct WindowRecord {
    unsigned char m_pad00[0x10];
    GameWindow *m_window;
    unsigned char m_pad14[0x10];
    bool m_hidden;
    unsigned char m_pad25[3];
    AsciiString m_name;
};

namespace rts {
template <class T> struct hash {
    unsigned int operator()(T value) const;
};
template <class T> struct equal_to {
    bool operator()(const T &, const T &) const;
};
}

typedef _STL::hash_map<AsciiString, WindowRecord, rts::hash<AsciiString>,
    rts::equal_to<AsciiString> > WindowTable;

WindowTable *const g_windowTable = (WindowTable *)0x012F19A4;

void bfmeFinish991() {
    WindowTable *table = g_windowTable;
    for (WindowTable::iterator it = table->begin(); it != table->end(); ++it) {
        if (!it->second.m_hidden) {
            GameWindow *window = it->second.m_window;
            if (window && !window->winIsHidden()) {
                window->winHide(true);
                window->winSetStatus(0x10000000);
            }
        }
    }
}
