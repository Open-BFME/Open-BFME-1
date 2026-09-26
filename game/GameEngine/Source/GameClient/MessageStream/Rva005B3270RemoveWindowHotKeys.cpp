// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#define __PLACEMENT_VEC_NEW_INLINE
#include <map>
#include "PreRTS.h"
#include "Common/AsciiString.h"

class GameWindow;

class HotKey
{
public:
    GameWindow *m_win;
    AsciiString m_key;
};

class HotKeyAsciiStringLess
{
public:
    bool operator()(const AsciiString &left, const AsciiString &right) const
    {
        return left.compare(right) < 0;
    }
};

namespace _STL
{
template <> struct less<AsciiString> : public HotKeyAsciiStringLess
{
};
}

typedef std::map<AsciiString, HotKey> HotKeyTree;

class Rva005B3270Owner
{
public:
    void remove(GameWindow *window);

private:
    char m_head[8];
    HotKeyTree m_hotKeys;
    HotKeyTree m_commandKeys;
};

void Rva005B3270Owner::remove(GameWindow *window)
{
    HotKeyTree::iterator it = m_hotKeys.begin();
    while (it != m_hotKeys.end())
    {
        HotKeyTree::iterator next = it;
        ++next;
        if (it->second.m_win == window)
            m_hotKeys.erase(it);
        it = next;
    }

    it = m_commandKeys.begin();
    while (it != m_commandKeys.end())
    {
        HotKeyTree::iterator next = it;
        ++next;
        if (it->second.m_win == window)
            m_commandKeys.erase(it);
        it = next;
    }
}
