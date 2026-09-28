// ?bfmeHighlightApply@@YAXIPAXIPAUTexture@@PAUIDirect3DSurface8@@12@Z
// partial score=0.64 date=2026-09-28
// Retail RVA 0x00719090, 1936 bytes.
// ScreenHilightFilter::postRender (0x007D7040) calls this through ILT
// 0x0003F242 with seven cdecl arguments; the name is the one that caller's
// pin already uses.  The shaders it tests are the ones W3DShaderManager::init
// (0x00718E90) loads from "shaders\\Glow.pso" / "shaders\\Glow.vso" into
// 0x012F9D14 / 0x012F9D18, and the vertex declaration it created at
// 0x012F9D24.  The device calls are Direct3D 9 slots (SetSamplerState 0x114,
// SetVertexDeclaration 0x15C, SetPixelShaderConstantF 0x1B4,
// SetRenderTarget 0x94).  The second argument is the caller's 12-byte-element
// vector (begin/end/capacity), read as size() each loop test.

struct IDirect3DSurface8;
struct Texture;

// Direct3D 9 device slots this body calls; the rest are placeholders.
struct IDirect3DDevice8
{
	virtual void __stdcall slot000(); virtual void __stdcall slot001(); virtual void __stdcall slot002();
	virtual void __stdcall slot003(); virtual void __stdcall slot004(); virtual void __stdcall slot005();
	virtual void __stdcall slot006(); virtual void __stdcall slot007(); virtual void __stdcall slot008();
	virtual void __stdcall slot009(); virtual void __stdcall slot010(); virtual void __stdcall slot011();
	virtual void __stdcall slot012(); virtual void __stdcall slot013(); virtual void __stdcall slot014();
	virtual void __stdcall slot015(); virtual void __stdcall slot016(); virtual void __stdcall slot017();
	virtual void __stdcall slot018(); virtual void __stdcall slot019(); virtual void __stdcall slot020();
	virtual void __stdcall slot021(); virtual void __stdcall slot022(); virtual void __stdcall slot023();
	virtual void __stdcall slot024(); virtual void __stdcall slot025(); virtual void __stdcall slot026();
	virtual void __stdcall slot027(); virtual void __stdcall slot028(); virtual void __stdcall slot029();
	virtual void __stdcall slot030(); virtual void __stdcall slot031(); virtual void __stdcall slot032();
	virtual void __stdcall slot033(); virtual void __stdcall slot034(); virtual void __stdcall slot035();
	virtual void __stdcall slot036();
	virtual long __stdcall SetRenderTarget(unsigned index, IDirect3DSurface8 *surface);
	virtual void __stdcall slot038(); virtual void __stdcall slot039(); virtual void __stdcall slot040();
	virtual void __stdcall slot041(); virtual void __stdcall slot042(); virtual void __stdcall slot043();
	virtual void __stdcall slot044(); virtual void __stdcall slot045(); virtual void __stdcall slot046();
	virtual void __stdcall slot047(); virtual void __stdcall slot048(); virtual void __stdcall slot049();
	virtual void __stdcall slot050(); virtual void __stdcall slot051(); virtual void __stdcall slot052();
	virtual void __stdcall slot053(); virtual void __stdcall slot054(); virtual void __stdcall slot055();
	virtual void __stdcall slot056();
	virtual long __stdcall SetRenderState(unsigned state, unsigned value);
	virtual void __stdcall slot058(); virtual void __stdcall slot059(); virtual void __stdcall slot060();
	virtual void __stdcall slot061(); virtual void __stdcall slot062(); virtual void __stdcall slot063();
	virtual void __stdcall slot064();
	virtual long __stdcall SetTexture(unsigned stage, Texture *texture);
	virtual void __stdcall slot066(); virtual void __stdcall slot067(); virtual void __stdcall slot068();
	virtual long __stdcall SetSamplerState(unsigned sampler, unsigned type, unsigned value);
	virtual void __stdcall slot070(); virtual void __stdcall slot071(); virtual void __stdcall slot072();
	virtual void __stdcall slot073(); virtual void __stdcall slot074(); virtual void __stdcall slot075();
	virtual void __stdcall slot076(); virtual void __stdcall slot077(); virtual void __stdcall slot078();
	virtual void __stdcall slot079(); virtual void __stdcall slot080(); virtual void __stdcall slot081();
	virtual void __stdcall slot082(); virtual void __stdcall slot083(); virtual void __stdcall slot084();
	virtual void __stdcall slot085(); virtual void __stdcall slot086();
	virtual long __stdcall SetVertexDeclaration(unsigned declaration);
	virtual void __stdcall slot088(); virtual void __stdcall slot089(); virtual void __stdcall slot090();
	virtual void __stdcall slot091();
	virtual long __stdcall SetVertexShader(unsigned shader);
	virtual void __stdcall slot093();
	virtual long __stdcall SetVertexShaderConstantF(unsigned reg, const float *data, unsigned count);
	virtual void __stdcall slot095(); virtual void __stdcall slot096(); virtual void __stdcall slot097();
	virtual void __stdcall slot098(); virtual void __stdcall slot099(); virtual void __stdcall slot100();
	virtual void __stdcall slot101(); virtual void __stdcall slot102(); virtual void __stdcall slot103();
	virtual void __stdcall slot104(); virtual void __stdcall slot105(); virtual void __stdcall slot106();
	virtual long __stdcall SetPixelShader(unsigned shader);
	virtual void __stdcall slot108();
	virtual long __stdcall SetPixelShaderConstantF(unsigned reg, const float *data, unsigned count);
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;
	Vector4() {}
	Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
	void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
};

struct GlowSampleVector
{
	Vector3 *m_start;
	Vector3 *m_finish;
	Vector3 *m_endOfStorage;
	unsigned size() const { return m_finish - m_start; }
	Vector3 &operator[](unsigned n) { return m_start[n]; }
	const Vector3 &operator[](unsigned n) const { return m_start[n]; }
};

class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *, bool);
	static void Clear(bool, bool, bool, const Vector3 &, float, float,
		unsigned);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

protected:
	static IDirect3DDevice8 *D3DDevice;
};

extern unsigned number_of_DX8_calls;

// W3DShaderManager::init (0x00718E90) fills these from shaders\Glow.pso,
// shaders\Glow.vso and the vertex declaration it creates.
struct BfmeShaderManagerStatics
{
	unsigned m_padding00[5];
	unsigned m_glowPixelShader;
	unsigned m_glowVertexShader;
	unsigned m_padding1c[2];
	unsigned m_glowVertexDeclaration;
};

extern BfmeShaderManagerStatics g_bfmeShaderManager;

void bfmeHighlightDrawQuad(unsigned);

void bfmeHighlightApply(unsigned factorBits, void *samplesArg, unsigned size,
	Texture *texture0, IDirect3DSurface8 *surface1, Texture *texture1,
	IDirect3DSurface8 *surface0)
{
	if (g_bfmeShaderManager.m_glowPixelShader == 0 || g_bfmeShaderManager.m_glowVertexShader == 0)
		return;

	DX8Wrapper::Set_Render_Target(surface1, false);
	DX8Wrapper::Clear(true, false, false, Vector3(0.0f, 0.75f, 0.0f), 0.0f,
		1.0f, 0);

	IDirect3DDevice8 *dev = DX8Wrapper::_Get_D3D_Device8();
	int i;
	for (i = 0; i < 4; ++i) {
		dev->SetSamplerState(i, 1, 3);
		dev->SetSamplerState(i, 2, 3);
		dev->SetSamplerState(i, 5, 2);
		dev->SetSamplerState(i, 6, 2);
		dev->SetSamplerState(i, 7, 2);
	}

	dev->SetRenderState(0x16, 1);
	dev->SetRenderState(0x0e, 0);
	dev->SetRenderState(7, 0);
	dev->SetTexture(0, texture0);
	dev->SetTexture(1, texture0);
	dev->SetTexture(2, texture0);
	dev->SetTexture(3, texture0);
	dev->SetPixelShader(g_bfmeShaderManager.m_glowPixelShader);
	{
		IDirect3DDevice8 *d = DX8Wrapper::_Get_D3D_Device8();
		d->SetVertexDeclaration(g_bfmeShaderManager.m_glowVertexDeclaration);
	}
	++number_of_DX8_calls;
	dev->SetVertexShader(g_bfmeShaderManager.m_glowVertexShader);
	dev->SetRenderState(0x1b, 0);
	dev->SetRenderState(0x13, 2);
	dev->SetRenderState(0x14, 4);

	GlowSampleVector &samples = *(GlowSampleVector *)samplesArg;
	float factor = *(float *)&factorBits;
	unsigned n;
	Vector4 vc[4];
	Vector4 pc[4];
	for (n = 0; n < samples.size(); n += 4) {
		float inv = 1.0f / (float)(int)size;
		if (n == 4)
			dev->SetRenderState(0x1b, 1);
		for (int k = 0; k < 4; ++k) {
			const Vector3 &s = samples[n + k];
			pc[k].X = factor * s.Z;
			pc[k].Y = factor * s.Z;
			pc[k].Z = factor * s.Z;
			pc[k].W = factor * s.Z;
			vc[k] = Vector4(inv * s.X, inv * s.Y, 0.0f, 0.0f);
		}
		dev->SetPixelShaderConstantF(0, &pc[0].X, 4);
		Vector4 c7(0.5f, 0.0f, 0.0f, 0.0f);
		dev->SetPixelShaderConstantF(7, &c7.X, 1);
		dev->SetVertexShaderConstantF(0x0a, &vc[0].X, 4);
		bfmeHighlightDrawQuad(size);
	}

	dev->SetTexture(0, 0);
	dev->SetTexture(1, 0);
	dev->SetTexture(2, 0);
	dev->SetTexture(3, 0);
	dev->SetRenderTarget(0, surface0);
	dev->SetTexture(0, texture1);
	dev->SetTexture(1, texture1);
	dev->SetTexture(2, texture1);
	dev->SetTexture(3, texture1);
	dev->SetRenderState(0x1b, 0);

	for (n = 0; n < samples.size(); n += 4) {
		float inv = 1.0f / (float)(int)size;
		if (n == 4)
			dev->SetRenderState(0x1b, 1);
		for (int k = 0; k < 4; ++k) {
			const Vector3 &s = samples[n + k];
			pc[k].X = factor * s.Z;
			pc[k].Y = factor * s.Z;
			pc[k].Z = factor * s.Z;
			pc[k].W = factor * s.Z;
			vc[k] = Vector4(inv * s.Y, inv * s.X, 0.0f, 0.0f);
		}
		dev->SetPixelShaderConstantF(0, &pc[0].X, 4);
		dev->SetVertexShaderConstantF(0x0a, &vc[0].X, 4);
		bfmeHighlightDrawQuad(size);
	}

	for (i = 0; i < 4; ++i) {
		dev->SetSamplerState(i, 5, 2);
		dev->SetSamplerState(i, 6, 2);
		dev->SetSamplerState(i, 7, 2);
	}
	dev->SetPixelShader(0);
	DX8Wrapper::Set_Render_Target(0, true);
}
