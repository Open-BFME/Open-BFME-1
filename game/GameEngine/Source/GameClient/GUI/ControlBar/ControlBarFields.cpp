// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/controlbar /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// ControlBar member functions byte-matched against the reconstructed BFME
// field boundary (inputs/reference/shims/controlbar/GameClient/ControlBar.h):
// m_specialPowerShortcutParent@0xFC (ZH header has it at 0x184). The two
// list heads in that shim, m_commandButtons@0x28 and m_commandSets@0x2c,
// are ZH's own offsets — see the shim's header comment for why the earlier
// "BFME moved them" note was a swapped identity, not drift.
//
// They live here rather than in GUI/ControlBar/ControlBar.cpp because that
// TU resolves GameClient/ControlBar.h to the ZH-layout reference header (40+
// already-matched functions there depend on that layout for fields before
// this boundary, which are not yet reconstructed); the private
// /Iinputs/reference/shims/controlbar above makes only this TU see the true BFME
// offset, so converting this leaf here does not disturb ControlBar.cpp.
#include "PreRTS.h"
#include "GameClient/ControlBar.h"
#include "GameClient/GameWindow.h"

// ?hideSpecialPowerShortcut@ControlBar@@QAEXXZ
void ControlBar::hideSpecialPowerShortcut( void )
{
	if( !m_specialPowerShortcutParent )
		return;

	m_specialPowerShortcutParent->winHide( TRUE );

}
