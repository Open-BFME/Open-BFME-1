// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/radar /Ireference/shims/mouselayout /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/MessageStream.h"
#include "Common/Radar.h"
#include "Common/GlobalData.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Mouse.h"
#include "GameClient/CommandXlat.h"

// BFME interface slices: these offsets differ from the available ZH headers.
// Each used slot is witnessed in this callback; see astra_M/LAYOUTS.md.
class Rva004BFFE0MouseSlots {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void slot0C();
    virtual void slot0D();
    virtual void setCursor(Mouse::MouseCursor cursor);
};
class Rva004BFFE0UISlots {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void slot0C();
    virtual void slot0D();
    virtual void slot0E();
    virtual void slot0F();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot1A();
    virtual void slot1B();
    virtual void slot1C();
    virtual void slot1D();
    virtual void slot1E();
    virtual void slot1F();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot2A();
    virtual void slot2B();
    virtual void slot2C();
    virtual void slot2D();
    virtual void slot2E();
    virtual void slot2F();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot3A();
    virtual void slot3B();
    virtual void slot3C();
    virtual void slot3D();
    virtual void slot3E();
    virtual const DrawableList *getAllSelectedDrawables() const;
    virtual const DrawableList *getAllSelectedLocalDrawables();
};
class Rva004BFFE0ClientSlots {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void slot0C();
    virtual GameMessage::Type evaluateContextCommand(Drawable *, const Coord3D *, CommandTranslator::CommandEvaluateType);
};
class Rva004BFFE0StreamSlots {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void slot0C();
    virtual GameMessage *appendMessage(GameMessage::Type);
};
class Rva004BFFE0ViewSlots {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void slot0C();
    virtual void slot0D();
    virtual void slot0E();
    virtual void slot0F();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void lookAt(const Coord3D *);
};
struct Rva004BFFE0MouseFields { char field00[0x4D40]; int middleState; };
struct Rva004BFFE0CommandFields { char field00[0x3C]; AsciiString m_cursorName; };
struct Rva004BFFE0GlobalFields { char field00[0x60]; Bool m_useAlternateMouse; };

// BFME voice-info appends a position and one opaque word to the ZH fields.
class Rva004BFFE0VoiceInfo : public PickAndPlayInfo {
public: Coord3D m_position; unsigned int field1C;
};

// Retail FunctionLexicon RVA 0x00EA98E8: literal LeftHUDInput, ILT
// 0x000489A0 -> 0x004BFFE0. Source structure derives from the ZH twin.
WindowMsgHandledType ControlBarInput( GameWindow *window, UnsignedInt msg,

																			WindowMsgData mData1, WindowMsgData mData2 )

{

	return MSG_IGNORED;

}

WindowMsgHandledType LeftHUDInput( GameWindow *window, UnsignedInt msg,
																	 WindowMsgData mData1, WindowMsgData mData2 )
{
	
	Player *player = ThePlayerList->getLocalPlayer();

	if( !TheRadar->isRadarForced() && (TheRadar->isRadarHidden() || !player->hasRadar()) )
		return MSG_HANDLED;
	
	if( ((Rva004BFFE0MouseFields *)TheMouse)->middleState == MBS_Down )
		return MSG_IGNORED;

	switch( msg ) 
	{

		case GWM_NONE:
		case GWM_MOUSE_ENTERING:
		case GWM_MOUSE_LEAVING:
		{

			Bool targeting = FALSE;
			const CommandButton *command = TheInGameUI->getGUICommand();
			if( command 
					&& BitTest(command->getOptions(), NEED_TARGET_POS)
                    && (command->getCommandType() == 0x17 || command->getCommandType() == 0x1F || command->getCommandType() == 0x24) )
				targeting = TRUE;

			if (targeting)
                break;
			{
				const DrawableList *drawableList = ((Rva004BFFE0UISlots *)TheInGameUI)->getAllSelectedLocalDrawables();
				Mouse::MouseCursor cur = Mouse::ARROW;

				if (!(drawableList->empty() || msg == GWM_MOUSE_LEAVING)) 
				{
					if (command && command->getCommandType() == 9)
					{
						cur = Mouse::ATTACKMOVETO;
					}
					else
					{
						cur = Mouse::MOVETO;
					}
				}

				((Rva004BFFE0MouseSlots *)TheMouse)->setCursor(cur);

			}  // end if

			return MSG_HANDLED;
		}

		case GWM_MOUSE_POS:
		{

			ICoord2D mouse;
			mouse.x = mData1 & 0xFFFF;
			mouse.y = mData1 >> 16;

			ICoord2D screenPos;
			window->winGetScreenPosition( &screenPos.x, &screenPos.y );

			mouse.x -= screenPos.x;
			mouse.y -= screenPos.y;

			ICoord2D radar;
			if( (TheRadar->isRadarHidden() == FALSE || TheRadar->isRadarForced()) &&
					TheRadar->localPixelToRadar( &mouse, &radar ) )
			{

				const CommandButton *command = TheInGameUI->getGUICommand();
				if( command 
						&& BitTest(command->getOptions(), NEED_TARGET_POS)
                    && (command->getCommandType() == 0x17 || command->getCommandType() == 0x1F || command->getCommandType() == 0x24) )
				{
					Int index = TheMouse->getCursorIndex( ((const Rva004BFFE0CommandFields *)command)->m_cursorName );

					if( index != Mouse::INVALID_MOUSE_CURSOR )
						((Rva004BFFE0MouseSlots *)TheMouse)->setCursor( (Mouse::MouseCursor)index );
					else
						((Rva004BFFE0MouseSlots *)TheMouse)->setCursor( Mouse::CROSS );

				}  // end if
				else
				{
					const DrawableList *drawableList = ((Rva004BFFE0UISlots *)TheInGameUI)->getAllSelectedLocalDrawables();
					Mouse::MouseCursor cur = Mouse::ARROW;

					if (!(drawableList->empty() || msg == GWM_MOUSE_LEAVING)) 
					{
						if (command && command->getCommandType() == 9)
						{
							cur = Mouse::ATTACKMOVETO;
						}
						else
						{
							cur = Mouse::MOVETO;
						}
					}

					((Rva004BFFE0MouseSlots *)TheMouse)->setCursor(cur);
				}

			}  // end if

			break;

		}  // end case mouse position

		case GWM_RIGHT_UP:// Here to eat
		case GWM_LEFT_UP:// Here to eat
			break;

		case GWM_RIGHT_DOWN:
		case GWM_LEFT_DOWN:
		{
			ICoord2D mouse;
			ICoord2D radar;
			ICoord2D size;
			ICoord2D screenPos;
			Coord3D world;

			window->winGetSize( &size.x, &size.y );

			mouse.x = mData1 & 0xFFFF;
			mouse.y = mData1 >> 16;
			
			window->winGetScreenPosition( &screenPos.x, &screenPos.y );

			mouse.x -= screenPos.x;
			mouse.y -= screenPos.y;

			if( (TheRadar->isRadarHidden() == FALSE || TheRadar->isRadarForced()) &&
					TheRadar->localPixelToRadar( &mouse, &radar ) &&
					TheRadar->radarToWorld( &radar, &world ) )
			{

				const DrawableList *drawableList = ((Rva004BFFE0UISlots *)TheInGameUI)->getAllSelectedLocalDrawables(); // locally-owned only
				
				if (	drawableList->empty() 
					||	msg == (((const Rva004BFFE0GlobalFields *)TheGlobalData)->m_useAlternateMouse ? GWM_LEFT_DOWN : GWM_RIGHT_DOWN)	)
				{
					((Rva004BFFE0ViewSlots *)TheTacticalView)->lookAt( &world );
					break;
				}

				const CommandButton *command = TheInGameUI->getGUICommand();
				if( command 
					&& BitTest(command->getOptions(), NEED_TARGET_POS)
                    && (command->getCommandType() == 0x17 || command->getCommandType() == 0x1F || command->getCommandType() == 0x24) 
					)
				{

					((Rva004BFFE0ClientSlots *)TheGameClient)->evaluateContextCommand( NULL, &world, CommandTranslator::DO_COMMAND );

				}  // end if
				else if( command && command->getCommandType() == 9)
				{

					GameMessage *msg = ((Rva004BFFE0StreamSlots *)TheMessageStream)->appendMessage( (GameMessage::Type)0x42F );
					msg->appendLocationArgument( world );

					Rva004BFFE0VoiceInfo info;
                    info.m_position = world;
                    pickAndPlayUnitVoiceResponse(((Rva004BFFE0UISlots *)TheInGameUI)->getAllSelectedDrawables(), (GameMessage::Type)0x42F, &info);
                    TheInGameUI->setGUICommand(NULL);
				}
				else
				{
					GameMessage *newMsg = NULL;

					newMsg = ((Rva004BFFE0StreamSlots *)TheMessageStream)->appendMessage((GameMessage::Type)0x42E);
					newMsg->appendLocationArgument(world);
					Rva004BFFE0VoiceInfo info;
                    info.m_position = world;
                    pickAndPlayUnitVoiceResponse(drawableList, (GameMessage::Type)0x42E, &info);
				
				}  // end else

			}

	break;

		}  // end left down

		default:
			return MSG_IGNORED;

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end LeftHUDInput
