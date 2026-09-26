// ?update@TerrainTracksRenderObjClassSystem@@QAEXXZ
// Complete retail 0x0072EEB0..0x0072EFB7 (263 bytes), including all return paths.
// The releaseTrack definition must be visible in this TU: VC7.1 then knows
// that this callee preserves ECX and avoids saving the owner in EBP.
// Both update and releaseTrack (0x0072EB60/137B) independently match retail.
// The latter is already claimed as BfmeThingOM::bfmeDropOM and gets no new
// coverage credit. The field layout agrees with the independent name oracle.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims
// BFME retail 0x0072EEB0: update the active terrain-track edges.

typedef unsigned char Bool;
typedef int Int;

#include "vector3.h"
#include "vector2.h"
#include "ww3d.h"

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
	TerrainTracksRenderObjClass *m_prevSystem;
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
	void Reset(void);

private:
	void releaseTrack(TerrainTracksRenderObjClass *mod);

	unsigned char m_pad0[0x10];
	TerrainTracksRenderObjClass *m_usedModules;
	TerrainTracksRenderObjClass *m_freeModules;
	unsigned char m_pad1[4];
	Int m_maxTankTrackEdges;
	Int m_maxTankTrackOpaqueEdges;
	Int m_maxTankTrackFadeDelay;
};

extern GlobalData *TheGlobalData;

void TerrainTracksRenderObjClassSystem::releaseTrack(TerrainTracksRenderObjClass *mod) {
    if (!mod) return;
    if (mod->m_nextSystem) mod->m_nextSystem->m_prevSystem=mod->m_prevSystem;
    if (mod->m_prevSystem) mod->m_prevSystem->m_nextSystem=mod->m_nextSystem;
    else m_usedModules=mod->m_nextSystem;
    mod->m_prevSystem=0;
    mod->m_nextSystem=m_freeModules;
    if (m_freeModules) m_freeModules->m_prevSystem=mod;
    m_freeModules=mod;
    mod->m_haveAnchor=0;
    mod->m_haveCap=1;
    mod->m_topIndex=0;
    mod->m_bottomIndex=0;
    mod->m_activeEdgeCount=0;
    mod->m_totalEdgesAdded=0;
    mod->m_ownerDrawable=0;
}

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

// ?Reset@TerrainTracksRenderObjClassSystem@@QAEXXZ
// Retail 0x0072F000 walks the used list while releaseTrack relinks each node.
void TerrainTracksRenderObjClassSystem::Reset(void)
{
	TerrainTracksRenderObjClass *nextMod;
	TerrainTracksRenderObjClass *mod = m_usedModules;

	while (mod)
	{
		nextMod = mod->m_nextSystem;
		releaseTrack(mod);
		mod = nextMod;
	}
}
