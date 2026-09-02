// ?Draw@DX8Wrapper@@CAXHGGGGH@Z
// partial score=0.48 date=2026-09-02
// cl: /DNDEBUG /MD /GR-
// ?Draw@DX8Wrapper@@CAXHGGGGH@Z
// Retail 0x00906B40 size 526. BFME Draw: low-bound cull, optional material
// diffuse-black skip, Apply_Render_State_Changes, triangle-draw enable,
// snapshot ValidateDevice, then DrawPrimitive (last arg 0) or indexed/sorting.

class Vector3
{
public:
	float X, Y, Z;
};

class VertexMaterialClass
{
public:
	void Get_Diffuse(Vector3 *out);
};

class ShaderClass
{
	unsigned dummy;
};

class VertexBufferClass
{
public:
	unsigned short Get_Vertex_Count(void);
};

class IDirect3DDevice8
{
public:
	virtual void v00(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual void v06(void);
	virtual void v07(void);
	virtual void v08(void);
	virtual void v09(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual void v15(void);
	virtual void v16(void);
	virtual void v17(void);
	virtual void v18(void);
	virtual void v19(void);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual void v26(void);
	virtual void v27(void);
	virtual void v28(void);
	virtual void v29(void);
	virtual void v30(void);
	virtual void v31(void);
	virtual void v32(void);
	virtual void v33(void);
	virtual void v34(void);
	virtual void v35(void);
	virtual void v36(void);
	virtual void v37(void);
	virtual void v38(void);
	virtual void v39(void);
	virtual void v40(void);
	virtual void v41(void);
	virtual void v42(void);
	virtual void v43(void);
	virtual void v44(void);
	virtual void v45(void);
	virtual void v46(void);
	virtual void v47(void);
	virtual void v48(void);
	virtual void v49(void);
	virtual void v50(void);
	virtual void v51(void);
	virtual void v52(void);
	virtual void v53(void);
	virtual void v54(void);
	virtual void v55(void);
	virtual void v56(void);
	virtual void v57(void);
	virtual void v58(void);
	virtual void v59(void);
	virtual void v60(void);
	virtual void v61(void);
	virtual void v62(void);
	virtual void v63(void);
	virtual void v64(void);
	virtual void v65(void);
	virtual void v66(void);
	virtual void v67(void);
	virtual void v68(void);
	virtual void v69(void);
	virtual void ValidateDevice(unsigned long *passes);
	virtual void v71(void);
	virtual void v72(void);
	virtual void v73(void);
	virtual void v74(void);
	virtual void v75(void);
	virtual void v76(void);
	virtual void v77(void);
	virtual void v78(void);
	virtual void v79(void);
	virtual void v80(void);
	virtual void DrawPrimitive(unsigned type, unsigned start, unsigned count);
	virtual void DrawIndexedPrimitive(unsigned type, unsigned minvert, unsigned numvert, unsigned start, unsigned count);
};

class Debug_Statistics
{
public:
	static void Record_DX8_Polys_And_Vertices(int polys, int verts, const ShaderClass &shader);
};

void Draw_Sorting_IB_VB(int type, unsigned short start, unsigned short polys, unsigned short minvert, unsigned short verts);

extern unsigned DrawPolygonLowBoundLimit;
extern char g_materialSkipFlag;
extern VertexMaterialClass *g_renderStateMaterial;
extern float g_diffuseSkipLimit;
extern char _EnableTriangleDraw;
extern char g_snapshotActivated;
extern IDirect3DDevice8 *g_d3dDevice;
extern unsigned g_vertexBufferType;
extern unsigned g_indexBufferType;
extern VertexBufferClass *g_vertexBuffer;
extern unsigned short g_indexBaseOffset;
extern unsigned g_vbaOffset;
extern unsigned short g_vbaCount;
extern unsigned short g_ibaOffset;
extern ShaderClass g_renderStateShader;
extern unsigned g_renderStats;
extern unsigned g_drawCalls;

class DX8Wrapper
{
public:
	static void Apply_Render_State_Changes(void);
private:
	static void Draw(int primitive_type, unsigned short start_index, unsigned short polygon_count, unsigned short min_vertex_index, unsigned short vertex_count, int apply_render_state);
};

void DX8Wrapper::Draw(int primitive_type, unsigned short start_index, unsigned short polygon_count, unsigned short min_vertex_index, unsigned short vertex_count, int apply_render_state)
{
	if (DrawPolygonLowBoundLimit && DrawPolygonLowBoundLimit >= polygon_count)
		return;

	if (g_materialSkipFlag) {
		VertexMaterialClass *mat = g_renderStateMaterial;
		if (!mat)
			return;
		float dx, dy, dz;
		mat->Get_Diffuse((Vector3 *)&dx);
		if (dx < g_diffuseSkipLimit && dy < g_diffuseSkipLimit && dz < g_diffuseSkipLimit)
			return;
	}

	Apply_Render_State_Changes();

	if (!_EnableTriangleDraw)
		return;

	if (g_snapshotActivated) {
		unsigned long passes = 0;
		g_d3dDevice->ValidateDevice(&passes);
	}

	unsigned vb_type = g_vertexBufferType;
	if (vertex_count < 3) {
		min_vertex_index = 0;
		switch (vb_type) {
		case 0:
		case 1:
			vertex_count = (unsigned short)(g_vertexBuffer->Get_Vertex_Count() - g_indexBaseOffset - g_vbaOffset);
			break;
		case 2:
		case 3:
			vertex_count = g_vbaCount;
			break;
		}
	}

	if (!apply_render_state) {
		Debug_Statistics::Record_DX8_Polys_And_Vertices(polygon_count, vertex_count, g_renderStateShader);
		g_renderStats++;
		g_d3dDevice->DrawPrimitive(primitive_type, min_vertex_index, polygon_count);
		g_drawCalls++;
		return;
	}

	switch (vb_type) {
	case 0:
	case 2:
		if (g_indexBufferType == 0 || g_indexBufferType == 2) {
			Debug_Statistics::Record_DX8_Polys_And_Vertices(polygon_count, vertex_count, g_renderStateShader);
			g_renderStats++;
			g_d3dDevice->DrawIndexedPrimitive(
				primitive_type,
				min_vertex_index,
				vertex_count,
				start_index + g_ibaOffset,
				polygon_count);
			g_drawCalls++;
		}
		break;
	case 1:
	case 3:
		if (g_indexBufferType == 1 || g_indexBufferType == 3)
			Draw_Sorting_IB_VB(primitive_type, start_index, polygon_count, min_vertex_index, vertex_count);
		break;
	}
}
