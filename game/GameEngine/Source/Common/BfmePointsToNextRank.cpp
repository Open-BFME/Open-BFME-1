// ?bfmePointsToNextRank@@YAHVGen_uw_00025c1b@@@Z
// Recovered from the retail rank-band walk at 0x005549C0.

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
	int value = bfmeRankPointsFromStats( &stats, stats.m_points );
	int index = 1;
	while ( index < 10 && value >= g_bfmeLimitsDF[ index ] )
		++index;
	if ( index >= 10 )
		return 0;
	int zero;
	int diff;
	diff = g_bfmeLimitsDF[ index ] - value;
	zero = 0;
	int *result = diff < 0 ? &zero : &diff;
	return *result;
}
