// ?bfmePointsToNextRank@@YAHVGen_uw_00025c1b@@@Z
// Recovered from the retail rank-band walk at 0x005549C0.

// Retail's destructor calls land on the five-byte ILT thunk at 0x00025C1B
// (nothing defines the ??1Gen_uw_00025c1b spelling), so the destructor
// reaches it through the thunk's own address.
extern void j_00025c1b();

class Gen_uw_00025c1b
{
public:
	__forceinline ~Gen_uw_00025c1b()
	{
		typedef void ( Gen_uw_00025c1b::*Destroy )();
		union { void ( *fn )(); Destroy call; } destroy = { j_00025c1b };
		( this->*destroy.call )();
	}

	unsigned char m_head[ 0x1C4 ];
	int m_points;
};

// The rank points from stats is the five-byte ILT thunk at 0x00022976 (which
// jumps to the matched body at 0x004DA980).  Retail's own call from this
// function lands on that thunk, and nothing defines the generated
// ?bfmeRankPointsFromStats spelling, so the cdecl call goes through the
// thunk's own address, which is where retail's own call lands.
extern void j_00022976();

// The rank thresholds are the first member of the shared rank-point table,
// retail 0x012F401C (TheRankPointValues).
struct RankPoints
{
	int m_ranks[11];
};

extern RankPoints *TheRankPointValues;

int __cdecl bfmePointsToNextRank( Gen_uw_00025c1b stats )
{
	int value = ((int(__cdecl *)(Gen_uw_00025c1b *, int))j_00022976)(&stats, stats.m_points);
	int index = 1;
	while ( index < 10 && value >= TheRankPointValues->m_ranks[ index ] )
		++index;
	if ( index >= 10 )
		return 0;
	int zero;
	int diff;
	diff = TheRankPointValues->m_ranks[ index ] - value;
	zero = 0;
	int *result = diff < 0 ? &zero : &diff;
	return *result;
}