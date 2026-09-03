// ?update@TerrainTracksRenderObjClassSystem@@QAEXXZ
// partial score=0.6 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
// BFME retail 0x0072EEB0: update the active terrain-track edges.

typedef unsigned char Bool;
typedef int Int;

struct Vector3
{
	float X;
	float Y;
	float Z;
};

struct Vector2
{
	float X;
	float Y;
};

struct edgeInfo
{
	Vector3 endPointPos[2];
	Vector2 endPointUV[2];
	Int timeAdded;
	float alpha;
};

class TerrainTracksRenderObjClass
{
public:
	unsigned char m_base[8];
	void *m_stageZeroTexture;
	Int m_activeEdgeCount;
	Int m_totalEdgesAdded;
	void *m_ownerDrawable;
	edgeInfo m_edges[100];
	Vector3 m_lastAnchor;
	Int m_bottomIndex;
	Int m_topIndex;
	Bool m_haveAnchor;
	Bool m_bound;
	unsigned char m_pad0[2];
	float m_width;
	float m_length;
	Bool m_airborne;
	Bool m_haveCap;
	unsigned char m_pad1[2];
	TerrainTracksRenderObjClass *m_nextSystem;
};

class GlobalData
{
public:
	unsigned char m_pad[0x220];
	Bool m_makeTrackMarks;
};

class TerrainTracksRenderObjClassSystem
{
public:
	void update(void);

private:
	void releaseTrack(TerrainTracksRenderObjClass *mod);

	unsigned char m_pad0[0x10];
	TerrainTracksRenderObjClass *m_usedModules;
	unsigned char m_pad1[8];
	Int m_maxTankTrackEdges;
	Int m_maxTankTrackOpaqueEdges;
	Int m_maxTankTrackFadeDelay;
};

extern GlobalData *TheGlobalData;

class WW3D
{
public:
	static Int Get_Sync_Time(void)
	{
		return *(Int *)0x0133F420;
	}
};

void TerrainTracksRenderObjClassSystem::update(void)
{
	Int iTime = WW3D::Get_Sync_Time();
	float iDiff;
	TerrainTracksRenderObjClass *mod = m_usedModules, *nextMod;

	while (mod != 0)
	{
		Int i, index;
		Vector3 *endPoint;
		Vector2 *endPointUV;

		nextMod = mod->m_nextSystem;

		if (!TheGlobalData->m_makeTrackMarks)
			mod->m_haveAnchor = false;

		for (i = 0, index = mod->m_bottomIndex; i < mod->m_activeEdgeCount; i++, index++)
		{
			if (index >= m_maxTankTrackEdges)
				index = 0;

			endPoint = &mod->m_edges[index].endPointPos[0];
			endPointUV = &mod->m_edges[index].endPointUV[0];
			iDiff = (float)(iTime - mod->m_edges[index].timeAdded);
			iDiff = 1.0f - iDiff / (float)m_maxTankTrackFadeDelay;
			if (iDiff < 0.0)
				iDiff = 0.0f;
			if (mod->m_edges[index].alpha > 0.0f)
				mod->m_edges[index].alpha = iDiff;

			if (iDiff == 0.0f)
			{
				mod->m_bottomIndex++;
				mod->m_activeEdgeCount--;

				if (mod->m_bottomIndex >= m_maxTankTrackEdges)
					mod->m_bottomIndex = 0;
			}
			if (mod->m_activeEdgeCount == 0 && !mod->m_bound)
				releaseTrack(mod);
		}
		mod = nextMod;
	}
}
