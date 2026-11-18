// cl: /O2 /MD /EHsc-
//
// Team instance-list advance at retail 0x000C8A30 (4 bytes: mov eax,[ecx+14h];
// ret), previously only a gen-shim row.  Matched AIPlayer::isSupplySourceAttacked
// (AIPlayerIsSupplySourceAttacked.cpp), AIPlayer::selectTeamToReinforce and
// retail 0x0032C680 walk a TeamPrototype's team instances by calling ILT
// 0x00022A70, which jumps here, with ECX holding the current Team and the next
// Team returned in EAX.  The `_bfme_` spelling stays opaque: ZH's
// MAKE_DLINK(Team, TeamInstanceList) accessor dlink_next_TeamInstanceList is
// already ledgered at 0x00629E60, and retail has no identical-COMDAT folding,
// so this body's own EA identity is unproven.

class Team
{
public:
	Team *_bfme_nextInInstanceList() const;

private:
	char m_unmodelled[ 0x14 ];
	Team *m_nextInInstanceList; // retail [this+0x14]
};

Team *Team::_bfme_nextInInstanceList() const
{
	return m_nextInInstanceList;
}
