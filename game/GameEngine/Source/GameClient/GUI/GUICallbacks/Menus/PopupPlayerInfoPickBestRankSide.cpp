// cl: /DNDEBUG /MD /EHsc
// Open-BFME: retail 0x004DAA90, 129 bytes. Converted from gen-dump d_004daa90.
// Four calls to bfmeRankPointsFromStats (ILT 0x22976 -> 0x004DA980) with
// side keys 1,0,3,2 then a pair-max tournament that returns 0..3.

class Gen_uw_00025c1b;

int bfmeRankPointsFromStats( Gen_uw_00025c1b *stats, int side );

int bfmePickBestRankSide( Gen_uw_00025c1b *stats )
{
	int side1Points = bfmeRankPointsFromStats( stats, 1 );
	int side0Points = bfmeRankPointsFromStats( stats, 0 );
	int side3Points = bfmeRankPointsFromStats( stats, 3 );
	int side2Points = bfmeRankPointsFromStats( stats, 2 );
	int firstPairSide = ( side1Points >= side0Points );
	int firstPairPoints = *( ( side1Points > side0Points ) ? &side1Points : &side0Points );
	int secondPairSide = 2 + ( side3Points >= side2Points );
	if ( firstPairPoints < *( ( side3Points > side2Points ) ? &side3Points : &side2Points ) )
		return secondPairSide;
	return firstPairSide;
}
