// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/displaystring /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GadgetListBox.h"

// Retail 0x004B5AA0 is a thiscall adapter with four stack arguments. The
// owner has not been identified, so its class, field and method stay opaque.
// The three winGetUserData calls, the signed 16-bit bounds check and both
// gadget callees are witnessed in the retail body.
class Rva004B5AA0
{
public:
	Int m( const Image *image, Int height, Int width, Color color );
	GameWindow *m_00;
};

Int Rva004B5AA0::m( const Image *image, Int height, Int width, Color color )
{
	if( !m_00 )
		return -1;

	GameWindow *listbox = *(GameWindow **)((char *)m_00->winGetUserData() + 8);
	void *data = (*(GameWindow **)((char *)m_00->winGetUserData() + 8))->winGetUserData();
	if( *(Short *)((char *)data + 0x2c) >= *(Short *)data )
		GadgetListBoxSetListLength( listbox, 2 * (Int)*(Short *)data );

	return GadgetListBoxAddEntryImage( listbox, image, -1, 0, width, height, TRUE, color );
}
