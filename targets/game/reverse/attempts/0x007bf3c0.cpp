// ?updateVolumes@W3DVolumetricShadow@@IAEXM@Z
// partial score=0.66 date=2026-09-26
class Rva007BF3C0VisibilityView { public:
virtual void slot_00(void);
virtual void slot_01(void);
virtual void slot_02(void);
virtual void slot_03(void);
virtual void slot_04(void);
virtual void slot_05(void);
virtual void slot_06(void);
virtual void slot_07(void);
virtual void slot_08(void);
virtual void slot_09(void);
virtual void slot_10(void);
virtual void slot_11(void);
virtual void slot_12(void);
virtual void slot_13(void);
virtual void slot_14(void);
virtual void slot_15(void);
virtual void slot_16(void);
virtual void slot_17(void);
virtual void slot_18(void);
virtual void slot_19(void);
virtual void Validate_Transform(void) const;
virtual void slot_21(void);
virtual void slot_22(void);
virtual void slot_23(void);
virtual void slot_24(void);
virtual void slot_25(void);
virtual void slot_26(void);
virtual void slot_27(void);
virtual void slot_28(void);
virtual void slot_29(void);
virtual void slot_30(void);
virtual void slot_31(void);
virtual void slot_32(void);
virtual void slot_33(void);
virtual void slot_34(void);
virtual void slot_35(void);
virtual void slot_36(void);
virtual void slot_37(void);
virtual void slot_38(void);
virtual void slot_39(void);
virtual void slot_40(void);
virtual void slot_41(void);
virtual void slot_42(void);
virtual void slot_43(void);
virtual void slot_44(void);
virtual void slot_45(void);
virtual void slot_46(void);
virtual void slot_47(void);
virtual void slot_48(void);
virtual void slot_49(void);
virtual void slot_50(void);
virtual void slot_51(void);
virtual void slot_52(void);
virtual void slot_53(void);
virtual void slot_54(void);
virtual void slot_55(void);
virtual void slot_56(void);
virtual void slot_57(void);
virtual void slot_58(void);
virtual void slot_59(void);
virtual void slot_60(void);
virtual void slot_61(void);
virtual void slot_62(void);
virtual void slot_63(void);
virtual void slot_64(void);
virtual void slot_65(void);
virtual void slot_66(void);
virtual void slot_67(void);
virtual void slot_68(void);
virtual void slot_69(void);
virtual void slot_70(void);
virtual void slot_71(void);
virtual void slot_72(void);
virtual void slot_73(void);
virtual void slot_74(void);
virtual void slot_75(void);
virtual void slot_76(void);
virtual void slot_77(void);
virtual void slot_78(void);
virtual void slot_79(void);
virtual void slot_80(void);
virtual void slot_81(void);
virtual void slot_82(void);
virtual void slot_83(void);
virtual void slot_84(void);
virtual void slot_85(void);
virtual void slot_86(void);
virtual void slot_87(void);
virtual void slot_88(void);
virtual void slot_89(void);
virtual void slot_90(void);
virtual void slot_91(void);
virtual void slot_92(void);
virtual void slot_93(void);
virtual void slot_94(void);
virtual Int Is_Really_Visible(void);
virtual Int Is_Not_Hidden_At_All(void);
char m_prefix[0x14]; Matrix3D m_transform;
const Matrix3D &Get_Transform(void) const { Validate_Transform(); return m_transform; }
};
struct BfmeUpdateGeometryMeshView
{
	unsigned char m_beforeMeshIndex[0xc];
	Int m_meshRobjIndex;
	unsigned char m_beforePoolSize[8];
	Int m_poolSize;
	unsigned char m_afterPoolSize[0x14];
	unsigned char m_needsDeformedVertices;
};

struct BfmeUpdateGeometryView {
	unsigned char m_prefix[0x14];
	BfmeUpdateGeometryMeshView m_meshList[160];
	Int m_meshCount;
	BfmeUpdateGeometryMeshView *getMesh(Int j) { return &m_meshList[j]; }
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
	Int i, j;
	HLodClass *hlod = (HLodClass *)shadow->m_robj;
	MeshClass *mesh;
	static AABoxClass aaBox;
	static SphereClass sphere;
	Int meshIndex;

	DEBUG_ASSERTCRASH(hlod != NULL, ("updateVolumes : hlod is NULL!"));
	Bool parentVis = ((Rva007BF3C0VisibilityView *)shadow->m_robj)->Is_Really_Visible();
	for (i = 0; i < MAX_SHADOW_LIGHTS; i++)
	{
		for (j = 0; j < reinterpret_cast<BfmeUpdateGeometryView *>(shadow->m_geometry)->m_meshCount; j++)
		{
			meshIndex = reinterpret_cast<BfmeUpdateGeometryView *>(shadow->m_geometry)->getMesh(j)->m_meshRobjIndex;
			if (meshIndex >= 0)
				mesh = (MeshClass *)((BfmeHLodRenderObjView *)hlod)->Peek_Lod_Model(0, meshIndex);
			else
				mesh = (MeshClass *)shadow->m_robj;
			if (mesh)
			{
				if (!((Rva007BF3C0VisibilityView *)mesh)->Is_Not_Hidden_At_All())
					continue;
				BfmeUpdateGeometryMeshView *meshRecord = reinterpret_cast<BfmeUpdateGeometryView *>(shadow->m_geometry)->getMesh(j);
				const Matrix3D *meshTransform = &((Rva007BF3C0VisibilityView *)mesh)->Get_Transform();
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
					shadow->m_robj->Get_Position().Z - zoffset);
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
							sphere.Center += ((Rva007BF3C0VisibilityView *)mesh)->Get_Transform().Get_Translation();
							CollisionMath::OverlapType result =
								CollisionMath::Overlap_Test(*shadowCameraFrustum, sphere);
							if (result == CollisionMath::OVERLAPPED)
							{
								aaBox = shadow->m_shadowVolume[i][j]->getBoundingBox();
								aaBox.Translate(((Rva007BF3C0VisibilityView *)mesh)->Get_Transform().Get_Translation());
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

