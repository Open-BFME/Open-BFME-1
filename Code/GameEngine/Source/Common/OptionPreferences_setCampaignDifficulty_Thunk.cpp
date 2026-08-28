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
class OptionPreferences : public UserPreferences
{
public:
    virtual ~OptionPreferences();
    void setCampaignDifficulty(int value);
};

void OptionPreferences::setCampaignDifficulty(int value)
{
    AsciiString text;
    text.format("%d", value);
    (*this)["CampaignDifficulty"] = text;
}
