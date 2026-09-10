// ?Render@MeshClass@@UAEXAAVRenderInfoClass@@@Z
// partial score=0.66 date=2026-09-10
// MeshClass::Render @ 0x0092E4B0; complete clean-C++ near-match scratch.
// The surrounding TU supplies the production WW3D2 declarations.
extern unsigned char g_Va0133F42C;
extern float g_01076C24;

class Rva00923770
{
public:
	void * get(int index);
};

void MeshClass::Render(RenderInfoClass & rinfo)
{
	unsigned int sort_level;

	if (g_Va0133F42C) {
		if (Model == NULL) {
			return;
		}

		if (Model->MatInfo == NULL) {
			return;
		}

		MaterialInfoClass * material_info = Model->MatInfo;
		VertexMaterialClass * material = material_info->Peek_Vertex_Material(0);
		if (material == NULL) {
			return;
		}

		Vector3 emissive;
		material->Get_Emissive(&emissive);
		if (emissive.X <= g_01076C24 &&
			emissive.Y <= g_01076C24 &&
			emissive.Z <= g_01076C24) {
			return;
		}
	}

	if (Is_Not_Hidden_At_All() == false) {
		return;
	}

	sort_level = (unsigned int)Model->Get_Sort_Level();

	if (WW3D::Are_Static_Sort_Lists_Enabled() && sort_level != SORT_LEVEL_NONE) {
		Set_Lighting_Environment(rinfo.light_environment);
		m_alphaOverride = rinfo.alphaOverride;
		m_materialPassAlphaOverride = rinfo.materialPassAlphaOverride;
		m_materialPassEmissiveOverride = rinfo.materialPassEmissiveOverride;
		WW3D::Add_To_Static_Sort_List(this, sort_level);
	} else {
		const FrustumClass & frustum = rinfo.Camera.Get_Frustum();

		if (Model->Get_Flag(MeshGeometryClass::SKIN) ||
			CollisionMath::Overlap_Test(frustum, Get_Bounding_Box()) != CollisionMath::OUTSIDE) {
			bool rendered_something = false;

			if (Model->PolygonRendererList.Is_Empty()) {
				Model->Register_For_Rendering();
				WWASSERT(!Model->PolygonRendererList.Is_Empty());
			}

			if (sort_level == SORT_LEVEL_NONE) {
				Set_Lighting_Environment(rinfo.light_environment);
				m_alphaOverride = rinfo.alphaOverride;
				m_materialPassAlphaOverride = rinfo.materialPassAlphaOverride;
				m_materialPassEmissiveOverride = rinfo.materialPassEmissiveOverride;
			}

			DX8FVFCategoryContainer * fvf_container =
				Model->PolygonRendererList.Peek_Head()->Get_Texture_Category()->Get_Container();
			bool render_base_passes =
				((rinfo.Current_Override_Flags() & RenderInfoClass::RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY) == 0);
			bool is_alpha =
				(Model->Get_Single_Shader().Get_Alpha_Test() == ShaderClass::ALPHATEST_ENABLE) ||
				(Model->Get_Single_Shader().Get_Src_Blend_Func() == ShaderClass::SRCBLEND_SRC_ALPHA);

			if ((rinfo.Current_Override_Flags() & RenderInfoClass::RINFO_OVERRIDE_SHADOW_RENDERING) &&
				is_alpha == true) {
				render_base_passes = true;
			}

			if (render_base_passes) {
				DX8PolygonRendererListIterator it(&(Model->PolygonRendererList));
				while (!it.Is_Done()) {
					DX8PolygonRendererClass * polygon_renderer = it.Peek_Obj();
					polygon_renderer->Get_Texture_Category()->Add_Render_Task(polygon_renderer, this);
					it.Next();
				}
				rendered_something = true;
			}

			for (int i = 0; i < rinfo.Additional_Pass_Count(); i++) {
				MaterialPassClass * matpass = rinfo.Peek_Additional_Pass(i);
				if ((!Is_Translucent()) || matpass->Is_Enabled_On_Translucent_Meshes()) {
					if (rinfo.Current_Override_Flags() & RenderInfoClass::RINFO_OVERRIDE_ADDITIONAL_PASSES_ONLY) {
						fvf_container->Add_Delayed_Visible_Material_Pass(matpass, this);
					} else {
						fvf_container->Add_Visible_Material_Pass(matpass, this);
					}
					rendered_something = true;
				}
			}

			for (int i = 0; i < *(int *)((char *)&rinfo + 0x1b0); i++) {
				MaterialPassClass * matpass = static_cast<MaterialPassClass *>(
					reinterpret_cast<Rva00923770 *>(&rinfo)->get(i));
				if (matpass != NULL &&
					((!Is_Translucent()) || matpass->Is_Enabled_On_Translucent_Meshes())) {
					fvf_container->Add_Delayed_Visible_Material_Pass(matpass, this);
					rendered_something = true;
				}
			}

			if (rendered_something && Model->Get_Flag(MeshGeometryClass::SKIN)) {
				static_cast<DX8SkinFVFCategoryContainer *>(fvf_container)->Add_Visible_Skin(this);
			}
		}
	}
}
