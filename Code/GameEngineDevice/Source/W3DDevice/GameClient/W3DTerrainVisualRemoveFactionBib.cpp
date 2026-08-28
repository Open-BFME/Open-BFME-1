// cl: /DNDEBUG /MD /EHsc
// readable body of ?removeFactionBib@W3DTerrainVisual@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_padding[0x74];
	ObjectID m_id;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
	void removeTerrainBib(ObjectID id);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainVisual.h
class W3DTerrainVisual
{
public:
	virtual void removeFactionBib(Object *factionBuilding);

private:
	unsigned char m_basePadding[0x0C];
	BaseHeightMapRenderObjClass *m_terrainRenderObject;
	void *m_waterRenderObject;
	void *m_logicHeightMap;
};

void W3DTerrainVisual::removeFactionBib(Object *factionBuilding)
{
	if (m_logicHeightMap) {
		m_terrainRenderObject->removeTerrainBib(factionBuilding->getID());
	}
}
