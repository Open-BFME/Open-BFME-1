#pragma once

#include "matrix4.h"
#include "W3DDevice/GameClient/W3DBufferManager.h"
#include "GameClient/Shadow.h"

#define MAX_SHADOW_CASTER_MESHES 160

class W3DShadowGeometry;
class W3DShadowGeometryManager;
struct Geometry;
struct PolyNeighbor;
class W3DVolumetricShadow;
class Drawable;

struct W3DVolumetricShadowRenderTask : public W3DBufferManager::W3DRenderTask
{
	W3DVolumetricShadow *m_parentShadow;
	UnsignedByte m_meshIndex;
	UnsignedByte m_lightIndex;
};

class W3DVolumetricShadowManager
{
public:
	W3DVolumetricShadowManager(void);
	~W3DVolumetricShadowManager(void);
	Bool init(void);
	void reset(void);
	W3DVolumetricShadow *addShadow(RenderObjClass *, Shadow::ShadowTypeInfo *, Drawable *);
	void removeShadow(W3DVolumetricShadow *);
	void removeAllShadows(void);
	void addDynamicShadowTask(W3DVolumetricShadowRenderTask *task)
	{
		W3DBufferManager::W3DRenderTask *oldTask = m_dynamicShadowVolumesToRender;
		m_dynamicShadowVolumesToRender = task;
		m_dynamicShadowVolumesToRender->m_nextTask = oldTask;
	}
	void invalidateCachedLightPositions(void);
	void loadTerrainShadows(void);
	void renderShadows(Bool);
	void renderShadows(void);
	void ReleaseResources(void);
	Bool ReAcquireResources(void);
protected:
	void renderStencilShadows(void);
	W3DVolumetricShadow *m_shadowList;
	W3DVolumetricShadowRenderTask *m_dynamicShadowVolumesToRender;
	W3DShadowGeometryManager *m_W3DShadowGeometryManager;
};

extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;

class W3DVolumetricShadow : public Shadow
{
	friend class W3DVolumetricShadowManager;
	enum { SHADOW_DYNAMIC = 0x1 };
public:
	W3DVolumetricShadow(void);
	~W3DVolumetricShadow(void);
protected:
	virtual void release(void) { TheW3DVolumetricShadowManager->removeShadow(this); }
#if defined(_DEBUG) || defined(_INTERNAL)
	virtual void getRenderCost(RenderCost &) const;
#endif
	void SetGeometry(W3DShadowGeometry *);
	void setShadowLengthScale(Real value) { m_shadowLengthScale = value; }
	void updateOptimalExtrusionPadding(void);
	void setOptimalExtrusionPadding(Real value) { m_extraExtrusionPadding = value; }
	const W3DShadowGeometry *getGeometry(void) { return m_geometry; }
	void setRenderObject(RenderObjClass *robj) { assert(m_robj == NULL); m_robj = robj; }
	void setRenderObjExtent(Real extent) { m_robjExtent = extent; }
	void Update(void);
	void updateVolumes(Real);
	void updateMeshVolume(Int, Int, const Matrix3D *, const AABoxClass &, float);
	void RenderVolume(Int, Int);
	void RenderMeshVolume(Int, Int, const Matrix3D *);
	void RenderDynamicMeshVolume(Int, Int, const Matrix3D *);
	void RenderMeshVolumeBounds(Int, Int, const Matrix3D *);
	void setLightPosHistory(Int lightIndex, Int meshIndex, Vector3 &pos) { m_lightPosHistory[lightIndex][meshIndex] = pos; }
	W3DVolumetricShadow *m_next;
	void buildSilhouette(Int, Vector3 *);
	void addSilhouetteEdge(Int, PolyNeighbor *, PolyNeighbor *);
	void addNeighborlessEdges(Int, PolyNeighbor *);
	void addSilhouetteIndices(Int, Short, Short);
	Bool allocateSilhouette(Int, Int);
	void deleteSilhouette(Int);
	void resetSilhouette(Int);
	void constructVolume(Vector3 *, Real, Int, Int);
	void constructVolumeVB(Vector3 *, Real, Int, Int);
	Bool allocateShadowVolume(Int, Int);
	void deleteShadowVolume(Int);
	void resetShadowVolume(Int, Int);
	W3DShadowGeometry *m_geometry;
	RenderObjClass *m_robj;
	Real m_shadowLengthScale;
	Real m_robjExtent;
	Real m_extraExtrusionPadding;
	static Geometry m_tempShadowVolume;
	char m_bfmeShadowPadding[0x30];
	Geometry *m_shadowVolume[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DVertexBufferSlot *m_shadowVolumeVB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DIndexBufferSlot *m_shadowVolumeIB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DVolumetricShadowRenderTask m_shadowVolumeRenderTask[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	Int m_shadowVolumeCount[MAX_SHADOW_CASTER_MESHES];
	Vector3 m_lightPosHistory[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	Matrix4x4 m_objectXformHistory[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	Short *m_silhouetteIndex[MAX_SHADOW_CASTER_MESHES];
	Short m_numSilhouetteIndices[MAX_SHADOW_CASTER_MESHES];
	Short m_maxSilhouetteEntries[MAX_SHADOW_CASTER_MESHES];
	Int m_numIndicesPerMesh[MAX_SHADOW_CASTER_MESHES];
};
