// ?Add_Mesh@DX8RigidFVFCategoryContainer@@UAEXPAVMeshModelClass@@@Z
// partial score=0.25 date=2026-09-20
// slot2/7 of DX8RigidFVFCategoryContainer vtable @0x0113D040. Continuing the 0.25 stash
// (3rd session on this body).
//
// PREREQUISITE RESOLVED THIS SESSION: the Vertex_Split_Table constructor at 0x00946FE0 is now
// independently LANDED (matched) by another lane as
// Code/Libraries/Source/WWVegas/WW3D2/VertexSplitTableConstructorBFME.cpp, using a
// __declspec(noinline) ctor plus a `force_vertex_split_table_constructor` anchor helper to keep
// it emitted. That resolves the prior sessions' blocker (declaring the ctor extern-only used to
// drop the class's only in-TU reference to `GapFillerClass::Get_Polygon_Array`, which orphaned
// the separately-matched ICF-folded row `?Get_Polygon_Array@GapFillerClass@@QBEPBVVector3i16@@XZ`
// at 0x0010BDB0, icf-owner=getDistributionType@GameClientRandomVariable).
//
// THIS SESSION: (1) changed dx8renderer.cpp's local Vertex_Split_Table class to DECLARE the
// constructor only (matching field layout: mmc, npatch_enable, polygon_count, polygon_array,
// allocated_polygon_array -- verified against VertexSplitTableConstructorBFME.cpp), deleting the
// stale inline body that still had ZH's gap_filler branch (retail BFME's real ctor has NO
// gap_filler branch at all -- confirmed independently in the prior blocked session's disasm of
// 0x00946FE0). (2) Rediscovered the SAME orphaning failure the 2nd session hit and root-caused
// it precisely via `./build.sh dx8renderer.cpp`: `FAIL ?Get_Polygon_Array@GapFillerClass...
// symbol not found in object`. (3) Fixed it for good with the SAME pattern the ctor's own file
// uses: added a `__declspec(noinline) force_gap_filler_get_polygon_array(const GapFillerClass*)`
// anchor function right after the Vertex_Split_Table class, documented as carrying no retail
// claim, whose only job is to keep that inline instantiation emitted now that nothing else in
// this TU calls it. `./build.sh dx8renderer.cpp` now reports Functions: OK 141/141 matched --
// the whole TU is clean, no more orphaning. This removes the prerequisite blocker for good; any
// future session can build straight from here without re-deriving it.
//
// BYTE STATE UNCHANGED: even with the ctor call now resolving correctly against the real
// 0x00946FE0 body, probe.py reports the SAME 1054B vs 1008B (46B over) result as the 2nd
// session's blocked verdict, with the same first divergence region. Retail:
//   +0029 lea ecx,[esp+0x48]        (address of the split_table local)
//   +0031 call 0x00946FE0           (Vertex_Split_Table ctor)
//   +0036 mov ebp,[esp+0x44]        (retail re-loads the object's address from a DIFFERENT
//                                    stack slot 4B below where it was computed -- looks like an
//                                    EH-bookkeeping/constructed-object shadow slot, given the
//                                    function's SEH frame and split_table's non-trivial dtor --
//                                    and keeps it live in EBP for the rest of the function)
//   +003a mov ecx,[esi+0xf0]        (vertex_buffer field, reordered ahead of the count read)
//   +0042 mov eax,[ebp+0x28]        (needed_vertices = split_table.Get_Vertex_Count(), via ebp)
// Ours computes the same value chain through ECX from a plain esp-relative slot (no ebp cache),
// one register/instruction-schedule step short throughout, consistent with the 2nd session's
// "frame/register lever not found" conclusion -- this is the ACTUAL dominant residue, not the
// ctor ICF issue, which only masked it.
//
// LEVERS TRIED THIS SESSION (both exhausted, no improving candidate):
//   - `python3 tools/eh_levers.py dx8renderer.cpp` (6 choices: throw() on 4 unrelated calls in
//     OTHER functions in this shared TU, plus the file's cl: EHsc/EHsc- toggle) fed through
//     shape_search.py (11 trials) -- no improvement; the EH state-store choices it generates
//     don't touch Add_Mesh's actual EH-shadow-slot/ebp residue at all.
//   - `python3 tools/shape_family_levers.py dx8renderer.cpp --families
//     sib,register,bool,test,copy,store,loop,branch,constant,frame` (30 choices, all elsewhere
//     in the file) through shape_search.py (9 trials) -- no improvement.
// Neither tool's choice generator currently produces anything that reaches a local-object
// address materialization / EH-shadow-slot choice like this one; that class of residue may need
// a hand-authored source variant (e.g. taking `&split_table`'s address explicitly early, or an
// RAII-wrapper shape) that neither lever family currently models. Flagging for the next session:
// try explicitly declaring `Vertex_Split_Table *sp = &split_table;` immediately after
// construction and routing every later `split_table.X()` call through `sp->X()`, and/or hand
// vary whether `needed_vertices` is computed before/after the `if (!vertex_buffer)` block.
// compiled 1054B vs target 1008B (46B over, unchanged since the 2nd session). t=45min
// model=claude-sonnet-5 score=0.25

// ---- Excerpt from Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.cpp (current tree state) ----
// (BfmeC998/Get_Vertex_Normal_Array pointer-to-member trick, BfmeFVFInfo layout struct, and all
// surrounding present-unmatched sibling functions in the same TU are unchanged from before;
// only Vertex_Split_Table's constructor and the new anchor function are new this session.)

class Vertex_Split_Table
{
	MeshModelClass* mmc;
	bool npatch_enable;
	unsigned polygon_count;
	TriIndex* polygon_array;

	bool allocated_polygon_array;

public:
	// Retail out-of-line constructor: matched separately at 0x00946FE0
	// (Code/Libraries/Source/WWVegas/WW3D2/VertexSplitTableConstructorBFME.cpp).
	// BFME retail dropped ZH's gap-filler support here (single unconditional
	// polygon-array memcpy, no gap_filler branch); declare only, do not redefine.
	Vertex_Split_Table(MeshModelClass* mmc_);

	~Vertex_Split_Table()
	{
		if (allocated_polygon_array) {
			delete[] polygon_array;
		}
	}

	const Vector3* Get_Vertex_Array() const
	{
		return (*reinterpret_cast<ShareBufferClass<Vector3> * const *>(reinterpret_cast<const char *>(mmc)+0x30))->Get_Array();
	}

	const Vector3* Get_Vertex_Normal_Array() const
	{
		union {
			void (BfmeC998::*void_function)(int);
			const Vector3 *(BfmeC998::*normal_function)(int);
		} function;
		function.void_function=&BfmeC998::bfmeGo998C;
		return (((BfmeC998 *)mmc)->*function.normal_function)(0);
	}

	const unsigned* Get_Color_Array(unsigned index) const
	{
		return mmc->Get_Color_Array(index,false);
	}

	const Vector2* Get_UV_Array(unsigned uv_array_index) const
	{
		return mmc->Get_UV_Array_By_Index(uv_array_index);
	}

	const unsigned& Get_Vertex_Count() const
	{
		return *reinterpret_cast<const unsigned *>(reinterpret_cast<const char *>(mmc)+0x28);
	}

	unsigned Get_Polygon_Count() const
	{
		return polygon_count;
	}

	unsigned Get_Pass_Count() const
	{
		return mmc->Get_Pass_Count();
	}

	TextureClass* Peek_Texture(unsigned idx,unsigned pass,unsigned stage)
	{
		if (mmc->Has_Texture_Array(pass,stage)) {
			if (idx>=unsigned(mmc->Get_Polygon_Count())) {
				WWASSERT(mmc->Get_Gap_Filler());
				return mmc->Get_Gap_Filler()->Get_Texture_Array(pass,stage)[idx-mmc->Get_Polygon_Count()];
			}
			return mmc->Peek_Texture(idx,pass,stage);
		}
		return mmc->Peek_Single_Texture(pass,stage);
	}

	VertexMaterialClass* Peek_Material(unsigned idx,unsigned pass)
	{
		if (mmc->Has_Material_Array(pass)) {
			if (idx>=unsigned(mmc->Get_Polygon_Count())) {
				WWASSERT(mmc->Get_Gap_Filler());
				return mmc->Get_Gap_Filler()->Get_Material_Array(pass)[idx-mmc->Get_Polygon_Count()];
			}
			return mmc->Peek_Material(mmc->Get_Polygon_Array()[idx][0],pass);
		}
		return mmc->Peek_Single_Material(pass);
	}

	ShaderClass Peek_Shader(unsigned idx,unsigned pass)
	{
		if (mmc->Has_Shader_Array(pass)) {
			// BFME's MeshGeometry stores PolyCount at this+0x24.  The shared
			// header carries the later Zero Hour member order, so this TU-local
			// read keeps the renderer's retail ABI without changing that header.
			ShaderClass shader(0x0010441b);
			if (idx < *reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(mmc)+0x24)) {
				shader=mmc->Get_Shader(idx,pass);
			}

			if (npatch_enable) {
				shader.Set_NPatch_Enable(ShaderClass::NPATCH_ENABLE);
			}

			return shader;
		}
		if (!npatch_enable) return mmc->Get_Single_Shader(pass);
		ShaderClass shader=mmc->Get_Single_Shader(pass);
		shader.Set_NPatch_Enable(ShaderClass::NPATCH_ENABLE);
		return shader;

	}

	MeshModelClass* Get_Mesh_Model_Class()
	{
		return mmc;
	}

	unsigned short* Get_Polygon_Array(unsigned pass)
	{
		return (unsigned short*)polygon_array;
	}
};

// Emission anchor for ?Get_Polygon_Array@GapFillerClass@@QBEPBVVector3i16@@XZ
// (matched, RVA 0x0010BDB0, icf-owner getDistributionType@GameClientRandomVariable).
// No retail claim. The corrected Vertex_Split_Table constructor (0x00946FE0,
// landed separately in VertexSplitTableConstructorBFME.cpp) no longer calls
// this, since retail BFME dropped ZH's gap-filler branch there; without another
// live call site in this TU the inline instantiation stops being emitted and
// the ICF-folded match above fails to link.
__declspec(noinline) const TriIndex *force_gap_filler_get_polygon_array(const GapFillerClass *gf)
{
	return gf->Get_Polygon_Array();
}

// ----------------------------------------------------------------------------

class BfmeFVFInfo
{
public:
	unsigned FVF;
	unsigned fvf_size;
	unsigned location_offset;
	unsigned normal_offset;
	unsigned blend_offset;
	unsigned texcoord_offset[8];
	unsigned diffuse_offset;
	unsigned specular_offset;
	unsigned bfme_fvf_info_tail;

	unsigned Get_Location_Offset() const { return location_offset; }
	unsigned Get_Normal_Offset() const { return normal_offset; }
	unsigned Get_Tex_Offset(unsigned n) const { return texcoord_offset[n]; }
	unsigned Get_Diffuse_Offset() const { return diffuse_offset; }
	unsigned Get_Specular_Offset() const { return specular_offset; }
	unsigned Get_FVF_Size() const { return fvf_size; }
};

// ?Add_Mesh@DX8RigidFVFCategoryContainer@@UAEXPAVMeshModelClass@@@Z present-unmatched
void DX8RigidFVFCategoryContainer::Add_Mesh(MeshModelClass* mmc_)
{
	WWASSERT(Check_If_Mesh_Fits(mmc_));

	Vertex_Split_Table split_table(mmc_);
	int needed_vertices=split_table.Get_Vertex_Count();

	/*
	** This FVFCategoryContainer doesn't have a vertex buffer yet so allocate one big
	** enough to contain this mesh.
	*/
	if (!vertex_buffer) {
		int vb_size=4000;
		if (vb_size<needed_vertices) vb_size=needed_vertices;
		if (sorting) {
			vertex_buffer=NEW_REF(SortingVertexBufferClass,(vb_size));
			WWASSERT(vertex_buffer->FVF_Info().Get_FVF()==FVF);	// Only one sorting FVF type!
		}
		else {
			vertex_buffer=NEW_REF(DX8VertexBufferClass,(
				FVF,
				vb_size,
				(*(const unsigned char*)((const char*)DX8Wrapper::Get_Current_Caps()+0x13b) && WW3D::Get_NPatches_Level()>1) ? DX8VertexBufferClass::USAGE_NPATCHES : DX8VertexBufferClass::USAGE_DEFAULT));
		}
	}

	/*
	** Append this mesh's vertices to the vertex buffer.
	*/

	VertexBufferClass::AppendLockClass l(vertex_buffer,used_vertices,split_table.Get_Vertex_Count());
	const BfmeFVFInfo fi=*(const BfmeFVFInfo*)&vertex_buffer->FVF_Info();
	unsigned char *vb=(unsigned char*) l.Get_Vertex_Array();
	unsigned int i;
	const Vector3 *locs=split_table.Get_Vertex_Array();
	const Vector3 *norms=split_table.Get_Vertex_Normal_Array();
	const unsigned *diffuse=split_table.Get_Color_Array(0);
	const unsigned *specular=split_table.Get_Color_Array(1);
	for (i=0; i<split_table.Get_Vertex_Count(); i++)
	{
		*(Vector3*)(vb+fi.Get_Location_Offset())=locs[i];

		if ((FVF&D3DFVF_NORMAL)==D3DFVF_NORMAL && norms) {
			*(Vector3*)(vb+fi.Get_Normal_Offset())=norms[i];
		}

		if ((FVF&D3DFVF_DIFFUSE)==D3DFVF_DIFFUSE) {
			if (diffuse) {
				*(unsigned int*)(vb+fi.Get_Diffuse_Offset())=diffuse[i];
			} else {
				*(unsigned int*)(vb+fi.Get_Diffuse_Offset()) = 0xFFFFFFFF;
			}
		}

		if ((FVF&D3DFVF_SPECULAR)==D3DFVF_SPECULAR) {
			if (specular) {
				*(unsigned int*)(vb+fi.Get_Specular_Offset())=specular[i];
			} else {
				*(unsigned int*)(vb+fi.Get_Specular_Offset()) = 0xFFFFFFFF;
			}
		}

		vb+=fi.Get_FVF_Size();
	}


	/*
	** Append the UV coordinates to the vertex buffer
	*/
	int uvcount = 0;
	if ((FVF&D3DFVF_TEX1) == D3DFVF_TEX1) {
		uvcount = 1;
	}
	if ((FVF&D3DFVF_TEX2) == D3DFVF_TEX2) {
		uvcount = 2;
	}
	if ((FVF&D3DFVF_TEX3) == D3DFVF_TEX3) {
		uvcount = 3;
	}
	if ((FVF&D3DFVF_TEX4) == D3DFVF_TEX4) {
		uvcount = 4;
	}
	if ((FVF&D3DFVF_TEX5) == D3DFVF_TEX5) {
		uvcount = 5;
	}
	if ((FVF&D3DFVF_TEX6) == D3DFVF_TEX6) {
		uvcount = 6;
	}
	if ((FVF&D3DFVF_TEX7) == D3DFVF_TEX7) {
		uvcount = 7;
	}
	if ((FVF&D3DFVF_TEX8) == D3DFVF_TEX8) {
		uvcount = 8;
	}

	for (int j=0; j<uvcount; j++) {
		unsigned char *vb=(unsigned char*) l.Get_Vertex_Array();
		const Vector2*uvs=split_table.Get_UV_Array(j);
		if (uvs) {
			for (i=0; i<split_table.Get_Vertex_Count(); i++)
			{
				*(Vector2*)(vb+fi.Get_Tex_Offset(j))=uvs[i];
				vb+=fi.Get_FVF_Size();
			}
		}
	}

	Generate_Texture_Categories(split_table,used_vertices);

	used_vertices+=needed_vertices;//vertex_count;
}
