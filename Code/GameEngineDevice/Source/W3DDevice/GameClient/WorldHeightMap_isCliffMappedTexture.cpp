// cl: /DNDEBUG /MD /EHsc
// readable body of ?isCliffMappedTexture@WorldHeightMap@@QAE_NHH@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp

// WorldHeightMap::isCliffMappedTexture, retail 0x00728250. No calls: the cell
// index is built from the map origin at +0x120E0/+0x120E4 and the row stride at
// +0x08, bounds-checked against the cell count at +0x20 - signed at both ends,
// which is the `js' and the `jge' - and used to index the pointer table at
// +0x94. The answer is whether that entry is non-null.

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	Bool isCliffMappedTexture( Int x, Int y );

private:
	unsigned char m_unmodelled_00[ 8 ];
	Int m_stride;							// +0x08
	unsigned char m_unmodelled_0C[ 0x20 - 0x0C ];
	Int m_cellCount;						// +0x20
	unsigned char m_unmodelled_24[ 0x94 - 0x24 ];
	void **m_cliffInfo;						// +0x94
	unsigned char m_unmodelled_98[ 0x120E0 - 0x98 ];
	Int m_originX;							// +0x120E0
	Int m_originY;							// +0x120E4
};

// ?isCliffMappedTexture@WorldHeightMap@@QAE_NHH@Z
Bool WorldHeightMap::isCliffMappedTexture( Int x, Int y )
{
	Int index = ( m_originY + y ) * m_stride + m_originX + x;

	if( index < 0 || index >= m_cellCount )
		return false;

	return m_cliffInfo[ index ] != 0;
}
