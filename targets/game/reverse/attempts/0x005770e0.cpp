// ?_bfme_populateMultiPlayer@BfmeAptScreenScoreScreen@@QAEXH@Z
// partial score=0.2 date=2026-09-10
// Complete ScoreScreen reconstruction candidate for retail RVA 0x005770E0.
// This fragment is intended to be resumed in the existing ScoreScreen.cpp TU.
struct BfmeScoreObject { char m_pad[ 0x18 ]; Int m_order; };
struct BfmeScoreEntry
{
	BfmeScoreObject *m_object;
	Player *m_player;
	Int m_teamScore;
	Int m_score;
};
struct BfmeScoreEntryLess
{
	void *m_state;
	Bool operator()( const BfmeScoreEntry *left,
		const BfmeScoreEntry *right ) const;
	Bool operator()( const BfmeScoreEntry &left,
		const BfmeScoreEntry &right ) const
	{
		return operator()( &left, &right );
	}
};
struct BfmeScoreGameSlotLayout
{
	char m_pad[ 0x2C ];
	AsciiString m_internalPlayerName;
};
struct BfmeScorePlayerLayout
{
	char m_pad[ 0x230 ];
	Team *m_team;
};
class BfmeAptScreenScoreScreen
{
public:
	void _bfme_populateMultiPlayer( Int type );
	void _bfme_addPlayerTable( Player *player, GameSlot *slot, Int row );
private:
	char m_unmodelled_prefix[ 0x25C ];
	Int m_type;
	char m_unmodelled_between[ 0x10 ];
	Int m_teamBreakWords[ 2 ];
};
static __forceinline ScoreKeeper *bfmeScoreKeeper( Player *player )
{
	return (ScoreKeeper *)( (char *)player + 0x348 );
}
static __forceinline Team *bfmeScoreTeam( Player *player )
{
	return ( (BfmeScorePlayerLayout *)player )->m_team;
}
void BfmeAptScreenScoreScreen::_bfme_populateMultiPlayer( Int type )
{
	m_type = type;
	std::vector<BfmeScoreEntry> scores;
	scores.reserve( 8 );
	for( Int i = 0; i < 8; ++i )
	{
		GameSlot *slot = TheGameInfo->getSlot( i );
		if( slot->isOccupied() )
		{
			AsciiString playerName =
				( (BfmeScoreGameSlotLayout *)slot )->m_internalPlayerName;
			if( !playerName.isEmpty() )
			{
				Player *player = ThePlayerList->findPlayerWithNameKey(
					TheNameKeyGenerator->nameToKey( playerName.str() ) );
				if( player != 0 && !player->isPlayerObserver() )
				{
					BfmeScoreEntry entry =
						{ (BfmeScoreObject *)slot, player, 0, 0 };
					scores.push_back( entry );
				}
			}
		}
	}
	for( BfmeScoreEntry *entry = scores.begin();
		entry != scores.end(); ++entry )
	{
		Int score = bfmeScoreKeeper( entry->m_player )->calculateScore();
		entry->m_teamScore = score;
		entry->m_score = score;
		for( BfmeScoreEntry *other = scores.begin(); other != entry; ++other )
		{
			if( entry->m_player->getRelationship( bfmeScoreTeam( other->m_player ) ) == ALLIES &&
				other->m_player->getRelationship( bfmeScoreTeam( entry->m_player ) ) == ALLIES )
				entry->m_teamScore +=
					bfmeScoreKeeper( other->m_player )->calculateScore();
		}
	}
	BfmeScoreEntryLess less = { 0 };
	std::sort( scores.begin(), scores.end(), less );
	m_teamBreakWords[ 0 ] = 0;
	m_teamBreakWords[ 1 ] = 0;
	unsigned char *teamBreak = (unsigned char *)m_teamBreakWords;
	Player *previous = 0;
	Int row = 0;
	for( BfmeScoreEntry *entry = scores.begin();
		entry != scores.end(); ++entry )
	{
		if( previous != 0 &&
			( entry->m_player->getRelationship( bfmeScoreTeam( previous ) ) != ALLIES ||
				previous->getRelationship( bfmeScoreTeam( entry->m_player ) ) != ALLIES ) )
			teamBreak[ row ] = 1;
		_bfme_addPlayerTable( entry->m_player,
			(GameSlot *)entry->m_object, row );
		previous = entry->m_player;
		++row;
	}
	if( row < 8 )
		teamBreak[ row ] = 1;
}
