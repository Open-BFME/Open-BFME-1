// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: retail 0x004DA980, 208 bytes. Converted from gen-dump d_004da980.
// Rank points one side contributes: the per-general wins and losses counts
// for that side key, weighted by the rank-point table (m_winMultiplier +0x28,
// m_lostMultiplier +0x2C at retail 0x012F401C, as in CalculateRank) and
// clipped at zero. ILT 0x00022976 routes here; bfmePickBestRankSide and the
// online profile rank tooltip call it per side.

#include <map>

// Retail calls the int-key tree find pinned at ILT 0x00033E9C, whose
// instantiation carries this one-int pod as the mapped type.
struct Gen_t_000a3c70_p4pod
{
	int a[1];
};

typedef std::map<int, Gen_t_000a3c70_p4pod> PerGeneralMap;

class Gen_uw_00025c1b
{
public:
	int id;
	PerGeneralMap wins;
	PerGeneralMap losses;
};

struct RankPoints
{
	int m_ranks[10];
	float m_winMultiplier;
	float m_lostMultiplier;
};

extern RankPoints *TheRankPointValues;

int bfmeRankPointsFromStats( Gen_uw_00025c1b *stats, int side )
{
	if ( stats->id == 0 || !TheRankPointValues )
		return 0;

	int value = 0;
	int winKey = side;
	PerGeneralMap::iterator it = stats->wins.find( winKey );
	if ( it != stats->wins.end() )
		value = it->second.a[0];
	int rankPoints = (int)( (float)value * TheRankPointValues->m_winMultiplier );

	value = 0;
	int lossKey = side;
	it = stats->losses.find( lossKey );
	if ( it != stats->losses.end() )
		value = it->second.a[0];
	rankPoints = (int)( (float)value * TheRankPointValues->m_lostMultiplier + rankPoints );

	int zero = 0;
	return *( rankPoints < 0 ? &zero : &rankPoints );
}
