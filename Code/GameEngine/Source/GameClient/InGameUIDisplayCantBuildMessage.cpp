// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// InGameUI::displayCantBuildMessage (0x0043E420): slot 24 (+0x60) of
// InGameUI's table 0x00CF5B38, the slot just before beginAreaSelectHint where
// Zero Hour declares it. Zero Hour's body: one GUI label per LegalBuildCode
// through TheInGameUI's message(AsciiString, ...) at vtable +0x30.

#include "ascii_string.h"

// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h
enum LegalBuildCode
{
	LBC_OK = 0,
	LBC_RESTRICTED_TERRAIN,
	LBC_NOT_FLAT_ENOUGH,
	LBC_OBJECTS_IN_THE_WAY,
	LBC_NO_CLEAR_PATH,
	LBC_SHROUD,
	LBC_TOO_CLOSE_TO_SUPPLIES,
	LBC_GENERIC_FAILURE,
};

#define BFME_CANT_BUILD_SLOT(n) virtual void bfmeCantBuildSlot##n() = 0;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	BFME_CANT_BUILD_SLOT(0) BFME_CANT_BUILD_SLOT(1) BFME_CANT_BUILD_SLOT(2) BFME_CANT_BUILD_SLOT(3)
	BFME_CANT_BUILD_SLOT(4) BFME_CANT_BUILD_SLOT(5) BFME_CANT_BUILD_SLOT(6) BFME_CANT_BUILD_SLOT(7)
	BFME_CANT_BUILD_SLOT(8) BFME_CANT_BUILD_SLOT(9) BFME_CANT_BUILD_SLOT(10) BFME_CANT_BUILD_SLOT(11)
	virtual void message( AsciiString stringManagerLabel, ... ) = 0;	///< vtable +0x30
	BFME_CANT_BUILD_SLOT(13) BFME_CANT_BUILD_SLOT(14) BFME_CANT_BUILD_SLOT(15)
	BFME_CANT_BUILD_SLOT(16) BFME_CANT_BUILD_SLOT(17) BFME_CANT_BUILD_SLOT(18) BFME_CANT_BUILD_SLOT(19)
	BFME_CANT_BUILD_SLOT(20) BFME_CANT_BUILD_SLOT(21) BFME_CANT_BUILD_SLOT(22) BFME_CANT_BUILD_SLOT(23)
	virtual void displayCantBuildMessage( LegalBuildCode lbc );	///< vtable +0x60
};

#undef BFME_CANT_BUILD_SLOT

extern InGameUI *TheInGameUI;

// ?displayCantBuildMessage@InGameUI@@UAEXW4LegalBuildCode@@@Z
void InGameUI::displayCantBuildMessage( LegalBuildCode lbc )
{

	switch( lbc )
	{

		//---------------------------------------------------------------------------------------------
		case LBC_RESTRICTED_TERRAIN:
			TheInGameUI->message( "GUI:CantBuildRestrictedTerrain" );
			break;

		//---------------------------------------------------------------------------------------------
		case LBC_NOT_FLAT_ENOUGH:
			TheInGameUI->message( "GUI:CantBuildNotFlatEnough" );
			break;

		//---------------------------------------------------------------------------------------------
		case LBC_OBJECTS_IN_THE_WAY:
			TheInGameUI->message( "GUI:CantBuildObjectsInTheWay" );
			break;

		//---------------------------------------------------------------------------------------------
		case LBC_TOO_CLOSE_TO_SUPPLIES:
			TheInGameUI->message( "GUI:CantBuildTooCloseToSupplies" );
			break;

		//---------------------------------------------------------------------------------------------
		case LBC_NO_CLEAR_PATH:
		  TheInGameUI->message( "GUI:CantBuildNoClearPath" );
			break;

		//---------------------------------------------------------------------------------------------
		case LBC_SHROUD:
			TheInGameUI->message( "GUI:CantBuildShroud" );
			break;

		//---------------------------------------------------------------------------------------------
		case LBC_GENERIC_FAILURE:
		default:

			TheInGameUI->message( "GUI:CantBuildThere" );
			break;

	}  // end switch

}  // end displayCantBuildMessage
