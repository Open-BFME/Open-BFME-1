// ?Render@DX8SkinFVFCategoryContainer@@UAEXXZ
// partial score=0.429 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;
extern const float g_bfmeScaleB3;


class BoxDynamicVBAccessClass
{
	const FVFInfoClass &FVFInfo;
	unsigned Type;
	unsigned FVF;
	unsigned Start;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	VertexBufferClass *VertexBuffer;

public:
	BoxDynamicVBAccessClass(unsigned type,unsigned fvf,unsigned short vertex_count,unsigned start);
	~BoxDynamicVBAccessClass();

	class WriteLockClass
	{
		BoxDynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;
	public:
		WriteLockClass(BoxDynamicVBAccessClass *vb_access);
		~WriteLockClass();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

struct DX8SkinFVFCategoryContainer_BFME_Retail_VisibleSkinFieldsAt94A320
{
	unsigned char pad[0xf0];
	unsigned int visibleVertexCount;
	unsigned int visibleSkinCount;
	MeshClass *visibleSkinHead;
	MeshClass *visibleSkinTail;
};

struct DX8SkinRenderMeshRuntimeData
{
	MeshClass *Parent;
};

struct DX8SkinRenderMeshBFMEFields
{
	unsigned char pad[0x314];
	DX8SkinRenderMeshRuntimeData *RuntimeData;
};


void DX8SkinFVFCategoryContainer::Render(void)
{
	static DynamicVectorClass<Vector3> renderTempVertexBuffer;
	static DynamicVectorClass<Vector3> renderTempNormalBuffer;
	DX8SkinFVFCategoryContainer_BFME_Retail_VisibleSkinFieldsAt94A320 *fields =
		reinterpret_cast<DX8SkinFVFCategoryContainer_BFME_Retail_VisibleSkinFieldsAt94A320 *>(this);

	SNAPSHOT_SAY(("DX8SkinFVFCategoryContainer::Render()\n"));
	if (!Anything_To_Render()) {
		SNAPSHOT_SAY(("Nothing to render\n"));
		return;
	}
	AnythingToRender=false;
	DX8Wrapper::Set_Vertex_Buffer(NULL);

	unsigned int maxVertexCount=fields->visibleVertexCount;
	if (maxVertexCount > 65535)
		maxVertexCount = 65535;

	BoxDynamicVBAccessClass vb(
		sorting ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8,
		5,
		maxVertexCount,
		0);
	SNAPSHOT_SAY(("DynamicVBAccess - %s - %d vertices\n",sorting ? "sorting" : "non-sorting",fields->visibleVertexCount));

	unsigned int renderedVertexCount=0;
	MeshClass * mesh = fields->visibleSkinHead;
	MeshClass * remainingMesh = fields->visibleSkinHead;
	while (renderedVertexCount < fields->visibleVertexCount)
	{
		mesh = remainingMesh;
		{
			BoxDynamicVBAccessClass::WriteLockClass l(&vb);
			VertexFormatXYZNDUV2 * dest_verts = l.Get_Formatted_Vertex_Array();
			unsigned vertex_offset=0;
			remainingMesh = NULL;
			while (mesh != NULL) {
				MeshModelClass * mmc = mesh->Peek_Model();
				int mesh_vertex_count=mmc->Get_Vertex_Count();
				if (vertex_offset+mesh_vertex_count > maxVertexCount || remainingMesh)
				{
					mesh->Set_Base_Vertex_Offset(VERTEX_BUFFER_OVERFLOW);
					if (remainingMesh == NULL)
						remainingMesh = mesh;
					mesh = mesh->Peek_Next_Visible_Skin();
					continue;
				}

				WWASSERT((vertex_offset+mesh_vertex_count)<=fields->visibleVertexCount);
				DX8SkinRenderMeshBFMEFields *meshFields =
					reinterpret_cast<DX8SkinRenderMeshBFMEFields *>(mesh);
				if (meshFields->RuntimeData != NULL && meshFields->RuntimeData->Parent != NULL) {
					Debug_Statistics::Record_Sorting_Polys_And_Vertices(mesh->Get_Num_Polys(),mesh_vertex_count);
					mesh->Set_Base_Vertex_Offset(meshFields->RuntimeData->Parent->Get_Base_Vertex_Offset());
					renderedVertexCount += mesh_vertex_count;
				}
				else {
					Debug_Statistics::Record_Sorting_Polys_And_Vertices(mesh->Get_Num_Polys(),mesh_vertex_count);
					if (renderTempVertexBuffer.Length() < mesh_vertex_count) renderTempVertexBuffer.Resize(mesh_vertex_count);
					if (renderTempNormalBuffer.Length() < mesh_vertex_count) renderTempNormalBuffer.Resize(mesh_vertex_count);
					Vector3* loc=&(renderTempVertexBuffer[0]);
					Vector3* norm=&(renderTempNormalBuffer[0]);
					const Vector2* uv0=mmc->Get_UV_Array_By_Index(0);
					const Vector2* uv1=mmc->Get_UV_Array_By_Index(1);
					const unsigned* diffuse=mmc->Get_Color_Array(0,false);
					VertexFormatXYZNDUV2* verts=dest_verts+vertex_offset;
					mesh->Get_Deformed_Vertices(loc,norm);
					for (int v=0;v<mesh_vertex_count;++v) {
						verts[v].x=(*loc)[0];
						verts[v].y=(*loc)[1];
						verts[v].z=(*loc)[2];
						verts[v].nx=(*norm)[0];
						verts[v].ny=(*norm)[1];
						verts[v].nz=(*norm)[2];
						if (diffuse) verts[v].diffuse=*diffuse++;
						else verts[v].diffuse=0;
						if (uv0) { verts[v].u1=(*uv0)[0]; verts[v].v1=(*uv0)[1]; uv0++; }
						else { verts[v].u1=0.0f; verts[v].v1=0.0f; }
						if (uv1) { verts[v].u2=(*uv1)[0]; verts[v].v2=(*uv1)[1]; uv1++; }
						else { verts[v].u2=0.0f; verts[v].v2=0.0f; }
						loc++;
						norm++;
					}
					if (mesh->_bfme_ro_get_98() > BfmeZeroRange) {
						mesh->_bfme_ro_get_98();
					}
					else {
						float alpha = mesh->Get_Alpha_Override();
						if (alpha != g_bfmeDefaultBU) {
							alpha *= g_bfmeScaleB3;
							unsigned alpha_value = (unsigned)alpha << 24;
							for (int v=0;v<mesh_vertex_count;++v) {
								verts->diffuse = (verts->diffuse & 0x00ffffff) | alpha_value;
								++verts;
							}
						}
					}
					mesh->Set_Base_Vertex_Offset(vertex_offset);
					if (meshFields->RuntimeData != NULL)
						meshFields->RuntimeData->Parent = mesh;
					vertex_offset+=mesh_vertex_count;
					renderedVertexCount += mesh_vertex_count;
				}
				mesh = mesh->Peek_Next_Visible_Skin();
			}
		}
		DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&vb));
		DX8Wrapper::Set_Index_Buffer(index_buffer,0);
		for (unsigned pass=0;pass<passes;++pass) {
			TextureCategoryListIterator it(&visible_texture_category_list[pass]);
			while (!it.Is_Done()) {
				it.Peek_Obj()->Render();
				it.Next();
			}
		}
		Render_Procedural_Material_Passes();
	}
	for (unsigned pass=0;pass<passes;++pass) {
		while (DX8TextureCategoryClass * tex = visible_texture_category_list[pass].Remove_Head()) {
		}
	}
	WWASSERT(renderedVertexCount==fields->visibleVertexCount);
	clearVisibleSkinList();
}
