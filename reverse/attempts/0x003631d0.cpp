// ?d_003631d0@@YAXXZ
// partial score=0.85 date=2026-08-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#include "Common/AsciiString.h"
#include <vector>

struct Elem003631D0
{
    char pad0[0x0C];
    AsciiString name;
    char pad1[0x58 - 0x0C - sizeof(AsciiString)];
};

struct Container003631D0
{
    char pad[0x18];
    Elem003631D0 *m_begin;
    Elem003631D0 *m_end;

    Elem003631D0 *find(AsciiString const &s);
};

Elem003631D0 *Container003631D0::find(AsciiString const &s)
{
    int n = (int)((char *)m_end - (char *)m_begin) / (int)sizeof(Elem003631D0);
    for (int i = 0; i < n; ++i) {
        Elem003631D0 *p = m_begin + i;
        AsciiString tmp = p->name;
        if (tmp.compare(s) == 0)
            return p;
    }
    return 0;
}
