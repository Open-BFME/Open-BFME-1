// cl: /DNDEBUG /MD /EHsc
// readable body of ?adjustTerrainLOD@BaseHeightMapRenderObjClass@@UAEXH@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp

class BaseHeightMapRenderObjClass;
class HeightMapRenderObjClass;
class RTS3DScene;
class View;

#define UNUSED_VIRTUALS_16(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9(); virtual void prefix##a(); virtual void prefix##b(); \
	virtual void prefix##c(); virtual void prefix##d(); virtual void prefix##e(); virtual void prefix##f()

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
struct GlobalData
{
	char m_unknown[0x54];
	int m_terrainLOD;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
struct WorldHeightMap
{
	char m_unknown[0x120e8];
	int m_drawWidth;
	int m_drawHeight;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShroud.h
class W3DShroud
{
public:
	void reset();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DRoadBuffer.h
class W3DRoadBuffer
{
public:
	void loadRoads();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DScene.h
class RTS3DScene
{
public:
	virtual void unused00();
	virtual void unused04();
	virtual void addRenderObject(void *object);
	virtual void removeRenderObject(void *object);
	virtual void unused10(); virtual void unused14(); virtual void unused18(); virtual void unused1c();
	virtual void unused20(); virtual void unused24(); virtual void unused28(); virtual void unused2c();
	virtual void unused30(); virtual void unused34();
	virtual void registerObject(void *object, int event);
	virtual void unregisterObject(void *object, int event);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/HeightMap.h
class HeightMapRenderObjClass
{
public:
	HeightMapRenderObjClass(int useDepthFade);
	UNUSED_VIRTUALS_16(unused000_);
	UNUSED_VIRTUALS_16(unused040_);
	UNUSED_VIRTUALS_16(unused080_);
	UNUSED_VIRTUALS_16(unused0c0_);
	UNUSED_VIRTUALS_16(unused100_);
	UNUSED_VIRTUALS_16(unused140_);
	UNUSED_VIRTUALS_16(unused180_);
	UNUSED_VIRTUALS_16(unused1c0_);
	virtual void unused200(); virtual void unused204(); virtual void unused208(); virtual void unused20c();
	virtual int initHeightData(int width, int height, WorldHeightMap *map, void *lights);

	W3DRoadBuffer *roadBuffer() const
	{
		return *reinterpret_cast<W3DRoadBuffer *const *>(reinterpret_cast<const char *>(this) + 0x30ac);
	}

private:
	char m_data[0x3178];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/View.h
class View
{
public:
	UNUSED_VIRTUALS_16(unused000_);
	UNUSED_VIRTUALS_16(unused040_);
	UNUSED_VIRTUALS_16(unused080_);
	virtual void unused0c0(); virtual void unused0c4(); virtual void unused0c8(); virtual void unused0cc();
	virtual void unused0d0(); virtual void unused0d4(); virtual void unused0d8(); virtual void unused0dc();
	virtual void unused0e0(); virtual void unused0e4(); virtual void unused0e8(); virtual void unused0ec();
	virtual void unused0f0(); virtual void unused0f4();
	virtual void setAngle(float angle);
	virtual float getAngle();
};

#undef UNUSED_VIRTUALS_16

extern GlobalData *TheWritableGlobalData;
extern HeightMapRenderObjClass *TheHeightMap;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern View *TheTacticalView;

class __declspec(novtable) BaseHeightMapRenderObjClass
{
public:
	virtual void adjustTerrainLOD(int adjustment);

private:
	char m_unknown04[0x7c];
	RTS3DScene *m_scene;
	char m_unknown84[0x2f70];
	WorldHeightMap *m_map;
	char m_unknown2ff8[0xb4];
	W3DRoadBuffer *m_roadBuffer;
	char m_unknown30b0[8];
	W3DShroud *m_shroud;
};

void BaseHeightMapRenderObjClass::adjustTerrainLOD(int adjustment)
{
	if (adjustment > 0 && TheWritableGlobalData->m_terrainLOD < 7)
		TheWritableGlobalData->m_terrainLOD = TheWritableGlobalData->m_terrainLOD + 1;
	if (adjustment < 0 && TheWritableGlobalData->m_terrainLOD > 1)
		TheWritableGlobalData->m_terrainLOD = TheWritableGlobalData->m_terrainLOD - 1;

	if (TheWritableGlobalData->m_terrainLOD == 8)
		TheWritableGlobalData->m_terrainLOD = 7;

	if (m_map == 0)
		return;
	if (m_shroud != 0)
		m_shroud->reset();

	HeightMapRenderObjClass *newRenderObject = TheHeightMap;
	if (newRenderObject == 0)
		newRenderObject = new HeightMapRenderObjClass(0);
	if (TheWritableGlobalData->m_terrainLOD == 5)
		newRenderObject = 0;

	RTS3DScene *scene = m_scene;
	if (scene != 0)
	{
		scene->removeRenderObject(this);
		scene->unregisterObject(this, 0);
		if (newRenderObject != 0)
		{
			scene->addRenderObject(newRenderObject);
			scene->registerObject(newRenderObject, 0);
		}
	}

	if (newRenderObject != 0)
	{
		newRenderObject->initHeightData(m_map->m_drawWidth, m_map->m_drawHeight, m_map, 0);
		TheTerrainRenderObject = reinterpret_cast<BaseHeightMapRenderObjClass *>(newRenderObject);
		newRenderObject->roadBuffer()->loadRoads();
	}

	if (TheTacticalView != 0)
	{
		TheTacticalView->setAngle(TheTacticalView->getAngle() + 1.0f);
		TheTacticalView->setAngle(TheTacticalView->getAngle() - 1.0f);
	}
}
