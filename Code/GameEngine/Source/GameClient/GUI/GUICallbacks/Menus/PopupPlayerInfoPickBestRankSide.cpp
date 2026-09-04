// cl: /DNDEBUG /MD /EHsc
// Open-BFME: retail 0x004DAA90, 129 bytes. Converted from gen-dump d_004daa90.
// Four calls to bfmeRankPointsFromStats (ILT 0x22976 -> 0x004DA980) with
// side keys 1,0,3,2 then a pair-max tournament that returns 0..3.

class Gen_uw_00025c1b;

int bfmeRankPointsFromStats( Gen_uw_00025c1b *stats, int side );

int bfmePickBestRankSide( Gen_uw_00025c1b *stats )
{
	int p1 = bfmeRankPointsFromStats( stats, 1 );
	int p0 = bfmeRankPointsFromStats( stats, 0 );
	int p3 = bfmeRankPointsFromStats( stats, 3 );
	int p2 = bfmeRankPointsFromStats( stats, 2 );
	int idx0 = ( p1 >= p0 );
	int pair0 = *( ( p1 > p0 ) ? &p1 : &p0 );
	int idx1 = 2 + ( p3 >= p2 );
	if ( pair0 < *( ( p3 > p2 ) ? &p3 : &p2 ) )
		return idx1;
	return idx0;
}
