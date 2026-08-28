// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/drawable /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?getID@Drawable@@QBE?AW4DrawableID@@XZ: Code/GameEngine/Source/GameClient/Drawable.cpp
//
// Drawable field accessors, byte-matched against the reconstructed BFME
// Drawable layout (reference/shims/drawable/GameClient/Drawable.h). These
// are the retail bodies the incremental-link thunks jump to.
//
// They live here rather than in GameClient/Drawable.cpp because that TU
// resolves GameClient/Drawable.h to the ZH-layout reference header (m_id at
// the ZH-compiled offset 0x08c); the private /Ireference/shims/drawable
// above makes only this TU see the true BFME offsets, so converting these
// leaves does not disturb Drawable.cpp's existing matches.
#include "PreRTS.h"
#include "GameClient/Drawable.h"

// Retail body at 0x004116B0 (7B): mov eax,[ecx+0x100]; ret. The ledger row
// previously held only the 5-byte E9 thunk at 0x00009B01 that jumps here;
// repointed to the real body when converting from the MASM dump.
// ?getID@Drawable@@QBE?AW4DrawableID@@XZ
DrawableID Drawable::getID( void ) const
{
	return m_id;
}

// Retail body at 0x0077F6B0 (17B): mov eax,[ecx+0x138]; test eax,eax;
// je +4; add eax,0x3c; ret / xor eax,eax; ret. Matches ZH's own
// `m_locoInfo ? &m_locoInfo->m_wheelInfo : NULL` -- DrawableLocoInfo's
// internal layout (vptr + 14 Reals = 0x3c before m_wheelInfo) is unchanged
// from ZH, only the outer Drawable::m_locoInfo pointer moved.
// ?getWheelInfo@Drawable@@QBEPBUTWheelInfo@@XZ
const TWheelInfo *Drawable::getWheelInfo( void ) const
{
	return m_locoInfo ? reinterpret_cast<const TWheelInfo *>(
		reinterpret_cast<const unsigned char *>(m_locoInfo) + 0x3c) : NULL;
}
