// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
// readable body of ?addEdgeToTrack@TerrainTracksRenderObjClass@@QAEXMM@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp
// BFME retail 0x0072F390: the track render object's cap-edge method.

#include "WWMath/vector2.h"
#include "WWMath/vector3.h"

typedef unsigned char Bool;
typedef int PathfindLayerEnum;

enum
{
	LAYER_GROUND = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	PathfindLayerEnum getLayer(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	unsigned char m_pad[0xFC];
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void v0(void) const;
	virtual void v1(void) const;
	virtual void v2(void) const;
	virtual void v3(void) const;
	virtual void v4(void) const;
	virtual void v5(void) const;
	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const;
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
		Coord3D *normal = 0, Bool clip = true) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
class TerrainTracksRenderObjClassSystem
{
public:
	unsigned char m_pad[0x1C];
	int m_maxTankTrackEdges;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static unsigned int Get_Sync_Time(void)
	{
		return *(unsigned int *)0x0133F420;
	}
};

#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define TheTerrainTracksRenderObjClassSystem (*(TerrainTracksRenderObjClassSystem **)0x012F9D98)

static inline float sqr(float value)
{
	return value * value;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
struct edgeInfo
{
	Vector3 endPointPos[2];
	Vector2 endPointUV[2];
	int timeAdded;
	float alpha;
};

class BfmeTrackLikeD62640
{
public:
	void addCapEdgeToTrack(float x, float y);

private:
	unsigned char m_base[8];
	void *m_stageZeroTexture;
	int m_activeEdgeCount;
	int m_totalEdgesAdded;
	Drawable *m_ownerDrawable;
	edgeInfo m_edges[100];
	Vector3 m_lastAnchor;
	int m_bottomIndex;
	int m_topIndex;
	Bool m_haveAnchor;
	Bool m_bound;
	unsigned char m_pad[2];
	float m_width;
	float m_length;
	Bool m_airborne;
	Bool m_haveCap;
};

void BfmeTrackLikeD62640::addCapEdgeToTrack(float x, float y)
{
	if (m_haveCap)
	{
		return;
	}

	if (m_activeEdgeCount == 1)
	{
		m_haveCap = true;
		m_haveAnchor = false;
		return;
	}

	Vector3 vPos;
	Vector3 vZ;
	Coord3D vZTmp;
	PathfindLayerEnum objectLayer;
	float eHeight;

	if (m_ownerDrawable && (objectLayer = m_ownerDrawable->m_object->getLayer()) != LAYER_GROUND)
	{
		eHeight = 0.25f + TheTerrainLogic->getLayerHeight(x, y, objectLayer, &vZTmp);
	}
	else
	{
		eHeight = TheTerrainLogic->getGroundHeight(x, y, &vZTmp);
	}

	vZ.X = vZTmp.x;
	vZ.Y = vZTmp.y;
	vZ.Z = vZTmp.z;

	vPos.X = x;
	vPos.Y = y;
	vPos.Z = eHeight;

	Vector3 vDir = Vector3(x, y, eHeight) - m_lastAnchor;
	int maxEdgeCount = TheTerrainTracksRenderObjClassSystem->m_maxTankTrackEdges;

	if (vDir.Length2() < sqr(m_length))
	{
		int lastAddedEdge = m_topIndex - 1;
		if (lastAddedEdge < 0)
			lastAddedEdge = maxEdgeCount - 1;
		m_edges[lastAddedEdge].alpha = 0.0f;
		m_haveCap = true;
		m_haveAnchor = false;
		return;
	}

	if (m_activeEdgeCount >= maxEdgeCount)
	{
		m_bottomIndex++;
		m_activeEdgeCount--;

		if (m_bottomIndex >= maxEdgeCount)
			m_bottomIndex = 0;
	}

	if (m_topIndex >= maxEdgeCount)
		m_topIndex = 0;

	vDir.Z = 0;
	vDir.Normalize();

	Vector3 vX;
	Vector3::Cross_Product(vDir, vZ, &vX);

	edgeInfo &topEdge = m_edges[m_topIndex];

	topEdge.endPointPos[0] = vPos - (m_width * 0.5f * vX);
	topEdge.endPointPos[0].Z += 2.0f;

	if (m_totalEdgesAdded & 1)
	{
		topEdge.endPointUV[0].X = 0.0f;
		topEdge.endPointUV[0].Y = 0.0f;
	}
	else
	{
		topEdge.endPointUV[0].X = 0.0f;
		topEdge.endPointUV[0].Y = 1.0f;
	}

	topEdge.endPointPos[1] = vPos + (m_width * 0.5f * vX);
	topEdge.endPointPos[1].Z += 2.0f;

	if (m_totalEdgesAdded & 1)
	{
		topEdge.endPointUV[1].X = 1.0f;
		topEdge.endPointUV[1].Y = 0.0f;
	}
	else
	{
		topEdge.endPointUV[1].X = 1.0f;
		topEdge.endPointUV[1].Y = 1.0f;
	}

	topEdge.timeAdded = WW3D::Get_Sync_Time();
	topEdge.alpha = 0.0f;
	m_lastAnchor = vPos;
	m_activeEdgeCount++;
	m_totalEdgesAdded++;
	m_topIndex++;
	m_haveCap = true;
	m_haveAnchor = false;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
class TerrainTracksRenderObjClass
{
public:
	void addEdgeToTrack(float x, float y);

private:
	unsigned char m_base[8];
	void *m_stageZeroTexture;
	int m_activeEdgeCount;
	int m_totalEdgesAdded;
	Drawable *m_ownerDrawable;
	edgeInfo m_edges[100];
	Vector3 m_lastAnchor;
	int m_bottomIndex;
	int m_topIndex;
	Bool m_haveAnchor;
	Bool m_bound;
	unsigned char m_pad[2];
	float m_width;
	float m_length;
	Bool m_airborne;
	Bool m_haveCap;
};

void TerrainTracksRenderObjClass::addEdgeToTrack(float x, float y)
{
	if (!m_haveAnchor)
	{
		PathfindLayerEnum objectLayer;
		if (m_ownerDrawable && (objectLayer = m_ownerDrawable->m_object->getLayer()) != LAYER_GROUND)
			m_lastAnchor = Vector3(x, y, TheTerrainLogic->getLayerHeight(x, y, objectLayer) + 0.25f);
		else
			m_lastAnchor = Vector3(x, y, TheTerrainLogic->getGroundHeight(x, y));

		m_haveAnchor = true;
		m_airborne = true;
		m_haveCap = true;
		return;
	}

	m_haveCap = false;

	Vector3 vPos;
	Vector3 vZ;
	Coord3D vZTmp;
	float eHeight;
	PathfindLayerEnum objectLayer;

	if (m_ownerDrawable && (objectLayer = m_ownerDrawable->m_object->getLayer()) != LAYER_GROUND)
		return;

	eHeight = TheTerrainLogic->getGroundHeight(x, y, &vZTmp);

	vZ.X = vZTmp.x;
	vZ.Y = vZTmp.y;
	vZ.Z = vZTmp.z;

	vPos.X = x;
	vPos.Y = y;
	vPos.Z = eHeight;

	Vector3 vDir = Vector3(x, y, eHeight) - m_lastAnchor;
	if (vDir.Length2() < sqr(m_length))
		return;

	int maxEdgeCount = TheTerrainTracksRenderObjClassSystem->m_maxTankTrackEdges;

	if (m_activeEdgeCount >= maxEdgeCount)
	{
		m_bottomIndex++;
		m_activeEdgeCount--;

		if (m_bottomIndex >= maxEdgeCount)
			m_bottomIndex = 0;
	}

	if (m_topIndex >= maxEdgeCount)
		m_topIndex = 0;

	vDir.Z = 0;
	vDir.Normalize();

	Vector3 vX;
	Vector3::Cross_Product(vDir, vZ, &vX);

	edgeInfo &topEdge = m_edges[m_topIndex];

	topEdge.endPointPos[0] = vPos - (m_width * 0.5f * vX);
	topEdge.endPointPos[0].Z += 2.0f;

	if (m_totalEdgesAdded & 1)
	{
		topEdge.endPointUV[0].X = 0.0f;
		topEdge.endPointUV[0].Y = 0.0f;
	}
	else
	{
		topEdge.endPointUV[0].X = 0.0f;
		topEdge.endPointUV[0].Y = 1.0f;
	}

	topEdge.endPointPos[1] = vPos + (m_width * 0.5f * vX);
	topEdge.endPointPos[1].Z += 2.0f;

	if (m_totalEdgesAdded & 1)
	{
		topEdge.endPointUV[1].X = 1.0f;
		topEdge.endPointUV[1].Y = 0.0f;
	}
	else
	{
		topEdge.endPointUV[1].X = 1.0f;
		topEdge.endPointUV[1].Y = 1.0f;
	}

	topEdge.timeAdded = WW3D::Get_Sync_Time();
	topEdge.alpha = 1.0f;
	if (m_airborne || m_activeEdgeCount <= 1)
		topEdge.alpha = 0.0f;
	m_airborne = false;

	m_lastAnchor = vPos;
	m_activeEdgeCount++;
	m_totalEdgesAdded++;
	m_topIndex++;
}
