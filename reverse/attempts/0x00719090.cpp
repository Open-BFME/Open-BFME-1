// ?bfmeHighlightApply@@YAXIPAXIPAUTexture@@PAUIDirect3DSurface8@@12@Z
// partial score=0.32 date=2026-09-17
// Retail 0x00719090, reached by the proven bfmeHighlightApply ILT at
// 0x0003F242 from ScreenHilightFilter::postRender.  The seven cdecl
// arguments are retained from that caller: the first is a float bit pattern,
// the second is a begin/end range of 12-byte samples, the third is the quad
// size, and the remaining four values are the two textures and two surfaces.
//
// The renderer is BFME-specific.  Its two four-sample passes are kept
// explicit here because retail's x87 stream and shader-constant writes prove
// the pass boundaries; no class name is inferred for the sample range.

typedef int Int;
typedef unsigned UnsignedInt;
typedef float Real;

struct IDirect3DSurface8;
struct Texture;

struct BfmeDevice;
struct BfmeDeviceVtable
{
	char m_pad000[0xe4];
	long (__stdcall *setRenderState)(BfmeDevice *, UnsignedInt, UnsignedInt);
	char m_pad0e8[0x104 - 0xe8];
	long (__stdcall *setTexture)(BfmeDevice *, UnsignedInt, Texture *);
	char m_pad108[4];
	long (__stdcall *setTextureStageState)(BfmeDevice *, UnsignedInt,
		UnsignedInt, UnsignedInt);
	char m_pad110[4];
	long (__stdcall *setSamplerState)(BfmeDevice *, UnsignedInt,
		UnsignedInt, UnsignedInt);
	char m_pad118[0x15c - 0x118];
	long (__stdcall *setFVF)(BfmeDevice *, UnsignedInt);
	char m_pad160[0x170 - 0x160];
	long (__stdcall *setVertexShader)(BfmeDevice *, UnsignedInt);
	char m_pad174[0x178 - 0x174];
	long (__stdcall *setVertexShaderConstant)(BfmeDevice *, UnsignedInt,
		const Real *, UnsignedInt);
	char m_pad17c[0x1ac - 0x17c];
	long (__stdcall *setPixelShader)(BfmeDevice *, UnsignedInt);
	char m_pad1b0[4];
	long (__stdcall *setPixelShaderConstant)(BfmeDevice *, UnsignedInt,
		const Real *, UnsignedInt);
	long (__stdcall *setRenderTarget)(BfmeDevice *, UnsignedInt,
		IDirect3DSurface8 *);
};

struct BfmeDevice
{
	BfmeDeviceVtable *v;
};

struct Vector3
{
	Real x;
	Real y;
	Real z;
};

struct BfmeSample
{
	Real x;
	Real y;
	Real z;
};

struct BfmeSampleRange
{
	BfmeSample *begin;
	BfmeSample *end;
};

class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *, bool);
	static void Clear(bool, bool, bool, const Vector3 &, Real, Real,
		UnsignedInt);
};

#define BfmeDeviceGlobal (*(BfmeDevice **)0x01340534)
#define BfmeHighlightPixelShader (*(UnsignedInt *)0x012F9D14)
#define BfmeHighlightVertexShader (*(UnsignedInt *)0x012F9D18)
#define BfmeHighlightFVF (*(UnsignedInt *)0x012F9D24)
#define BfmeDX8CallCount (*(UnsignedInt *)0x01340594)
#define BfmeOne (*(const Real *)0x01075334)

#pragma comment(linker, "/alternatename:?bfmeHighlightDrawQuad@@YAXI@Z=?j_00018bb0@@YAXXZ")

void bfmeHighlightDrawQuad(UnsignedInt size);

static __forceinline Real bfmeHighlightFactor(UnsignedInt bits)
{
	return *(const Real *)&bits;
}

static __forceinline void bfmeFillZConstants(Real *constants,
	const BfmeSample *sample, Real factor)
{
	Real value = factor * sample->z;
	constants[0] = value;
	constants[1] = value;
	constants[2] = value;
	constants[3] = value;
}

static __forceinline void bfmeFillFirstPassVertices(Real *vertices,
	const BfmeSample *sample, Real inverse)
{
	vertices[0] = inverse * sample[0].x;
	vertices[1] = inverse * sample[0].y;
	vertices[2] = 0.0f;
	vertices[3] = 0.0f;
	vertices[4] = inverse * sample[1].x;
	vertices[5] = inverse * sample[1].y;
	vertices[6] = 0.0f;
	vertices[7] = 0.0f;
	vertices[8] = inverse * sample[2].x;
	vertices[9] = inverse * sample[2].y;
	vertices[10] = 0.0f;
	vertices[11] = 0.0f;
	vertices[12] = vertices[8] * sample[3].x;
	vertices[13] = vertices[8] * sample[3].y;
	vertices[14] = 0.0f;
	vertices[15] = 0.0f;
}

static __forceinline void bfmeFillSecondPassVertices(Real *vertices,
	const BfmeSample *sample, Real inverse)
{
	vertices[0] = inverse * sample[0].y;
	vertices[1] = inverse * sample[0].x;
	vertices[2] = 0.0f;
	vertices[3] = 0.0f;
	vertices[4] = inverse * sample[1].y;
	vertices[5] = inverse * sample[1].x;
	vertices[6] = 0.0f;
	vertices[7] = 0.0f;
	vertices[8] = inverse * sample[2].y;
	vertices[9] = inverse * sample[2].x;
	vertices[10] = 0.0f;
	vertices[11] = 0.0f;
	vertices[12] = vertices[8] * sample[3].y;
	vertices[13] = vertices[8] * sample[3].x;
	vertices[14] = 0.0f;
	vertices[15] = 0.0f;
}

void bfmeHighlightApply(UnsignedInt factorBits, void *sampleRange,
	UnsignedInt size, Texture *texture0, IDirect3DSurface8 *surface1,
	Texture *texture1, IDirect3DSurface8 *surface0)
{
	if (BfmeHighlightPixelShader == 0 || BfmeHighlightVertexShader == 0)
		return;

	DX8Wrapper::Set_Render_Target(surface1, false);
	Vector3 clearColor;
	clearColor.x = 0.0f;
	clearColor.y = 0.75f;
	clearColor.z = 0.0f;
	DX8Wrapper::Clear(true, false, false, clearColor, 0.0f, 1.0f, 0);

	BfmeDevice *device = BfmeDeviceGlobal;
	UnsignedInt i;
	for (i = 0; i < 4; ++i)
	{
		device->v->setSamplerState(device, 0, 1, 3);
		device->v->setSamplerState(device, 0, 2, 3);
		device->v->setSamplerState(device, 0, 5, 2);
		device->v->setSamplerState(device, 0, 6, 2);
		device->v->setSamplerState(device, 0, 7, 2);
	}

	device->v->setRenderState(device, 0x16, 1);
	device->v->setRenderState(device, 0x0e, 0);
	device->v->setRenderState(device, 7, 0);

	for (i = 0; i < 4; ++i)
		device->v->setTexture(device, i, texture0);

	device->v->setPixelShader(device, BfmeHighlightPixelShader);
	device->v->setFVF(device, BfmeHighlightFVF);
	++BfmeDX8CallCount;
	device->v->setVertexShader(device, BfmeHighlightVertexShader);
	device->v->setRenderState(device, 0x1b, 0);
	device->v->setRenderState(device, 0x13, 2);
	device->v->setRenderState(device, 0x14, 4);

	BfmeSampleRange *range = (BfmeSampleRange *)sampleRange;
	UnsignedInt count = (UnsignedInt)(range->end - range->begin);
	Real factor = bfmeHighlightFactor(factorBits);
	Real inverse = BfmeOne / (Real)size;
	Real pixelConstants[16];
	Real vertexConstants[16];
	Real constant7[4];
	constant7[0] = 0.5f;
	constant7[1] = 0.0f;
	constant7[2] = 0.0f;
	constant7[3] = 0.0f;

	for (i = 0; i < count; i += 4)
	{
		if (i == 4)
			device->v->setRenderState(device, 0x1b, 1);

		const BfmeSample *sample = range->begin + i;
		bfmeFillZConstants(&pixelConstants[0], sample + 0, factor);
		bfmeFillZConstants(&pixelConstants[4], sample + 1, factor);
		bfmeFillZConstants(&pixelConstants[8], sample + 2, factor);
		bfmeFillZConstants(&pixelConstants[12], sample + 3, factor);
		bfmeFillFirstPassVertices(vertexConstants, sample, inverse);

		device->v->setPixelShaderConstant(device, 0, pixelConstants, 4);
		device->v->setPixelShaderConstant(device, 7, constant7, 1);
		device->v->setVertexShaderConstant(device, 0x0a,
			vertexConstants, 4);
		bfmeHighlightDrawQuad(size);
	}

	for (i = 0; i < 4; ++i)
		device->v->setTexture(device, i, 0);
	device->v->setRenderTarget(device, 0, surface0);

	for (i = 0; i < 4; ++i)
		device->v->setTexture(device, i, texture1);
	device->v->setRenderState(device, 0x1b, 0);

	for (i = 0; i < count; i += 4)
	{
		if (i == 4)
			device->v->setRenderState(device, 0x1b, 1);

		const BfmeSample *sample = range->begin + i;
		bfmeFillZConstants(&pixelConstants[0], sample + 0, factor);
		bfmeFillZConstants(&pixelConstants[4], sample + 1, factor);
		bfmeFillZConstants(&pixelConstants[8], sample + 2, factor);
		bfmeFillZConstants(&pixelConstants[12], sample + 3, factor);
		bfmeFillSecondPassVertices(vertexConstants, sample, inverse);

		device->v->setPixelShaderConstant(device, 0, pixelConstants, 4);
		device->v->setVertexShaderConstant(device, 0x0a,
			vertexConstants, 4);
		bfmeHighlightDrawQuad(size);
	}

	device->v->setSamplerState(device, 0, 5, 2);
	device->v->setSamplerState(device, 0, 6, 2);
	device->v->setSamplerState(device, 0, 7, 2);
	device->v->setPixelShader(device, 0);
	DX8Wrapper::Set_Render_Target(0, true);
}
