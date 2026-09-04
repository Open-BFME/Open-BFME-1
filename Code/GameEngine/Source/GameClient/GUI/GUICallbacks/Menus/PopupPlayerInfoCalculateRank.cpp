// cl: /DNDEBUG /MD /EHsc
// Open-BFME: CalculateRank, retail 0x004DA530, 194 bytes. Converted from
// gen-dump d_004da530. Apt Online QuickMatch names this body. BFME keeps the
// ZH wins/losses weighted sum and max(0,) clip but drops duration, disconnect,
// and campaign honor terms. TheRankPointValues lives at g_bfmeLimitsDF
// (m_winMultiplier +0x28, m_lostMultiplier +0x2C).

struct BfmeNode1110
{
	char m_pad[8];
	BfmeNode1110 *m_leftmost;
	char m_pad1[4];
	int m_key;
	int m_value;
};

class PSPlayerStats
{
public:
	int id;
	BfmeNode1110 *wins;
	char m_padWins[8];
	BfmeNode1110 *losses;
};

struct RankPoints
{
	int m_ranks[10];
	float m_winMultiplier;
	float m_lostMultiplier;
};

extern RankPoints *g_bfmeLimitsDF;

BfmeNode1110 *__cdecl bfmeNext1110( BfmeNode1110 *node );

int CalculateRank( const PSPlayerStats &stats )
{
	if ( stats.id == 0 || !g_bfmeLimitsDF )
		return 0;

	int numGames = 0;
	BfmeNode1110 *header = stats.wins;
	BfmeNode1110 *node = header->m_leftmost;
	while ( node != header )
	{
		numGames += node->m_value;
		node = bfmeNext1110( node );
		header = stats.wins;
	}
	int rankPoints = (int)( (float)numGames * g_bfmeLimitsDF->m_winMultiplier );

	numGames = 0;
	header = stats.losses;
	node = header->m_leftmost;
	while ( node != header )
	{
		numGames += node->m_value;
		node = bfmeNext1110( node );
		header = stats.losses;
	}
	rankPoints = (int)( (float)numGames * g_bfmeLimitsDF->m_lostMultiplier + (float)rankPoints );

	int zero = 0;
	return *( rankPoints < 0 ? &zero : &rankPoints );
}
