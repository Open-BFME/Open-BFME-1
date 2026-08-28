// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/player /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?hasRadar@Player@@QBE_NXZ: Code/GameEngine/Source/Common/RTS/Player.cpp
// readable body of ?hasScience@Player@@QBE_NW4ScienceType@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// readable body of ?isCapableOfPurchasingScience@Player@@QBE_NW4ScienceType@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
#define Matrix4x4 Matrix4  // BFME renamed it
//
// Player radar-cluster field accessors, byte-matched against the reconstructed
// BFME Player layout (reference/shims/player/Common/Player.h). disableRadar
// (retail 0xCC1C0, behind thunk 0x3C2BD) reads m_radarDisabled at [this+0x60],
// m_disableProofRadarCount at [this+0x5c] and m_radarCount at [this+0x58] --
// this header's natural (ZH-derived) layout puts them at 0x4c/0x48/0x44, a
// uniform +0x14 (5 dwords) inserted somewhere between m_playerIndex (proven
// UNSHIFTED at [this+0x24] via the matched getPlayerMask@Player) and
// m_radarCount. See the shim header for the full offset writeup.
//
// hasRadar's own standalone body (0xC9A80, immediately after
// okToPlayRadarEdgeSound's body at 0xC9A20 in the same retail compiland) is a
// pure field read with no external calls, so it lands cleanly. disableRadar/
// enableRadar/addRadar/removeRadar all ALSO call through TheAudio->
// getMiscAudio(), which retail dispatches virtually ([vtbl+0x124]) while the
// current (unshimmed) AudioManager header still declares it as a plain
// non-virtual member -- an AudioManager-side vtable drift outside this
// track's scope (Player-side field reads were proven byte-identical up to
// that point; see reverse/re_attempts.log). Left unconverted rather than
// landed with an unresolved call.
//
// This lives here rather than in Common/RTS/Player.cpp because that TU
// resolves Common/Player.h to the ZH-layout reference header (m_radarDisabled
// @0x4c); the private /Ireference/shims/player above makes only this TU see
// the true BFME offsets, so converting this leaf does not disturb Player.cpp
// (83 matches).
#include "PreRTS.h"
#include "Common/Player.h"

// ?hasRadar@Player@@QBE_NXZ
Bool Player::hasRadar() const
{
	if( m_radarDisabled  && (m_disableProofRadarCount == 0) )
		return FALSE;// Nope, no matter how many you have, if I say no, you don't have it

	// Otherwise, check if I actually do have it.
	return m_radarCount > 0;
}

// hasScience/hasPrereqsForScience have no standalone body proven at this RVA;
// they are defined here ONLY so /O2 inlines them into isCapableOfPurchasingScience
// below exactly as retail does (retail's own body goes straight from the
// hasScience find to the playerHasPrereqsForScience call, no intervening call
// instructions -- see the comment on isCapableOfPurchasingScience). hasScience
// itself has no known standalone retail call site (see reverse/re_attempts.log);
// hasPrereqsForScience already has its own row (Player.cpp, natural header --
// it never dereferences a Player field, so layout drift doesn't affect it).
Bool Player::hasScience(ScienceType t) const
{
	return std::find(m_sciences.begin(), m_sciences.end(), t) != m_sciences.end();
}

Bool Player::hasPrereqsForScience(ScienceType t) const
{
	return TheScienceStore->playerHasPrereqsForScience(this, t);
}

// isCapableOfPurchasingScience's own body (0xCFDF0, behind ILT thunk 0x449e45)
// reads m_sciences.begin()/end() at [this+0x234]/[this+0x238] (inlined
// hasScience) and m_sciencePurchasePoints at [this+0x264] (inlined
// getSciencePurchasePoints) -- both proven in reference/shims/player's
// second BFME-only insertion writeup. TheScienceStore->playerHasPrereqsForScience
// (0xDCDD, inlined from hasPrereqsForScience) and ->getSciencePurchaseCost
// (0x2BFD) are both already pinned in reverse/symbols.csv.
//
// BFME identity differs from the ZH source here: retail has NO
// isScienceDisabled()/isScienceHidden() check between hasScience() and
// hasPrereqsForScience() -- confirmed by exhaustive disassembly of the 110B
// body (0xCFDF0-0xCFE5E), which goes straight from the hasScience find to
// the prereqs call. Written to match retail exactly, not the ZH source.
// ?isCapableOfPurchasingScience@Player@@QBE_NW4ScienceType@@@Z
Bool Player::isCapableOfPurchasingScience(ScienceType science) const
{
	if (science == SCIENCE_INVALID)
	{
		return false;
	}

	if (hasScience(science))
	{
		return false;
	}

	if (!hasPrereqsForScience(science))
	{
		return false;
	}

	Int cost = TheScienceStore->getSciencePurchaseCost(science);
	// purchase cost of zero means "not purchasable!"
	if (cost == 0 || cost > getSciencePurchasePoints())
	{
		return false;
	}

	return true;
}
