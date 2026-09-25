// ?xfer@W3DTerrainVisual@@MAEXPAVXfer@@@Z
// partial score=0.98 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System
// W3DTerrainVisual::xfer, retail 0x007318A0 (259 bytes): slot 3 (BFME's
// Snapshot xfer slot) of W3DTerrainVisual's vftable 0x011212F0, the only table
// holding it. Zero Hour W3DTerrainVisual.cpp's xfer, reshaped the BFME way: the
// base-class xfer comes first and everything else is skipped for a light CRC,
// the version is 1 so the height map and the render object's snapshot are
// unconditional, and the height map holds two bytes per cell.
#include "xfer.h"
#include "snapshot.h"

struct BfmeFormattedText
{
	void *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

// The water render object is xferred through a Snapshot at offset 0.
class W3DTerrainVisualWater : public Snapshot
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MapObject.h
class WorldHeightMap
{
public:
	int getXExtent() const { return m_width; }
	int getYExtent() const { return m_height; }
	unsigned char *getDataPtr() { return m_data; }

private:
	unsigned char m_pad00[0x08];
	int m_width;						// +0x08
	int m_height;						// +0x0C
	unsigned char m_pad10[0x24 - 0x10];
	unsigned char *m_data;				// +0x24
};

// The terrain render object: BFME's load-time refresh is its virtual slot 138,
// and its Snapshot base sits at +0xCC.
class W3DTerrainVisualRenderObjectHead
{
public:
#define S(n) virtual void slot##n();
#define S10(n) S(n##0) S(n##1) S(n##2) S(n##3) S(n##4) S(n##5) S(n##6) S(n##7) S(n##8) S(n##9)
	S10(0) S10(1) S10(2) S10(3) S10(4) S10(5) S10(6) S10(7) S10(8) S10(9)
	S10(10) S10(11) S10(12)
	S(130) S(131) S(132) S(133) S(134) S(135) S(136) S(137)
#undef S10
#undef S
	virtual void slot138(bool value);

private:
	unsigned char m_pad04[0xCC - 0x04];
};

class W3DTerrainVisualRenderObject : public W3DTerrainVisualRenderObjectHead, public Snapshot
{
};

class W3DTerrainVisualBase
{
protected:
	virtual void xfer(Xfer *xfer);
};

class W3DTerrainVisual : public W3DTerrainVisualBase
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad04[0x10 - 0x04];
	W3DTerrainVisualRenderObject *m_terrainRenderObject;	// +0x10
	W3DTerrainVisualWater *m_waterRenderObject;			// +0x14
	WorldHeightMap *m_logicHeightMap;					// +0x18
	bool m_isWaterGridRenderingEnabled;					// +0x1C
};

// ?xfer@W3DTerrainVisual@@MAEXPAVXfer@@@Z
void W3DTerrainVisual::xfer( Xfer *xfer )
{
	// extend base class
	W3DTerrainVisualBase::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 1;
	*xfer == version;

	// flag for whether or not the water grid is enabled
	bool gridEnabled = m_isWaterGridRenderingEnabled;
	*xfer == gridEnabled;
	if( gridEnabled != m_isWaterGridRenderingEnabled )
	{
		BfmeFormattedText error;
		bfmeFormatText( &error, 5, 0 );
		_CxxThrowException( &error, &g_rva005c5100ThrowInfo );
	}

	// xfer grid data if enabled
	if( gridEnabled )
		*xfer == *m_waterRenderObject;

	{
		// Write out the terrain height data.
		unsigned char *data = m_logicHeightMap->getDataPtr();
		int len = m_logicHeightMap->getXExtent() * m_logicHeightMap->getYExtent() * 2;
		int xferLen = len;
		*xfer == xferLen;
		if( len > xferLen )
			len = xferLen;
		xfer->XferRawBytes( data, len );
		if( xfer->IsLoading() )
		{
			// Update the display height map.
			m_terrainRenderObject->slot138( true );
		}
	}
	Snapshot *terrain = m_terrainRenderObject;
	*xfer == *terrain;
}
