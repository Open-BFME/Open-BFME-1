// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?setCommandBarBorder@ControlBar@@AAEXPAVGameWindow@@W4CommandButtonMappedBorderType@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// Lift the ControlBar::setCommandBarBorder naked dump to clean C++.
//
// Zero Hour's ControlBar.cpp body with one BFME addition: a fifth border type.
// Retail's jump table covers switch values 1 through 5 and is an identity map,
// so the case bodies are laid out in source order and the fifth follows ZH's
// four.
//
// The colour members are not declared in the enum's order -- the bodies read
// this+0x280, +0x288, +0x284, +0x28C and +0x290 in case order -- so the offsets
// are proven while the pairing of ZH's names to them rests on BFME having kept
// the enum order and appended to it. The fifth type has no ZH name at all, so it
// carries a _bfme_ one.
//
// GadgetButtonSetBorder's third argument is defaulted in ZH's four cases and
// passed explicitly in the default arm; retail pushes it every time, which is
// what a defaulted argument looks like from the outside.

typedef int Int;
typedef unsigned int Color;

enum { GAME_COLOR_UNDEFINED = 0xFFFFFF };

enum CommandButtonMappedBorderType
{
	COMMAND_BUTTON_BORDER_NONE = 0,
	COMMAND_BUTTON_BORDER_BUILD,
	COMMAND_BUTTON_BORDER_UPGRADE,
	COMMAND_BUTTON_BORDER_ACTION,
	COMMAND_BUTTON_BORDER_SYSTEM,
	COMMAND_BUTTON_BORDER_BFME_FIFTH
};

class GameWindow;

void GadgetButtonSetBorder(GameWindow *button, Color color, Int enable);	///< ILT thunk at 0x00002982

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
private:
	void setCommandBarBorder(GameWindow *button, CommandButtonMappedBorderType type);

	unsigned char m_unreconstructed_00[0x280];
	Color m_commandButtonBorderBuildColor;				///< retail this+0x280
	Color m_commandButtonBorderActionColor;				///< retail this+0x284
	Color m_commandButtonBorderUpgradeColor;			///< retail this+0x288
	Color m_commandButtonBorderSystemColor;				///< retail this+0x28C
	Color m_bfmeCommandButtonBorderFifthColor;			///< retail this+0x290
};

// ?setCommandBarBorder@ControlBar@@AAEXPAVGameWindow@@W4CommandButtonMappedBorderType@@@Z
void ControlBar::setCommandBarBorder( GameWindow *button, CommandButtonMappedBorderType type)
{
	if(!button)
		return;

	switch( type )
	{
		case COMMAND_BUTTON_BORDER_BUILD:
		{
			GadgetButtonSetBorder(button, m_commandButtonBorderBuildColor, 1);
			break;
		}
		//-------------------------------------------------------------------------------------------------
		case COMMAND_BUTTON_BORDER_UPGRADE:
		{
			GadgetButtonSetBorder(button, m_commandButtonBorderUpgradeColor, 1 );
			break;
		}
		//-------------------------------------------------------------------------------------------------
		case COMMAND_BUTTON_BORDER_ACTION:
		{
			GadgetButtonSetBorder(button, m_commandButtonBorderActionColor, 1);
			break;
		}
		//-------------------------------------------------------------------------------------------------
		case COMMAND_BUTTON_BORDER_SYSTEM:
		{
			GadgetButtonSetBorder(button, m_commandButtonBorderSystemColor, 1);
			break;
		}
		//-------------------------------------------------------------------------------------------------
		case COMMAND_BUTTON_BORDER_BFME_FIFTH:
		{
			GadgetButtonSetBorder(button, m_bfmeCommandButtonBorderFifthColor, 1);
			break;
		}

		//-------------------------------------------------------------------------------------------------
		case COMMAND_BUTTON_BORDER_NONE:
		default:
			GadgetButtonSetBorder(button, GAME_COLOR_UNDEFINED, 0);
	}
}
