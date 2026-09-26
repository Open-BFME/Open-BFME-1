// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/stringbaseascii /Ireference/shims/asciistringsetoutofline /Ireference/shims/fullfade /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/GameWindow.h"

// Vtable 0x0110CB30 slot 2 routes through ILT 0x00043B67 to this body.
// BFME frame 1 shares the scale-up path; retail makes no audio call there.
void ScoreScaleUpTransition::update(Int frame)
{
    m_drawState = -1;
    if (frame < SCORESCALEUPTRANSITION_START || frame > SCORESCALEUPTRANSITION_END)
        return;
    switch (frame)
    {
    case SCORESCALEUPTRANSITION_START:
        if (!m_isForward && m_win)
        {
            m_win->winHide(true);
            m_isFinished = true;
        }
        break;
    case SCORESCALEUPTRANSITION_1:
    case SCORESCALEUPTRANSITION_2:
    case SCORESCALEUPTRANSITION_3:
    case SCORESCALEUPTRANSITION_4:
    case SCORESCALEUPTRANSITION_5:
        if (m_win)
            m_win->winHide(true);
        m_drawState = frame;
        break;
    case SCORESCALEUPTRANSITION_END:
        if (m_isForward && m_win)
        {
            m_win->winHide(false);
            m_isFinished = true;
        }
        break;
    }
}
