// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims
// Complete reconstruction of retail 0x00730590, 684 bytes, through 0x0073083B.
// The entry is the W3DTerrainVisual subsystem secondary-base entry: its ECX is
// four bytes into the complete object, so these four fields are at +0x0c..+0x18
// from the received pointer (the complete-object offsets are +0x10..+0x1c).

#include "vector3.h"
#include <stddef.h>

typedef bool Bool;
typedef int Int;

class Gen_00602c10
{
public:
	void m(void);
};

extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);

class Rva00730590InitLock
{
public:
	Rva00730590InitLock(void) { W3DRadarResetLock(); }
	~Rva00730590InitLock(void) { bfmeUnlock1179(); }
};

// The native HeightMapRenderObjClass has four BFME vtable-bearing regions;
// this view only needs the primary table and the proven allocation extent.
#define BFME_HEIGHT_SLOT(n) virtual void slot##n(void);
class BaseHeightMapRenderObjClass
{
public:
	BFME_HEIGHT_SLOT(0)   BFME_HEIGHT_SLOT(1)   BFME_HEIGHT_SLOT(2)   BFME_HEIGHT_SLOT(3)
	BFME_HEIGHT_SLOT(4)   BFME_HEIGHT_SLOT(5)   BFME_HEIGHT_SLOT(6)   BFME_HEIGHT_SLOT(7)
	BFME_HEIGHT_SLOT(8)   BFME_HEIGHT_SLOT(9)   BFME_HEIGHT_SLOT(10)  BFME_HEIGHT_SLOT(11)
	BFME_HEIGHT_SLOT(12)  BFME_HEIGHT_SLOT(13)  BFME_HEIGHT_SLOT(14)  BFME_HEIGHT_SLOT(15)
	BFME_HEIGHT_SLOT(16)  BFME_HEIGHT_SLOT(17)  BFME_HEIGHT_SLOT(18)  BFME_HEIGHT_SLOT(19)
	BFME_HEIGHT_SLOT(20)  BFME_HEIGHT_SLOT(21)  BFME_HEIGHT_SLOT(22)  BFME_HEIGHT_SLOT(23)
	BFME_HEIGHT_SLOT(24)  BFME_HEIGHT_SLOT(25)  BFME_HEIGHT_SLOT(26)  BFME_HEIGHT_SLOT(27)
	BFME_HEIGHT_SLOT(28)  BFME_HEIGHT_SLOT(29)  BFME_HEIGHT_SLOT(30)  BFME_HEIGHT_SLOT(31)
	BFME_HEIGHT_SLOT(32)  BFME_HEIGHT_SLOT(33)  BFME_HEIGHT_SLOT(34)  BFME_HEIGHT_SLOT(35)
	BFME_HEIGHT_SLOT(36)  BFME_HEIGHT_SLOT(37)  BFME_HEIGHT_SLOT(38)  BFME_HEIGHT_SLOT(39)
	BFME_HEIGHT_SLOT(40)  BFME_HEIGHT_SLOT(41)  BFME_HEIGHT_SLOT(42)  BFME_HEIGHT_SLOT(43)
	BFME_HEIGHT_SLOT(44)  BFME_HEIGHT_SLOT(45)  BFME_HEIGHT_SLOT(46)  BFME_HEIGHT_SLOT(47)
	BFME_HEIGHT_SLOT(48)  BFME_HEIGHT_SLOT(49)  BFME_HEIGHT_SLOT(50)  BFME_HEIGHT_SLOT(51)
	BFME_HEIGHT_SLOT(52)  BFME_HEIGHT_SLOT(53)  BFME_HEIGHT_SLOT(54)  BFME_HEIGHT_SLOT(55)
	BFME_HEIGHT_SLOT(56)  BFME_HEIGHT_SLOT(57)  BFME_HEIGHT_SLOT(58)  BFME_HEIGHT_SLOT(59)
	BFME_HEIGHT_SLOT(60)  BFME_HEIGHT_SLOT(61)  BFME_HEIGHT_SLOT(62)  BFME_HEIGHT_SLOT(63)
	BFME_HEIGHT_SLOT(64)  BFME_HEIGHT_SLOT(65)  BFME_HEIGHT_SLOT(66)  BFME_HEIGHT_SLOT(67)
	BFME_HEIGHT_SLOT(68)  BFME_HEIGHT_SLOT(69)  BFME_HEIGHT_SLOT(70)  BFME_HEIGHT_SLOT(71)
	BFME_HEIGHT_SLOT(72)  BFME_HEIGHT_SLOT(73)  BFME_HEIGHT_SLOT(74)  BFME_HEIGHT_SLOT(75)
	BFME_HEIGHT_SLOT(76)  BFME_HEIGHT_SLOT(77)  BFME_HEIGHT_SLOT(78)  BFME_HEIGHT_SLOT(79)
	BFME_HEIGHT_SLOT(80)  BFME_HEIGHT_SLOT(81)  BFME_HEIGHT_SLOT(82)  BFME_HEIGHT_SLOT(83)
	BFME_HEIGHT_SLOT(84)  BFME_HEIGHT_SLOT(85)  BFME_HEIGHT_SLOT(86)  BFME_HEIGHT_SLOT(87)
	BFME_HEIGHT_SLOT(88)  BFME_HEIGHT_SLOT(89)  BFME_HEIGHT_SLOT(90)  BFME_HEIGHT_SLOT(91)
	BFME_HEIGHT_SLOT(92)  BFME_HEIGHT_SLOT(93)  BFME_HEIGHT_SLOT(94)  BFME_HEIGHT_SLOT(95)
	BFME_HEIGHT_SLOT(96)  BFME_HEIGHT_SLOT(97)  BFME_HEIGHT_SLOT(98)  BFME_HEIGHT_SLOT(99)
	BFME_HEIGHT_SLOT(100) BFME_HEIGHT_SLOT(101) BFME_HEIGHT_SLOT(102) BFME_HEIGHT_SLOT(103)
	BFME_HEIGHT_SLOT(104) BFME_HEIGHT_SLOT(105) BFME_HEIGHT_SLOT(106) BFME_HEIGHT_SLOT(107)
	BFME_HEIGHT_SLOT(108) BFME_HEIGHT_SLOT(109) BFME_HEIGHT_SLOT(110) BFME_HEIGHT_SLOT(111)
	BFME_HEIGHT_SLOT(112) BFME_HEIGHT_SLOT(113) BFME_HEIGHT_SLOT(114) BFME_HEIGHT_SLOT(115)
	BFME_HEIGHT_SLOT(116) BFME_HEIGHT_SLOT(117) BFME_HEIGHT_SLOT(118) BFME_HEIGHT_SLOT(119)
	virtual void slot120(Int, Int);
	BFME_HEIGHT_SLOT(121) BFME_HEIGHT_SLOT(122) BFME_HEIGHT_SLOT(123)
	BFME_HEIGHT_SLOT(124) BFME_HEIGHT_SLOT(125) BFME_HEIGHT_SLOT(126) BFME_HEIGHT_SLOT(127)
	BFME_HEIGHT_SLOT(128) BFME_HEIGHT_SLOT(129) BFME_HEIGHT_SLOT(130) BFME_HEIGHT_SLOT(131)
	BFME_HEIGHT_SLOT(132) BFME_HEIGHT_SLOT(133) BFME_HEIGHT_SLOT(134) BFME_HEIGHT_SLOT(135)
	BFME_HEIGHT_SLOT(136) BFME_HEIGHT_SLOT(137)

	Int m_baseField04;
};
#undef BFME_HEIGHT_SLOT

class HeightMapRenderObjClass : public BaseHeightMapRenderObjClass
{
public:
	HeightMapRenderObjClass(Int useDepthFade);

private:
	unsigned char m_knownBfmeBody[0x3174];
};

class SceneClass;

class TerrainTracksRenderObjClassSystem
{
public:
	TerrainTracksRenderObjClassSystem(void);
	void init(SceneClass *scene);

private:
	void *m_vertexBuffer;
	void *m_indexBuffer;
	void *m_vertexMaterialClass;
	unsigned int m_shaderBits;
	void *m_usedModules;
	void *m_freeModules;
	void *m_tracksScene;
	Int m_maxTankTrackEdges;
	Int m_maxTankTrackOpaqueEdges;
	Int m_maxTankTrackFadeDelay;
};

class W3DShadowManager
{
public:
	W3DShadowManager(void);
	Bool rva007B7500(void);

private:
	unsigned char m_knownBfmeBody[0x0c];
};

class RenderObjClass
{
public:
#define BFME_RENDER_SLOT(n) virtual void slot##n(void);
	BFME_RENDER_SLOT(0)  BFME_RENDER_SLOT(1)  BFME_RENDER_SLOT(2)  BFME_RENDER_SLOT(3)
	BFME_RENDER_SLOT(4)  BFME_RENDER_SLOT(5)  BFME_RENDER_SLOT(6)  BFME_RENDER_SLOT(7)
	BFME_RENDER_SLOT(8)  BFME_RENDER_SLOT(9)  BFME_RENDER_SLOT(10) BFME_RENDER_SLOT(11)
	BFME_RENDER_SLOT(12) BFME_RENDER_SLOT(13) BFME_RENDER_SLOT(14) BFME_RENDER_SLOT(15)
	BFME_RENDER_SLOT(16) BFME_RENDER_SLOT(17) BFME_RENDER_SLOT(18) BFME_RENDER_SLOT(19)
	BFME_RENDER_SLOT(20) BFME_RENDER_SLOT(21)
	virtual void Set_Position(const Vector3 &position);
#undef BFME_RENDER_SLOT
};

class WaterSnapshot
{
public:
	virtual void slot0(void);
};

enum WaterType { WATER_TYPE_0_TRANSLUCENT = 0, WATER_TYPE_1_FB_REFLECTION = 1 };
class WaterRenderObjClass : public WaterSnapshot, public RenderObjClass
{
public:
	WaterRenderObjClass(void);
	Int init(float positionZ, float extentX, float extentY,
		SceneClass *scene, WaterType type);
	void toggleCloudLayer(Bool state) { m_useCloudPlane = state; }

	unsigned char m_knownWaterFields[0x110];
	Bool m_useCloudPlane;
	unsigned char m_knownWaterTail[0x2eb];
};

class SmudgeManager
{
public:
	virtual void slot0(void);
	virtual void init(void);
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	W3DSmudgeManager(void);

private:
	unsigned char m_knownBfmeBody[0x40];
};

class SceneClass
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void Add_Render_Object(RenderObjClass *object);
};

class W3DDisplay
{
public:
	static SceneClass *m_3DScene;
};

class GlobalData
{
public:
	unsigned char m_beforeCloudPlane[0x63];
	unsigned char m_useCloudPlane;        // +0x63
	unsigned char m_beforeWaterPosition[0x10];
	float m_waterPositionX;               // +0x74
	float m_waterPositionY;               // +0x78
	float m_waterPositionZ;               // +0x7c
	float m_waterExtentX;                 // +0x80
	float m_waterExtentY;                 // +0x84
	Int m_waterType;                      // +0x88
	unsigned char m_beforeGridClamps[0x20];
	float m_vertexWaterHeightClampLow;    // +0xac
	unsigned char m_beforeGridClampHigh[0x0c];
	float m_vertexWaterHeightClampHi;     // +0xbc
	unsigned char m_beforeGridAngle[0x0c];
	float m_vertexWaterAngle;             // +0xcc
	unsigned char m_beforeGridXPosition[0x0c];
	float m_vertexWaterXPosition;         // +0xdc
	unsigned char m_beforeGridYPosition[0x0c];
	float m_vertexWaterYPosition;         // +0xec
	unsigned char m_beforeGridZPosition[0x0c];
	float m_vertexWaterZPosition;         // +0xfc
	unsigned char m_beforeGridCellX[0x0c];
	Int m_vertexWaterXGridCells;          // +0x10c
	unsigned char m_beforeGridCellY[0x0c];
	Int m_vertexWaterYGridCells;          // +0x11c
	unsigned char m_beforeGridSize[0x0c];
	float m_vertexWaterGridSize;          // +0x12c
	unsigned char m_beforeAttenuationA[0x0c];
	float m_vertexWaterAttenuationA;      // +0x13c
	unsigned char m_beforeAttenuationB[0x0c];
	float m_vertexWaterAttenuationB;      // +0x14c
	unsigned char m_beforeAttenuationC[0x0c];
	float m_vertexWaterAttenuationC;      // +0x15c
	unsigned char m_beforeAttenuationRange[0x0c];
	float m_vertexWaterAttenuationRange;  // +0x16c
};

#define BFME_OFFSET_ASSERT(type, field, value) \
	typedef char bfme_offset_##field[(offsetof(type, field) == (value)) ? 1 : -1]
#define BFME_SIZE_ASSERT(type, value) \
	typedef char bfme_size_##type[(sizeof(type) == (value)) ? 1 : -1]

BFME_OFFSET_ASSERT(GlobalData, m_useCloudPlane, 0x63);
BFME_OFFSET_ASSERT(GlobalData, m_waterPositionX, 0x74);
BFME_OFFSET_ASSERT(GlobalData, m_waterPositionY, 0x78);
BFME_OFFSET_ASSERT(GlobalData, m_waterPositionZ, 0x7c);
BFME_OFFSET_ASSERT(GlobalData, m_waterExtentX, 0x80);
BFME_OFFSET_ASSERT(GlobalData, m_waterExtentY, 0x84);
BFME_OFFSET_ASSERT(GlobalData, m_waterType, 0x88);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterHeightClampLow, 0xac);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterHeightClampHi, 0xbc);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterAngle, 0xcc);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterXPosition, 0xdc);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterYPosition, 0xec);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterZPosition, 0xfc);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterXGridCells, 0x10c);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterYGridCells, 0x11c);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterGridSize, 0x12c);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterAttenuationA, 0x13c);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterAttenuationB, 0x14c);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterAttenuationC, 0x15c);
BFME_OFFSET_ASSERT(GlobalData, m_vertexWaterAttenuationRange, 0x16c);

BFME_SIZE_ASSERT(HeightMapRenderObjClass, 0x317c);
BFME_SIZE_ASSERT(TerrainTracksRenderObjClassSystem, 0x28);
BFME_SIZE_ASSERT(W3DShadowManager, 0x0c);
BFME_SIZE_ASSERT(WaterRenderObjClass, 0x404);
BFME_SIZE_ASSERT(W3DSmudgeManager, 0x44);

#undef BFME_OFFSET_ASSERT
#undef BFME_SIZE_ASSERT

class TerrainVisualSettings
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual void slot3(void);
	virtual void slot4(void);
	virtual void slot5(void);
	virtual void slot6(void);
	virtual void slot7(void);
	virtual void slot8(void);
	virtual void slot9(void);
	virtual void slot10(void);
	virtual void setWaterGridHeightClamps(void *water, float low, float high);
	virtual void setWaterAttenuationFactors(void *water, float a, float b, float c, float range);
	virtual void slot13(void);
	virtual void setWaterTransform(void *water, float angle, float x, float y, float z);
	virtual void slot15(void);
	virtual void setWaterGridResolution(void *water, float x, float y, float size);
};

extern HeightMapRenderObjClass *TheTerrainRenderObject;
extern TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem;
extern W3DShadowManager *TheW3DShadowManager;
extern WaterRenderObjClass *TheWaterRenderObj;
extern W3DSmudgeManager *TheSmudgeManager;
extern TerrainVisualSettings *TheTerrainVisual;
extern GlobalData *TheGlobalData;
extern Bool Rva012F08A0;

class Rva00730590
{
public:
	virtual void slot0(void);
	virtual void init(void);

	unsigned char m_secondaryBaseFields[8];
	HeightMapRenderObjClass *m_terrainRenderObject; // received this+0x0c
	WaterRenderObjClass *m_waterRenderObject;       // received this+0x10
	void *m_logicHeightMap;                         // received this+0x14
	Bool m_isWaterGridRenderingEnabled;             // received this+0x18
};

void Rva00730590::init(void)
{
	Rva00730590InitLock lock;
	(reinterpret_cast<Gen_00602c10 *>(this))->m();

	m_terrainRenderObject = new HeightMapRenderObjClass(0);
	m_terrainRenderObject->slot120(2, 0);
	TheTerrainRenderObject = m_terrainRenderObject;

	TerrainTracksRenderObjClassSystem *tracks =
		new TerrainTracksRenderObjClassSystem;
	TheTerrainTracksRenderObjClassSystem = tracks;
	tracks->init(W3DDisplay::m_3DScene);

	W3DShadowManager *shadow = new W3DShadowManager;
	TheW3DShadowManager = shadow;
	shadow->rva007B7500();

	m_waterRenderObject = new WaterRenderObjClass;
	TheWaterRenderObj = m_waterRenderObject;
	m_waterRenderObject->init(TheGlobalData->m_waterPositionZ,
		TheGlobalData->m_waterExtentX, TheGlobalData->m_waterExtentY,
		W3DDisplay::m_3DScene,
		static_cast<WaterType>(TheGlobalData->m_waterType));
	m_waterRenderObject->Set_Position(
		Vector3(TheGlobalData->m_waterPositionX,
			TheGlobalData->m_waterPositionY, TheGlobalData->m_waterPositionZ));

	W3DSmudgeManager *smudge = new W3DSmudgeManager;
	TheSmudgeManager = smudge;
	smudge->init();

	if (!Rva012F08A0 && TheGlobalData->m_waterType != 1 && m_waterRenderObject)
		W3DDisplay::m_3DScene->Add_Render_Object(
			static_cast<RenderObjClass *>(m_waterRenderObject));

	if (m_waterRenderObject) {
		if (TheGlobalData->m_useCloudPlane != 0)
			m_waterRenderObject->toggleCloudLayer(true);
		else
			m_waterRenderObject->toggleCloudLayer(false);
	}

	TheTerrainVisual->setWaterGridHeightClamps(
		0, TheGlobalData->m_vertexWaterHeightClampLow,
		TheGlobalData->m_vertexWaterHeightClampHi);
	TheTerrainVisual->setWaterTransform(
		0, TheGlobalData->m_vertexWaterAngle,
		TheGlobalData->m_vertexWaterXPosition,
		TheGlobalData->m_vertexWaterYPosition,
		TheGlobalData->m_vertexWaterZPosition);
	TheTerrainVisual->setWaterGridResolution(
		0, static_cast<float>(TheGlobalData->m_vertexWaterXGridCells),
		static_cast<float>(TheGlobalData->m_vertexWaterYGridCells),
		TheGlobalData->m_vertexWaterGridSize);
	TheTerrainVisual->setWaterAttenuationFactors(
		0, TheGlobalData->m_vertexWaterAttenuationA,
		TheGlobalData->m_vertexWaterAttenuationB,
		TheGlobalData->m_vertexWaterAttenuationC,
		TheGlobalData->m_vertexWaterAttenuationRange);

	m_isWaterGridRenderingEnabled = false;
}
