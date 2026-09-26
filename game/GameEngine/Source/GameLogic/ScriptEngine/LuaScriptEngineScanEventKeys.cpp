// ?rva002E3360ScanEventKeys@LuaScriptEngine@@QAEXXZ
// The selector pin and the LuaScriptEngine constructor identify this body.
// Retail scans 13 eight-byte event records at this+0x10 and releases the
// AsciiString returned by KEYNAME when the record flag is clear.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

enum NameKeyType
{
    NAMEKEY_INVALID = 0
};

extern AsciiString KEYNAME(NameKeyType key);

struct EventKeyRecord
{
    NameKeyType m_key;
    unsigned char m_active;
    unsigned char m_padding[3];
};

class LuaScriptEngine
{
public:
    void rva002E3360ScanEventKeys();

private:
    unsigned char m_prefix[0x10];
    EventKeyRecord m_events[13];
};

void LuaScriptEngine::rva002E3360ScanEventKeys()
{
    for (int i = 0; i < 13; ++i)
    {
        if (m_events[i].m_active == 0)
        {
            KEYNAME(m_events[i].m_key);
        }
    }
}
