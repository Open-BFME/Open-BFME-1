// ?isCliffMappedTexture@Rva00022034WorldHeightMapThunk@@QAE_NHH@Z
// Retail 0x00022034 jumps to WorldHeightMap::isCliffMappedTexture at 0x00728250.

class WorldHeightMap
{
public:
	bool isCliffMappedTexture( int x, int y );
};

class Rva00022034WorldHeightMapThunk
{
public:
	bool isCliffMappedTexture( int x, int y );
};

bool Rva00022034WorldHeightMapThunk::isCliffMappedTexture( int x, int y )
{
	return ( (WorldHeightMap *)this )->isCliffMappedTexture( x, y );
}
