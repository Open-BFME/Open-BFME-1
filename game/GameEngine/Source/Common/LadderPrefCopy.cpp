// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Give VC7.1 a declared pair destructor that explicit instantiation can emit.
#define _STLP_TRIVIAL_DESTRUCTOR_BUG
#include <utility>

class AsciiString;
class UnicodeString;

#include "string_base.h"

// Retail copies each string through its matching narrow or wide StringBase body.
class AsciiString : private StringBase<char>
{
public:
    __forceinline AsciiString(const AsciiString &source) : StringBase<char>(source) {}
    ~AsciiString();
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    __forceinline UnicodeString(const UnicodeString &source) : StringBase<unsigned short>(source) {}
    ~UnicodeString();
};

// LadderPreferences::loadProfile fills these same offsets; the names agree
// with the upstream Common/LadderPreferences.h record and its time_t map key.
class LadderPref
{
public:
    __declspec(noinline) LadderPref(const LadderPref &source);

    UnicodeString name;
    AsciiString address;
    unsigned short port;
    long lastPlayDate;
};

// Keep the copy out of the pair constructor, whose retail body calls it at +0x13.
LadderPref::LadderPref(const LadderPref &source)
    : name(source.name), address(source.address), port(source.port), lastPlayDate(source.lastPlayDate)
{
}

typedef std::pair<const long, LadderPref> LadderPrefPair;
template LadderPrefPair::pair(const long &, const LadderPref &);
template LadderPrefPair::~pair();
