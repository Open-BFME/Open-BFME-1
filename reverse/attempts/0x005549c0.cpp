// ?bfmePointsToNextRank@@YAHVGen_uw_00025c1b@@@Z
// partial score=0.72 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Remaining points to the next rank band.  Walks g_bfmeLimitsDF the same
// way bfmeBand does after a helper reads the player's points out of the
// by-value stats object.

class Gen_uw_00025c1b
{
public:
	~Gen_uw_00025c1b();

	unsigned char m_head[ 0x1C4 ];
	int m_points;
};

int bfmeRankPointsFromStats( Gen_uw_00025c1b *stats, int points );

extern int *g_bfmeLimitsDF;

int __cdecl bfmePointsToNextRank( Gen_uw_00025c1b stats )
{
	int zero = 0;
	int value = bfmeRankPointsFromStats( &stats, stats.m_points );
	int index = 1;
	while ( index < 10 && value >= g_bfmeLimitsDF[ index ] )
		++index;
	if ( index >= 10 )
		return 0;
	int diff = g_bfmeLimitsDF[ index ] - value;
	return diff < 0 ? zero : diff;
}
