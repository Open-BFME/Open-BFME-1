// cl: /DNDEBUG /MD /EHsc
//
// Three preference setters landed as relocation-blind twins of
// Code/GameEngine/Source/Common/OptionPreferences_setCampaignDifficulty_Thunk.cpp
// (0x000920F0).  Each differs from the model in one .rdata slot -- the key
// literal -- plus its own EH table address.  Two of the three push the same
// literal, "Color", and are still separate functions at separate addresses.
//
// The declarations are the model's, unchanged.

// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: preserve retail's out-of-line preference/string call boundaries.

class AsciiString;

template <typename T>
class StringBase
{
    T *m_text;

    friend class AsciiString;
    StringBase(const T *text);

public:
    void set(const StringBase<T> &that);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
    char *m_text;

public:
    AsciiString() { m_text = 0; }
    AsciiString(const char *text)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(text);
    }
    ~AsciiString();
    AsciiString &operator=(const AsciiString &that)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
        return *this;
    }
    void __cdecl format(AsciiString format, ...);
};

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences : public PreferenceMap
{
public:
    virtual ~UserPreferences();
};


// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
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
