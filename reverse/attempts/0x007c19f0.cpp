// ?d_007c19f0@@YAXXZ
// partial score=0.52 date=2026-09-02
// cl: /DNDEBUG /MD /GR-
// thiscall 0x007C19F0 size 408: Get_Preset PRELIT_DIFFUSE, inlined Set_Material,
// Set_Shader, Set_Vertex_Buffer(this->vb,0), Set_Index_Buffer(this->ib,0),
// inlined Set_World_Identity, Apply_Render_State_Changes, then D3D stencil
// and SetVertexShader(0)/SetPixelShader(2).

class VertexMaterialClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType preset);
	int m_ref;
	virtual void Release_Ref();
};

class ShaderClass
{
};

class VertexBufferClass;
class IndexBufferClass;

extern VertexMaterialClass *g_renderStateMaterial;
extern unsigned g_renderStateChanged;
extern ShaderClass g_presetOpaqueShader;
extern float g_worldMatrix[16];

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
	virtual void SetRenderState(unsigned state, unsigned value);
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
	virtual void v70(void);
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
	virtual void v81(void);
	virtual void v82(void);
	virtual void v83(void);
	virtual void v84(void);
	virtual void v85(void);
	virtual void v86(void);
	virtual void v87(void);
	virtual void v88(void);
	virtual void SetVertexShader(unsigned vs);
	virtual void v90(void);
	virtual void SetPixelShader(unsigned ps);
};

extern IDirect3DDevice8 *g_d3dDevice;

class TacticalViewShim
{
public:
	int pad00;
	int pad04;
	int m_mask08;
};

extern TacticalViewShim *TheTacticalView;

class DX8Wrapper
{
public:
	static void Set_Shader(const ShaderClass &shader);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index);
	static void Apply_Render_State_Changes(void);
};

class BufferDrawHost
{
public:
	VertexBufferClass *vb;
	IndexBufferClass *ib;
	void setup(void);
};

void BufferDrawHost::setup(void)
{
	VertexMaterialClass *vmat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	if (vmat)
		++vmat->m_ref;
	VertexMaterialClass *old = g_renderStateMaterial;
	if (old) {
		int *pref = &old->m_ref;
		int n = *pref;
		--n;
		*pref = n;
		if (n == 0)
			old->Release_Ref();
	}
	g_renderStateMaterial = vmat;
	g_renderStateChanged |= 0x4000;
	if (vmat) {
		if (--vmat->m_ref == 0)
			vmat->Release_Ref();
	}

	DX8Wrapper::Set_Shader(g_presetOpaqueShader);
	DX8Wrapper::Set_Vertex_Buffer(vb, 0);
	DX8Wrapper::Set_Index_Buffer(ib, 0);

	if (!(g_renderStateChanged & 0x40000)) {
		g_worldMatrix[0] = 1.0f;
		g_worldMatrix[1] = 0.0f;
		g_worldMatrix[2] = 0.0f;
		g_worldMatrix[3] = 0.0f;
		g_worldMatrix[4] = 0.0f;
		g_worldMatrix[5] = 1.0f;
		g_worldMatrix[6] = 0.0f;
		g_worldMatrix[7] = 0.0f;
		g_worldMatrix[8] = 0.0f;
		g_worldMatrix[9] = 0.0f;
		g_worldMatrix[10] = 1.0f;
		g_worldMatrix[11] = 0.0f;
		g_worldMatrix[12] = 0.0f;
		g_worldMatrix[13] = 0.0f;
		g_worldMatrix[14] = 0.0f;
		g_worldMatrix[15] = 1.0f;
		g_renderStateChanged |= 0x40001;
	}

	DX8Wrapper::Apply_Render_State_Changes();

	IDirect3DDevice8 *dev = g_d3dDevice;
	dev->SetRenderState(0x34, 1);
	dev->SetRenderState(0x38, 8);
	int mask = TheTacticalView->m_mask08;
	dev->SetRenderState(0x3a, 0xffffffff);
	dev->SetRenderState(0x3b, ~mask);
	dev->SetVertexShader(0);
	dev->SetPixelShader(2);
}
