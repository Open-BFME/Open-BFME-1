// ?updateVolumes@W3DVolumetricShadow@@IAEXM@Z
// partial score=0.55 date=2026-09-09
// Retail boundary: 0x007BF3C0, 824 bytes, ret 4.
//
// This is the complete real-C++ production experiment kept as research after
// the checkpoint probe.  The named W3DVolumetricShadow::Update caller proves
// the identity, and the local view recovers the observed BFME field offsets.
// It is not an exact conversion: the retail body still has BFME-specific
// global recursion setup and a deformed-mesh/helper branch absent from this
// upstream-shaped source.  The live TU was restored after this snapshot.

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

void W3DVolumetricShadow::updateVolumes(Real zoffset)
{
	W3DVolumetricShadow *self = this;
	BfmeVolumetricShadowUpdateLayout *shadow =
		reinterpret_cast<BfmeVolumetricShadowUpdateLayout *>(this);
	RenderObjClass *robj = shadow->m_robj;
	Int i,j;

	HLodClass *hlod=(HLodClass *)robj;
	MeshClass *mesh;
	static AABoxClass aaBox;
	static SphereClass sphere;
	Int meshIndex;

	DEBUG_ASSERTCRASH(hlod != NULL,("updateVolumes : hlod is NULL!"));

	Bool parentVis=robj->Is_Really_Visible();

	for( i = 0; i < MAX_SHADOW_LIGHTS; i++ )
	{
		for (j=0; j<shadow->m_geometry->getMeshCount(); j++)
		{
			meshIndex=shadow->m_geometry->getMesh(j)->m_meshRobjIndex;

			if (meshIndex >= 0)
				mesh = (MeshClass *)hlod->Peek_Lod_Model(0,meshIndex);
			else
				mesh = (MeshClass *)robj;

			if (mesh)
			{
				if (!mesh->Is_Not_Hidden_At_All())
					continue;

				// Extend floor of model by zoffset to compensate for flying units.
				self->updateMeshVolume(j, i, &mesh->Get_Transform(), mesh->Get_Bounding_Box(),robj->Get_Position().Z - zoffset);
				// Updating the mesh volume may leave visibility unknown.
				if (shadow->m_shadowVolume[i][j])
				{
					if(shadow->m_shadowVolume[i][j]->getVisibleState() == Geometry::STATE_UNKNOWN)
					{
						if (parentVis)
						{
							shadow->m_shadowVolume[i][j]->setVisibleState(Geometry::STATE_VISIBLE);
						}
						else
						{
							sphere=shadow->m_shadowVolume[i][j]->getBoundingSphere();
							sphere.Center += mesh->Get_Transform().Get_Translation();
							CollisionMath::OverlapType result=CollisionMath::Overlap_Test(*shadowCameraFrustum,sphere);
							if (result == CollisionMath::OVERLAPPED)
							{
								aaBox=shadow->m_shadowVolume[i][j]->getBoundingBox();
								aaBox.Translate(mesh->Get_Transform().Get_Translation());
								if (CollisionMath::Overlap_Test(*shadowCameraFrustum,aaBox) != CollisionMath::OUTSIDE)
									shadow->m_shadowVolume[i][j]->setVisibleState(Geometry::STATE_VISIBLE);
								else
									shadow->m_shadowVolume[i][j]->setVisibleState(Geometry::STATE_INVISIBLE);
							}
							else
								shadow->m_shadowVolume[i][j]->setVisibleState((Geometry::VisibleState)result);
						}
					}
					if (shadow->m_shadowVolume[i][j]->getVisibleState() == Geometry::STATE_VISIBLE)
					{
						W3DBufferManager::W3DVertexBufferSlot *vbSlot=shadow->m_shadowVolumeVB[i][j];
						if (vbSlot)
						{
							W3DBufferManager::W3DRenderTask *oldTask=vbSlot->m_VB->m_renderTaskList;
							vbSlot->m_VB->m_renderTaskList=&shadow->m_shadowVolumeRenderTask[i][j];
							vbSlot->m_VB->m_renderTaskList->m_nextTask=oldTask;
						}
						else
						{
							TheW3DVolumetricShadowManager->addDynamicShadowTask(&shadow->m_shadowVolumeRenderTask[i][j]);
						}
					}
				}
			}
		}
	}
}
