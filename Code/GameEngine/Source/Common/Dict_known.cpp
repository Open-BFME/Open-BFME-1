// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: clean C++ lift of the inline Dict::known body at 0x000C8CD0.
// Retail calls Dict::getType(key), compares the result with `type`, returns
// the bool equality result, and cleans its two four-byte arguments.  These
// minimal declarations preserve the original enum types and link the call to
// the already matched Dict::getType implementation.
enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
public:
    enum DataType
    {
        DICT_NONE = -1,
        DICT_BOOL = 0,
        DICT_INT,
        DICT_REAL,
        DICT_ASCIISTRING,
        DICT_UNICODESTRING
    };

    DataType getType(NameKeyType key) const;
    bool known(NameKeyType key, DataType type) const;
};

bool Dict::known(NameKeyType key, DataType type) const
{
    return getType(key) == type;
}
