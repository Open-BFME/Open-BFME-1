// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DTerrainVisual@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp
// Open-BFME5: W3DTerrainVisual::W3DTerrainVisual at retail 0x007304E0.
//
// Identity is settled by the base call through the incremental-link thunk to
// 0x00602C70 (already pinned as ??0W3DTerrainVisualBase), by the member
// offsets +0x10/+0x14/+0x18 and the Bool at +0x1C, and by the global zeroed at
// 0x01306D7C (TheWaterRenderObj).
//
// It gets its own TU because BFME's W3DTerrainVisual is 0x20 bytes -- the size
// check in W3DGameClient.cpp asserts that -- while Zero Hour's header adds ten
// AsciiString skybox names whose constructors would put an EH frame on this
// body.  Zero Hour's TerrainVisual derives from Snapshot AND SubsystemInterface,
// which is where the two vftable stores at +0x00 and +0x04 come from, so the
// base stand-in reproduces that pair of polymorphic bases at retail offsets.
//
// STATEMENT ORDER IS THE WHOLE ROW.  This body was closed before on "retail
// writes both vftable pointers AFTER the four cleared fields and MSVC writes
// them first".  MSVC 7.1 does not pin the vftable stores to the top of the
// constructor: it sinks them to just before the first store that leaves the
// object.  Member stores through `this` that precede that statement in SOURCE
// ORDER float above the vftable stores; everything after it stays below.  Zero
// Hour's constructor assigns TheWaterRenderObj third, which splits the member
// group around the vftable pair; retail assigns it last, so the whole member
// group comes first.  No novtable, no volatile, no inlined intermediate base --
// just moving one statement to the end.

class WaterRenderObjClass;
extern WaterRenderObjClass *TheWaterRenderObj;
class BaseHeightMapRenderObjClass;
class WorldHeightMap;
typedef unsigned char Bool;

class W3DTerrainVisualSnapshot { public: virtual void crc(); virtual void xfer(); };
class W3DTerrainVisualSubsystem { public: virtual void init(); virtual void reset(); };

class W3DTerrainVisualBase : public W3DTerrainVisualSnapshot, public W3DTerrainVisualSubsystem
{
public:
	W3DTerrainVisualBase();
	virtual void load();
private:
	char m_baseFields[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainVisual.h
class W3DTerrainVisual : public W3DTerrainVisualBase
{
public:
	W3DTerrainVisual();
	virtual void getTerrainColorAt();
private:
	BaseHeightMapRenderObjClass *m_terrainRenderObject;
	WaterRenderObjClass *m_waterRenderObject;
	WorldHeightMap *m_logicHeightMap;
	Bool m_isWaterGridRenderingEnabled;
};

W3DTerrainVisual::W3DTerrainVisual()
{
	m_terrainRenderObject = 0;
	m_waterRenderObject = 0;
	m_logicHeightMap = 0;
	m_isWaterGridRenderingEnabled = 0;
	TheWaterRenderObj = 0;
}
