// ?updateVolumes@W3DVolumetricShadow@@IAEXM@Z
// partial score=0.65 date=2026-09-26
// Candidate compile in Code\GameEngineDevice\Source\W3DDevice\GameClient\Shadow\W3DVolumetricShadow.cpp; current body gives 822B vs 824B retail.
// BFME's shadow geometry holds 0x34-byte mesh records and keeps the mesh
// count beyond the Zero Hour geometry layout.
struct BfmeUpdateGeometryMeshView
{
	unsigned char m_beforePoolSize[0x18];
	Int m_poolSize;
	unsigned char m_beforeMeshIndex[4];
	Int m_meshRobjIndex;
	unsigned char m_afterMeshIndex[0xc];
	unsigned char m_needsDeformedVertices;
};

struct BfmeUpdateVolumeStateView
{
	unsigned char m_beforeVisibleState[0x44];
	Int m_visibleState;
};

class Rva00914860PoolA
{
public:
	Bool allocate(Int count, Int extra);
};

class BfmeShadowMesh
{
public:
	virtual void v00(void); virtual void v01(void); virtual void v02(void);
	virtual void v03(void); virtual void v04(void); virtual void v05(void);
	virtual void v06(void); virtual void v07(void); virtual void v08(void);
	virtual void v09(void); virtual void v10(void); virtual void v11(void);
	virtual void v12(void); virtual void v13(void); virtual void v14(void);
	virtual void v15(void); virtual void v16(void); virtual void v17(void);
	virtual void v18(void); virtual void v19(void); virtual void v20(void);
	void Get_Deformed_Vertices(Vector3 *vertices);
};

struct BfmeVolumetricShadowUpdateLayout
{
	char m_bfmePrefix[0x6c];
	W3DShadowGeometry *m_geometry;
	RenderObjClass *m_robj;
	Real m_shadowLengthScale;
	Real m_robjExtent;
	Real m_extraExtrusionPadding;
	Geometry *m_shadowVolume[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DBufferManager::W3DVertexBufferSlot *m_shadowVolumeVB[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
	W3DVolumetricShadowRenderTask m_shadowVolumeRenderTask[MAX_SHADOW_LIGHTS][MAX_SHADOW_CASTER_MESHES];
};

/** Update shadow volumes belonging to all meshes of this shadow caster.
*	Use zoffset to extend shadows below object's base by given amount.
*/
// ?updateVolumes@W3DVolumetricShadow@@IAEXM@Z
void W3DVolumetricShadow::updateVolumes(Real zoffset)
{
	BfmeVolumetricShadowUpdateLayout *shadow =
		reinterpret_cast<BfmeVolumetricShadowUpdateLayout *>(this);
	RenderObjClass *robj = shadow->m_robj;
	Int i, j;
	HLodClass *hlod = (HLodClass *)robj;
	MeshClass *mesh;
	static AABoxClass aaBox;
	static SphereClass sphere;
	Int meshIndex;

	DEBUG_ASSERTCRASH(hlod != NULL, ("updateVolumes : hlod is NULL!"));
	Bool parentVis = robj->Is_Really_Visible();
	for (i = 0; i < MAX_SHADOW_LIGHTS; i++)
	{
		for (j = 0; j < reinterpret_cast<BfmeW3DShadowGeometryLayout *>(
			shadow->m_geometry)->m_meshCount; j++)
		{
			BfmeUpdateGeometryMeshView *meshRecord =
				reinterpret_cast<BfmeUpdateGeometryMeshView *>(
					reinterpret_cast<unsigned char *>(shadow->m_geometry) + 0x14 + j * 0x34);
			meshIndex = meshRecord->m_meshRobjIndex;
			if (meshIndex >= 0)
				mesh = (MeshClass *)hlod->Peek_Lod_Model(0, meshIndex);
			else
				mesh = (MeshClass *)robj;
			if (mesh)
			{
				if (!mesh->Is_Not_Hidden_At_All())
					continue;
				const Matrix3D *meshTransform = &mesh->Get_Transform();
				if (meshRecord->m_needsDeformedVertices &&
					!((BfmeMeshRenderObjView *)mesh)->Class_ID())
				{
					if (*(Int *)0x01306F44 < meshRecord->m_poolSize)
					{
						Rva00914860PoolA *pool =
							reinterpret_cast<Rva00914860PoolA *>(0x01306F3C);
						if (pool->allocate(meshRecord->m_poolSize, 0) &&
							*(Int *)0x01306F44 < *(Int *)0x01306F4C)
							*(Int *)0x01306F4C = *(Int *)0x01306F44;
					}
					((BfmeShadowMesh *)((BfmeMeshRenderObjView *)mesh)->Mesh_View_14())
						->Get_Deformed_Vertices((Vector3 *)*(void **)0x01306F40);
					*(void **)((unsigned char *)shadow->m_shadowVolume[0][j] + 8) =
						*(void **)0x01306F40;
					*(Int *)((unsigned char *)shadow->m_shadowVolume[0][j] + 0x10) = 0;
				}
				updateMeshVolume(j, i, meshTransform, mesh->Get_Bounding_Box(),
					robj->Get_Position().Z - zoffset);
				if (shadow->m_shadowVolume[i][j])
				{
					BfmeUpdateVolumeStateView *volumeState =
						reinterpret_cast<BfmeUpdateVolumeStateView *>(shadow->m_shadowVolume[i][j]);
					if (volumeState->m_visibleState == Geometry::STATE_UNKNOWN)
					{
						if (parentVis)
							volumeState->m_visibleState = Geometry::STATE_VISIBLE;
						else
						{
							sphere = shadow->m_shadowVolume[i][j]->getBoundingSphere();
							sphere.Center += mesh->Get_Transform().Get_Translation();
							CollisionMath::OverlapType result =
								CollisionMath::Overlap_Test(*shadowCameraFrustum, sphere);
							if (result == CollisionMath::OVERLAPPED)
							{
								aaBox = shadow->m_shadowVolume[i][j]->getBoundingBox();
								aaBox.Translate(mesh->Get_Transform().Get_Translation());
								if (CollisionMath::Overlap_Test(*shadowCameraFrustum, aaBox) != CollisionMath::OUTSIDE)
									volumeState->m_visibleState = Geometry::STATE_VISIBLE;
								else
									volumeState->m_visibleState = Geometry::STATE_INVISIBLE;
							}
							else
								volumeState->m_visibleState = result;
						}
					}
					if (volumeState->m_visibleState == Geometry::STATE_VISIBLE)
					{
						W3DBufferManager::W3DVertexBufferSlot *vbSlot =
							shadow->m_shadowVolumeVB[i][j];
						if (vbSlot)
						{
							W3DBufferManager::W3DRenderTask *oldTask = vbSlot->m_VB->m_renderTaskList;
							vbSlot->m_VB->m_renderTaskList = &shadow->m_shadowVolumeRenderTask[i][j];
							vbSlot->m_VB->m_renderTaskList->m_nextTask = oldTask;
						}
						else
							TheW3DVolumetricShadowManager->addDynamicShadowTask(
								&shadow->m_shadowVolumeRenderTask[i][j]);
					}
				}
			}
		}
	}
}

