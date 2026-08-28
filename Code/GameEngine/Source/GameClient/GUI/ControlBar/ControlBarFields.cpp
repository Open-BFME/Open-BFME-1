// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/controlbar /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?findNonConstCommandSet@ControlBar@@AAEPAVCommandSet@@ABVAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
//
// ControlBar member functions byte-matched against the reconstructed BFME
// field boundary (reference/shims/controlbar/GameClient/ControlBar.h):
// m_specialPowerShortcutParent@0xFC (ZH header has it at 0x184). The two
// list heads in that shim, m_commandButtons@0x28 and m_commandSets@0x2c,
// are ZH's own offsets — see the shim's header comment for why the earlier
// "BFME moved them" note was a swapped identity, not drift.
//
// They live here rather than in GUI/ControlBar/ControlBar.cpp because that
// TU resolves GameClient/ControlBar.h to the ZH-layout reference header (40+
// already-matched functions there depend on that layout for fields before
// this boundary, which are not yet reconstructed); the private
// /Ireference/shims/controlbar above makes only this TU see the true BFME
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

struct BFMEAsciiStringView
{
	BFMEStringHeader *m_data;

	int compare( const BFMEAsciiStringView &string ) const
	{
		const BFMEAsciiStringView *self = this;
		const BFMEAsciiStringView *that = &string;
		int thatLen = that->m_data ? that->m_data->length : 0;
		const char *thatData = that->m_data ? &that->m_data->data[0] : (const char *)"";
		int thisLen = self->m_data ? self->m_data->length : 0;
		const char *thisData = self->m_data ? &self->m_data->data[0] : (const char *)"";
		int n = thisLen < thatLen ? thisLen : thatLen;
		int c = memcmp( thisData, thatData, n );
		if( c != 0 )
			return c;
		return thisLen - thatLen;
	}
};

// m_commandSets@0x2c and the CommandSet/AsciiString layouts are proven by
// the exact 126-byte body at retail RVA 0x4A0270. It is the SET loop, not
// the button loop: it walks its nodes via node+0x60, and retail's
// findCommandSet (0x4A0340) is the body that calls it. Keep the comparison
// in this TU-local view: its source shape mirrors the inline
// AsciiString::compare implementation and emits the retail double null
// checks and sub/mov/test tail.
CommandSet *ControlBar::findNonConstCommandSet( const AsciiString& name )
{
	for( const CommandSet *set = m_commandSets; set; set = set->getNext() )
	{
		const BFMEAsciiStringView &setName = reinterpret_cast<const BFMEAsciiStringView &>( set->getName() );
		const BFMEAsciiStringView &searchName = reinterpret_cast<const BFMEAsciiStringView &>( name );
		if( setName.compare( searchName ) == 0 )
			return const_cast<CommandSet *>( set );
	}

	return NULL;
}

// ?findNonConstCommandButton@ControlBar@@IAEPAVCommandButton@@ABVAsciiString@@@Z
// is the OTHER 126-byte loop, at retail 0x4A01B0, and is still unmatched.
// Compiling the set loop above against m_commandButtons@0x28 / node+0x14
// reproduces retail's instruction sequence there exactly, at the same 126
// bytes, down to the leading `8b 41 28` — and differs only by a register
// permutation (retail parks the node in ebp and materialises the NULL return
// after the pops; MSVC 7.1 here parks it in eax and xors first). Source-shape
// rewrites are not the lever: this same shape DOES match the set loop. Do not
// re-derive the identity — it is pinned by the call graph in the shim header.
