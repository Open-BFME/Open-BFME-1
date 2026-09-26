// ?d_004da980@@YAXXZ
// partial score=0.86 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <map>

typedef std::map<int, int> PerGeneralMap;

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

extern RankPoints *g_bfmeLimitsDF;

int bfmeRankPointsFromStats( register Gen_uw_00025c1b *stats, register int side )
{
	int rankPoints = 0;
	int zero;
	PerGeneralMap::iterator it;

	if ( stats->id == 0 || !g_bfmeLimitsDF )
		return 0;

	rankPoints = 0;
	int key = side;
	it = stats->wins.find( key );
	if ( it != stats->wins.end() )
	{
		volatile int value = it->second;
		rankPoints = (int)( (float)value * g_bfmeLimitsDF->m_winMultiplier );
	}

	it = stats->losses.find( key );
	if ( it != stats->losses.end() )
	{
		volatile int value = it->second;
		rankPoints = (int)( (float)value * g_bfmeLimitsDF->m_lostMultiplier + (float)rankPoints );
	}

	zero = 0;
	return *( rankPoints < 0 ? &zero : &rankPoints );
}
