// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/fullfade /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
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
