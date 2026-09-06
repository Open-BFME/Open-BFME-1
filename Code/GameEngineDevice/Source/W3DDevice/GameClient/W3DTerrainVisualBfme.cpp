// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DTerrainVisual@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp
// readable body of ?getWaterGridHeight@W3DTerrainVisual@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp
// readable body of ?setRawMapHeight@W3DTerrainVisual@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp
//
// The constructor (retail 0x007304E0) and the two overrides that use what it
// sets up: getWaterGridHeight (0x00730B60) and setRawMapHeight (0x00730BD0).
// Three files carried three copies of a class 0x20 bytes long, and only the
// constructor's copy said where the 0x10 bytes ahead of the members come from --
// the other two spelled them `unsigned char m_basePadding[0x0C]` after a lone
// virtual, which is the same 0x10 bytes and says nothing about them. One
// declaration, with the bases the constructor proves and the member types the
// two overrides prove.
//
// Identity of the constructor is settled by the base call through the
// incremental-link thunk to 0x00602C70 (already pinned as
// ??0W3DTerrainVisualBase), by the member offsets +0x10/+0x14/+0x18 and the
// Bool at +0x1C, and by the global zeroed at 0x01306D7C (TheWaterRenderObj).
//
// The three bodies get their own TU rather than joining W3DTerrainVisual.cpp
// because BFME's W3DTerrainVisual is 0x20 bytes -- the size check in
// W3DGameClient.cpp asserts that -- while Zero Hour's header adds ten
// AsciiString skybox names whose constructors would put an EH frame on the
// constructor. Zero Hour's TerrainVisual derives from Snapshot AND
// SubsystemInterface, which is where the two vftable stores at +0x00 and +0x04
// come from, so the base stand-in reproduces that pair of polymorphic bases at
// retail offsets.
//
// STATEMENT ORDER IS THE WHOLE CONSTRUCTOR. It was closed before on "retail
// writes both vftable pointers AFTER the four cleared fields and MSVC writes
// them first". MSVC 7.1 does not pin the vftable stores to the top of the
// constructor: it sinks them to just before the first store that leaves the
// object. Member stores through `this` that precede that statement in SOURCE
// ORDER float above the vftable stores; everything after it stays below. Zero
// Hour's constructor assigns TheWaterRenderObj third, which splits the member
// group around the vftable pair; retail assigns it last, so the whole member
// group comes first. No novtable, no volatile, no inlined intermediate base --
// just moving one statement to the end.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
public:
	Bool worldToGridSpace(float worldX, float worldY, float &gridX, float &gridY);
	void getGridVertexHeight(int x, int y, float *height);
};

extern WaterRenderObjClass *TheWaterRenderObj;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	int getBorderSizeInline() const { return m_borderSize; }

	unsigned short getHeight(int x, int y) const
	{
		int index = x + y * m_width;
		if (index < 0 || index >= m_cellCount || !m_heights) {
			return 0;
		}
		return m_heights[index];
	}

	void setRawHeight(int x, int y, int height)
	{
		int index = x + y * m_width;
		if (index >= 0 && index < m_cellCount && m_heights) {
			m_heights[index] = static_cast<unsigned short>(height);
		}
	}

private:
	unsigned char m_padding0[0x08];
	int m_width;
	unsigned char m_padding0C[0x04];
	int m_borderSize;
	unsigned char m_padding14[0x0C];
	int m_cellCount;
	unsigned short *m_heights;
};

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
	BFME_VIRTUAL_SLOT(0)   BFME_VIRTUAL_SLOT(1)   BFME_VIRTUAL_SLOT(2)   BFME_VIRTUAL_SLOT(3)
	BFME_VIRTUAL_SLOT(4)   BFME_VIRTUAL_SLOT(5)   BFME_VIRTUAL_SLOT(6)   BFME_VIRTUAL_SLOT(7)
	BFME_VIRTUAL_SLOT(8)   BFME_VIRTUAL_SLOT(9)   BFME_VIRTUAL_SLOT(10)  BFME_VIRTUAL_SLOT(11)
	BFME_VIRTUAL_SLOT(12)  BFME_VIRTUAL_SLOT(13)  BFME_VIRTUAL_SLOT(14)  BFME_VIRTUAL_SLOT(15)
	BFME_VIRTUAL_SLOT(16)  BFME_VIRTUAL_SLOT(17)  BFME_VIRTUAL_SLOT(18)  BFME_VIRTUAL_SLOT(19)
	BFME_VIRTUAL_SLOT(20)  BFME_VIRTUAL_SLOT(21)  BFME_VIRTUAL_SLOT(22)  BFME_VIRTUAL_SLOT(23)
	BFME_VIRTUAL_SLOT(24)  BFME_VIRTUAL_SLOT(25)  BFME_VIRTUAL_SLOT(26)  BFME_VIRTUAL_SLOT(27)
	BFME_VIRTUAL_SLOT(28)  BFME_VIRTUAL_SLOT(29)  BFME_VIRTUAL_SLOT(30)  BFME_VIRTUAL_SLOT(31)
	BFME_VIRTUAL_SLOT(32)  BFME_VIRTUAL_SLOT(33)  BFME_VIRTUAL_SLOT(34)  BFME_VIRTUAL_SLOT(35)
	BFME_VIRTUAL_SLOT(36)  BFME_VIRTUAL_SLOT(37)  BFME_VIRTUAL_SLOT(38)  BFME_VIRTUAL_SLOT(39)
	BFME_VIRTUAL_SLOT(40)  BFME_VIRTUAL_SLOT(41)  BFME_VIRTUAL_SLOT(42)  BFME_VIRTUAL_SLOT(43)
	BFME_VIRTUAL_SLOT(44)  BFME_VIRTUAL_SLOT(45)  BFME_VIRTUAL_SLOT(46)  BFME_VIRTUAL_SLOT(47)
	BFME_VIRTUAL_SLOT(48)  BFME_VIRTUAL_SLOT(49)  BFME_VIRTUAL_SLOT(50)  BFME_VIRTUAL_SLOT(51)
	BFME_VIRTUAL_SLOT(52)  BFME_VIRTUAL_SLOT(53)  BFME_VIRTUAL_SLOT(54)  BFME_VIRTUAL_SLOT(55)
	BFME_VIRTUAL_SLOT(56)  BFME_VIRTUAL_SLOT(57)  BFME_VIRTUAL_SLOT(58)  BFME_VIRTUAL_SLOT(59)
	BFME_VIRTUAL_SLOT(60)  BFME_VIRTUAL_SLOT(61)  BFME_VIRTUAL_SLOT(62)  BFME_VIRTUAL_SLOT(63)
	BFME_VIRTUAL_SLOT(64)  BFME_VIRTUAL_SLOT(65)  BFME_VIRTUAL_SLOT(66)  BFME_VIRTUAL_SLOT(67)
	BFME_VIRTUAL_SLOT(68)  BFME_VIRTUAL_SLOT(69)  BFME_VIRTUAL_SLOT(70)  BFME_VIRTUAL_SLOT(71)
	BFME_VIRTUAL_SLOT(72)  BFME_VIRTUAL_SLOT(73)  BFME_VIRTUAL_SLOT(74)  BFME_VIRTUAL_SLOT(75)
	BFME_VIRTUAL_SLOT(76)  BFME_VIRTUAL_SLOT(77)  BFME_VIRTUAL_SLOT(78)  BFME_VIRTUAL_SLOT(79)
	BFME_VIRTUAL_SLOT(80)  BFME_VIRTUAL_SLOT(81)  BFME_VIRTUAL_SLOT(82)  BFME_VIRTUAL_SLOT(83)
	BFME_VIRTUAL_SLOT(84)  BFME_VIRTUAL_SLOT(85)  BFME_VIRTUAL_SLOT(86)  BFME_VIRTUAL_SLOT(87)
	BFME_VIRTUAL_SLOT(88)  BFME_VIRTUAL_SLOT(89)  BFME_VIRTUAL_SLOT(90)  BFME_VIRTUAL_SLOT(91)
	BFME_VIRTUAL_SLOT(92)  BFME_VIRTUAL_SLOT(93)  BFME_VIRTUAL_SLOT(94)  BFME_VIRTUAL_SLOT(95)
	BFME_VIRTUAL_SLOT(96)  BFME_VIRTUAL_SLOT(97)  BFME_VIRTUAL_SLOT(98)  BFME_VIRTUAL_SLOT(99)
	BFME_VIRTUAL_SLOT(100) BFME_VIRTUAL_SLOT(101) BFME_VIRTUAL_SLOT(102) BFME_VIRTUAL_SLOT(103)
	BFME_VIRTUAL_SLOT(104) BFME_VIRTUAL_SLOT(105) BFME_VIRTUAL_SLOT(106) BFME_VIRTUAL_SLOT(107)
	BFME_VIRTUAL_SLOT(108) BFME_VIRTUAL_SLOT(109) BFME_VIRTUAL_SLOT(110) BFME_VIRTUAL_SLOT(111)
	BFME_VIRTUAL_SLOT(112) BFME_VIRTUAL_SLOT(113) BFME_VIRTUAL_SLOT(114) BFME_VIRTUAL_SLOT(115)
	BFME_VIRTUAL_SLOT(116) BFME_VIRTUAL_SLOT(117) BFME_VIRTUAL_SLOT(118) BFME_VIRTUAL_SLOT(119)
	BFME_VIRTUAL_SLOT(120) BFME_VIRTUAL_SLOT(121) BFME_VIRTUAL_SLOT(122) BFME_VIRTUAL_SLOT(123)
	BFME_VIRTUAL_SLOT(124) BFME_VIRTUAL_SLOT(125) BFME_VIRTUAL_SLOT(126) BFME_VIRTUAL_SLOT(127)
	BFME_VIRTUAL_SLOT(128) BFME_VIRTUAL_SLOT(129) BFME_VIRTUAL_SLOT(130) BFME_VIRTUAL_SLOT(131)
	BFME_VIRTUAL_SLOT(132) BFME_VIRTUAL_SLOT(133) BFME_VIRTUAL_SLOT(134) BFME_VIRTUAL_SLOT(135)
	BFME_VIRTUAL_SLOT(136) BFME_VIRTUAL_SLOT(137)
	virtual void staticLightingChanged(int partialUpdate);
};

#undef BFME_VIRTUAL_SLOT

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
	virtual Bool getWaterGridHeight(float worldX, float worldY, float *height);
	virtual void setRawMapHeight(const ICoord2D *gridPos, int height);

private:
	BaseHeightMapRenderObjClass *m_terrainRenderObject;   // +0x10
	WaterRenderObjClass *m_waterRenderObject;             // +0x14
	WorldHeightMap *m_logicHeightMap;                     // +0x18
	Bool m_isWaterGridRenderingEnabled;                   // +0x1C
};

// ??0W3DTerrainVisual@@QAE@XZ
W3DTerrainVisual::W3DTerrainVisual()
{
	m_terrainRenderObject = 0;
	m_waterRenderObject = 0;
	m_logicHeightMap = 0;
	m_isWaterGridRenderingEnabled = 0;
	TheWaterRenderObj = 0;
}

// ?getWaterGridHeight@W3DTerrainVisual@@UAE_NMMPAM@Z
Bool W3DTerrainVisual::getWaterGridHeight(float worldX, float worldY, float *height)
{
	float gridX;
	float gridY;
	if (m_isWaterGridRenderingEnabled) {
		WaterRenderObjClass *water = m_waterRenderObject;
		if (water && water->worldToGridSpace(worldX, worldY, gridX, gridY)) {
			water->getGridVertexHeight(static_cast<int>(gridX),
				static_cast<int>(gridY), height);
			return 1;
		}
	}
	return 0;
}

// ?setRawMapHeight@W3DTerrainVisual@@UAEXPBUICoord2D@@H@Z
void W3DTerrainVisual::setRawMapHeight(const ICoord2D *gridPos, int height)
{
	if (m_logicHeightMap) {
		int x = gridPos->x + m_logicHeightMap->getBorderSizeInline();
		int y = gridPos->y + m_logicHeightMap->getBorderSizeInline();
		if (m_logicHeightMap->getHeight(x, y) > height) {
			m_logicHeightMap->setRawHeight(x, y, height);
			m_terrainRenderObject->staticLightingChanged(0);
		}
	}
}
