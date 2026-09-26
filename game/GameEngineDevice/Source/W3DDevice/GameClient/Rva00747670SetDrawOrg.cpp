// cl: /DNDEBUG /MD /EHsc
//
// Retail RVA 0x00747670 (202 bytes), thiscall (Int xOrg, Int yOrg) -> Bool.
// callers_of finds no named caller and no vtable slot names the method, so
// this lands under an opaque address-derived name per docs/naming_evidence.md
// even though its shape is a strong (1.00 similarity) match for
// WorldHeightMap::setDrawOrg -- inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/
// game/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h:259.
// BFME moved m_drawOriginX/Y/m_drawWidthX/m_drawHeightY to +0x120e0..+0x120ec
// (tools/bfme_layout.py WorldHeightMap witnesses +0x120c8/+0x120d8 for the
// two neighbouring members named in the brief); m_width/m_height stay at
// their ZH offsets +8/+0xc.  The two "if (TheGlobalData && ...)" guards in
// the ZH source collapse to a single outer "if (TheWritableGlobalData)" in
// retail, guarding both the stretch-terrain and draw-entire-terrain checks.

typedef int Int;
typedef bool Bool;

enum
{
	STRETCH_DRAW_WIDTH = 0x41,
	STRETCH_DRAW_HEIGHT = 0x41
};

// this+0x4e/this+0x50 read through TheWritableGlobalData; only these two
// bytes are proven from the disassembly.
class Rva00747670GlobalData
{
public:
	unsigned char m_unreconstructed_00[0x4e];
	Bool m_stretchTerrain;         // +0x4e
	unsigned char m_unreconstructed_4f[1];
	Bool m_drawEntireTerrain;      // +0x50
};

extern Rva00747670GlobalData *TheWritableGlobalData;

class Rva00747670HeightMap
{
public:
	Bool rva00747670( Int xOrg, Int yOrg );

	unsigned char m_unreconstructed_00[8];
	Int m_width;                          // +0x8
	Int m_height;                         // +0xc
	unsigned char m_unreconstructed_10[0x120e0 - 0x10];
	Int m_drawOriginX;                    // +0x120e0
	Int m_drawOriginY;                    // +0x120e4
	Int m_drawWidthX;                     // +0x120e8
	Int m_drawHeightY;                    // +0x120ec
};

// ?rva00747670@Rva00747670HeightMap@@QAE_NHH@Z
Bool Rva00747670HeightMap::rva00747670( Int xOrg, Int yOrg )
{
	Int newX = xOrg;
	Int newY = yOrg;
	Int newWidth = m_drawWidthX;
	Int newHeight = m_drawHeightY;

	if ( TheWritableGlobalData )
	{
		if ( TheWritableGlobalData->m_stretchTerrain )
		{
			newWidth = STRETCH_DRAW_WIDTH;
			newHeight = STRETCH_DRAW_HEIGHT;
		}
		if ( TheWritableGlobalData->m_drawEntireTerrain )
		{
			newWidth = m_width;
			newHeight = m_height;
		}
	}

	if ( newWidth > m_width )
		newWidth = m_width;
	if ( newHeight > m_height )
		newHeight = m_height;

	if ( newX > m_width - newWidth )
		newX = m_width - newWidth;
	if ( newX < 0 )
		newX = 0;

	if ( newY > m_height - newHeight )
		newY = m_height - newHeight;
	if ( newY < 0 )
		newY = 0;

	Bool anythingDifferent = ( m_drawOriginX != newX ) ||
		( m_drawOriginY != newY ) ||
		( m_drawWidthX != newWidth ) ||
		( m_drawHeightY != newHeight );

	if ( anythingDifferent )
	{
		m_drawOriginX = newX;
		m_drawOriginY = newY;
		m_drawWidthX = newWidth;
		m_drawHeightY = newHeight;
		return true;
	}
	return false;
}
