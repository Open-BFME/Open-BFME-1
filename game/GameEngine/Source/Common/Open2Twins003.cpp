// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Three preference setters landed as relocation-blind twins of
// game/GameEngine/Source/Common/OptionPreferences_setCampaignDifficulty_Thunk.cpp
// (0x000920F0).  Each differs from the model in one .rdata slot -- the key
// literal -- plus its own EH table address.  Two of the three push the same
// literal, "Color", and are still separate functions at separate addresses.
//
// The declarations are the model's, unchanged.

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: preserve retail's out-of-line pinputs/reference/string call boundaries.

class AsciiString;

#include "string_base.h"

#include "ascii_string.h"

namespace _STL
{
template <typename T> struct less;
template <typename T> class allocator;
template <typename First, typename Second> struct pair;

template <typename Key, typename Value, typename Compare,
          typename Allocator>
class map
{
public:
    Value &operator[](const Key &key);
};
}

typedef _STL::map<AsciiString, AsciiString, _STL::less<AsciiString>,
                  _STL::allocator<_STL::pair<const AsciiString, AsciiString> > >
    PreferenceMap;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences : public PreferenceMap
{
public:
    virtual ~UserPreferences();
};


class Open2Option086F30 : public UserPreferences
{
public:
    virtual ~Open2Option086F30();
    void store(int value);
};

// @?store@Open2Option086F30@@QAEXH@Z 0x00086F30
void Open2Option086F30::store(int value)
{
    AsciiString text;
    text.format("%d", value);
    (*this)["Color"] = text;
}

class Open2Option087010 : public UserPreferences
{
public:
    virtual ~Open2Option087010();
    void store(int value);
};

// @?store@Open2Option087010@@QAEXH@Z 0x00087010
void Open2Option087010::store(int value)
{
    AsciiString text;
    text.format("%d", value);
    (*this)["PlayerTemplate"] = text;
}

class Open2Option0AD8C0 : public UserPreferences
{
public:
    virtual ~Open2Option0AD8C0();
    void store(int value);
};

// @?store@Open2Option0AD8C0@@QAEXH@Z 0x000AD8C0
void Open2Option0AD8C0::store(int value)
{
    AsciiString text;
    text.format("%d", value);
    (*this)["Color"] = text;
}
