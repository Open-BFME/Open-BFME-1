// ?d_004b5530@@YAXXZ
// partial score=0.55 date=2026-09-25
// Candidate reconstruction for retail RVA 0x004B5530.
// Identity is supported by BFME callback registration and the ZH twin.
// Keep this trial untracked until the byte probe proves it.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "Common/Language.h"
#include "Gameclient/GameWindowManager.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetSlider.h"

WindowMsgHandledType GadgetHorizontalSliderSystem( GameWindow *window, UnsignedInt msg,
                                                                     WindowMsgData mData1, WindowMsgData mData2 )
{
    SliderData *s = (SliderData *)window->winGetUserData();
    WinInstanceData *instData = window->winGetInstanceData();
    ICoord2D size, childSize, childCenter, childRelativePos;
    window->winGetSize( &size.x, &size.y );
    switch( msg )
    {
        case GBM_SELECTED:
            TheWindowManager->winSendSystemMsg( window->winGetOwner(),
                                                 (GadgetGameMessage)0x4010,
                                                 (WindowMsgData)window, 0 );
            break;

        case GGM_LEFT_DRAG:
        {
            GameWindow *child = window->winGetChild();
            Int x, y, delta;
            Int mousex = mData2 & 0xFFFF;

            window->winGetScreenPosition( &x, &y );
            child->winGetSize( &childSize.x, &childSize.y );
            child->winGetScreenPosition( &childCenter.x, &childCenter.y );
            child->winGetPosition( &childRelativePos.x, &childRelativePos.y );
            childCenter.x += childSize.x / 2;
            childCenter.y += childSize.y / 2;

            if( mousex > x + size.x )
            {
                TheWindowManager->winSendSystemMsg( window, (GadgetGameMessage)0x400D,
                                                     s->maxVal, 0 );
                TheWindowManager->winSendSystemMsg( window->winGetOwner(),
                                                     (GadgetGameMessage)0x400C,
                                                     (WindowMsgData)window, s->maxVal );
                break;
            }
            else if( mousex < x )
            {
                TheWindowManager->winSendSystemMsg( window, (GadgetGameMessage)0x400D,
                                                     s->minVal, 0 );
                TheWindowManager->winSendSystemMsg( window->winGetOwner(),
                                                     (GadgetGameMessage)0x400C,
                                                     (WindowMsgData)window, s->minVal );
                break;
            }

            if( childCenter.x < x + childSize.x / 2 )
            {
                child->winSetPosition( 0, 0 );
                s->position = s->minVal;
            }
            else if( childCenter.x >= x + size.x - childSize.x / 2 )
            {
                Int rightPos = size.x - childSize.x;
                child->winSetPosition( rightPos, 0 );
                s->position = s->maxVal;
            }
            else
            {
                delta = childCenter.x - childSize.x / 2 - x;
                s->position = (Int)(delta / s->numTicks) + s->minVal;
                if( s->position > s->maxVal )
                    s->position = s->maxVal;
                if( s->position < s->minVal )
                    s->position = s->minVal;
            }

            TheWindowManager->winSendSystemMsg( window->winGetOwner(),
                                                 (GadgetGameMessage)0x400C,
                                                 (WindowMsgData)window, s->position );
            break;
        }

        case (GadgetGameMessage)0x400D:
        {
            Int newPos = (Int)mData1;
            GameWindow *child = window->winGetChild();
            if( newPos < s->minVal || newPos > s->maxVal )
                break;
            s->position = newPos;
            newPos = (Int)((newPos - s->minVal) * s->numTicks);
            child->winSetPosition( newPos, 0 );
            break;
        }

        case (GadgetGameMessage)0x400E:
        {
            ICoord2D size;
            GameWindow *child = window->winGetChild();
            window->winGetSize( &size.x, &size.y );
            s->minVal = (Int)mData1;
            s->maxVal = (Int)mData2;
            s->numTicks = (Real)(size.x - HORIZONTAL_SLIDER_THUMB_WIDTH)
                          / (Real)(s->maxVal - s->minVal);
            s->position = s->minVal;
            child->winSetPosition( 0, 0 );
            break;
        }

        case GWM_CREATE:
            break;

        case GWM_DESTROY:
            delete ( (SliderData *)window->winGetUserData() );
            break;

        case GWM_INPUT_FOCUS:
        {
            if( mData1 == FALSE )
                BitClear( instData->m_state, WIN_STATE_HILITED );
            else
                BitSet( instData->m_state, WIN_STATE_HILITED );
            TheWindowManager->winSendSystemMsg( window->winGetOwner(), GGM_FOCUS_CHANGE,
                                                 mData1, window->winGetWindowId() );
            *(Bool *)mData2 = TRUE;
            break;
        }

        case GGM_RESIZED:
        {
            Int height = (Int)mData2;
            s->numTicks = (Real)((Int)mData1 - HORIZONTAL_SLIDER_THUMB_WIDTH)
                          / (Real)(s->maxVal - s->minVal);
            GameWindow *thumb = window->winGetChild();
            if( thumb )
                thumb->winSetSize( HORIZONTAL_SLIDER_THUMB_WIDTH, height );
            break;
        }

        default:
            return MSG_IGNORED;
    }
    return MSG_HANDLED;
}
