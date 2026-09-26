// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Oy-
// stlport
// BFME wildcard comparison; identity from the matched DebugIOFlat::Write caller.
// Retail 0x0088A3A0 is 135 bytes through ret at +0x86 (inventory count was 132).
// Unlike the Zero Hour body, BFME folds ASCII uppercase on the input only.
#include "_pch.h"

#pragma optimize("s", off)
#pragma optimize("t", on)
#pragma optimize("y", off)
bool Debug::SimpleMatch(const char *str, const char *pattern)
{
    for (;;)
    {
        if (*str == 0)
            break;
        if (*pattern == 0)
            break;
        if (*pattern == '*')
            break;

        if (*str >= 'A' && *str <= 'Z')
        {
            if ((*str++ + ('a' - 'A')) != *pattern++)
                return false;
            continue;
        }

        char s = *str;
        char p = *pattern;
        ++pattern;
        ++str;
        if (s == p)
            continue;
        return false;
    }

    if (*pattern == '*')
    {
        ++pattern;
        while (*str)
            if (SimpleMatch(str++, pattern))
                return true;
        return *str == *pattern;
    }
    return *str == *pattern;
}
