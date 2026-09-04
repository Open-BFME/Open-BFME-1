// ?bfmeRankPointsFromStats@@YAHPAVGen_uw_00025c1b@@H@Z
// partial score=0.6 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: bfmeRankPointsFromStats, retail 0x004DA980, 208 bytes.
// Per-side CalculateRank: wins.find(side) and losses.find(side) weighted by
// TheRankPointValues at g_bfmeLimitsDF, then max(0,) lea-clip.
// Probe: ours=166 retail=208; guards match (id==0 / g_bfmeLimitsDF in ebp)
// then STLport find frame is push-ecx vs retail sub-esp-0xC and two-arg
// thiscall find with hidden iterator slot. Next lever: non-EH map find.

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

int bfmeRankPointsFromStats( Gen_uw_00025c1b *stats, int side )
{
	if ( stats->id == 0 || !g_bfmeLimitsDF )
		return 0;

	int rankPoints = 0;
	PerGeneralMap::iterator it = stats->wins.find( side );
	if ( it != stats->wins.end() )
	{
		int value = it->second;
		rankPoints = (int)( (float)value * g_bfmeLimitsDF->m_winMultiplier );
	}

	it = stats->losses.find( side );
	if ( it != stats->losses.end() )
	{
		int value = it->second;
		rankPoints = (int)( (float)value * g_bfmeLimitsDF->m_lostMultiplier + (float)rankPoints );
	}

	int zero = 0;
	return *( rankPoints < 0 ? &zero : &rankPoints );
}
