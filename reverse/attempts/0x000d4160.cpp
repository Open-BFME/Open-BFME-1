// ?removePlayerRelationship@Player@@QAE_NPBV1@@Z
// partial score=0.95 date=2026-09-05
// Byte-exact body for ?removePlayerRelationship@Player@@QAE_NPBV1@@Z, retail
// 0x000D4160, 126 bytes.  tools/probe.py reports EXACT (modulo relocation
// slots) when this replaces the existing present-unmatched body at
// Code/GameEngine/Source/Common/RTS/Player.cpp:690.
//
// NOT LANDED, and not for a codegen reason.  Player.cpp hosts 22 gen-funclet
// ledger rows pinned to compiler-local labels (uw_00c30026 cites
// object-symbol=$L113269).  Any edit to the TU renumbers those labels
// ($L113269 became $L113827 here), so add_match reverts on 22 stale pins that
// are byte-for-byte untouched.  Landing this needs those 22 rows re-derived in
// the same commit.  reverse/attempts/0x000d4160.patch is the exact diff.
//
// Near twin of the matched ?removeTeamRelationship@Player@@QAE_NPBVTeam@@@Z at
// 0x000D4200: same shape, with m_playerRelations at Player+0x28c instead of
// m_teamRelations at +0x290, and that->getPlayerIndex() ([that+0x24]) as the
// key instead of getRetailTeamID ([that+0x08]).
//
// The helpers playerRelationsOf and PlayerRelationMapType already exist in
// Player.cpp at lines 620 and 627.

Bool Player::removePlayerRelationship(const Player *that)
{
	// The same two BFME offsets getRelationship above casts for: m_playerRelations
	// at Player+0x28c, and its m_map at +0x04 of that. getPlayerIndex needs no
	// adjustment, since retail reads +0x24 too.
	if (!playerRelationsOf(this)->m_map.empty())
	{
		if (that == NULL)
		{
			playerRelationsOf(this)->m_map.clear();
			return true;
		}
		else
		{
			PlayerRelationMapType::iterator it = playerRelationsOf(this)->m_map.find(that->getPlayerIndex());
			if (it != playerRelationsOf(this)->m_map.end())
			{
				playerRelationsOf(this)->m_map.erase(it);
				return true;
			}
		}
	}
	return false;
}
