// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc /Iinputs/reference/shims/display /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "GameClient/ControlBarResizer.h"

AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

template <>
int StringBase<char>::compare(const char *text, int length) const
{
    const int ownLength = m_data ? m_data->length : 0;
    const char *ownText = m_data ? m_data->data : "";
    int result = memcmp(ownText, text, ownLength < length ? ownLength : length);
    if (result == 0)
        result = ownLength - length;
    return result;
}

template <>
int StringBase<char>::compare(const StringBase<char> &text) const
{
    const int length = text.m_data ? text.m_data->length : 0;
    const char *data = text.m_data ? text.m_data->data : "";
    return compare(data, length);
}

ResizerWindow *ControlBarResizer::findResizerWindow(AsciiString name)
{
    ResizerWindowList::iterator it = m_resizerWindowsList.begin();
    while (it != m_resizerWindowsList.end())
    {
        ResizerWindow *window = *it;
        if (!window)
        {
            ++it;
            continue;
        }
        if (window->m_name.compare(name) == 0)
            return window;
        ++it;
    }
    return 0;
}
