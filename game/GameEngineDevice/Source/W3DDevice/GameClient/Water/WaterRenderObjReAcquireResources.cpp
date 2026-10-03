// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims /Iinputs/reference/shims/sweep
//
// BFME WaterRenderObjClass::ReAcquireResources, retail 0x007A0500 (891 bytes).
// Identity: the Zero Hour W3DWater.cpp twin has the same body shape (index
// buffer refill, generate{Index,Vertex}Buffer, two shader loads, reflection
// render target, water-track re-acquire, three D3DXAssembleShader pixel
// shaders); the retail callers are WaterRenderObjClass::init and the
// Gen_006C6300 resource-release owner, exactly where the twin calls it.
//
// BFME differences from the twin, all witnessed by the retail bytes:
//  - this+0xcc is the refcounted index buffer (the matched retail destructor
//    releases the same offset through its inline refcount path);
//  - the two LoadAndCreateD3DShader calls are BFME's split BfmeShaderLoader
//    (pixel) / BfmeVertexShaderLoader (vertex), each taking (const char*, DWORD*);
//  - Create_Render_Target returns a four-byte owning texture handle by hidden
//    sret, so the call takes four stack slots and the result is bound with a
//    cross-TU operator= before the handle temporary's own release.
#include <string.h>
#include "d3d8_shim_validated.h"

#ifndef NULL
#define NULL 0
#endif

typedef unsigned short UnsignedShort;

#define NEW_REF(className, args) new className args
#define FAILED(hr) ((HRESULT)(hr) < 0)

#define PATCH_SIZE 15
#define SEA_REFLECTION_SIZE 256
#define SEA_PATCH_VERTEX_SIZE 0x18
#define MATER_MESH_VERTEX_SIZE 0x20
#define WATER_TRACK_PATCH_SIZE 0x0f
#define WATER_TRACK_VERTEX_SIZE 0x18
#define WATER_TRACK_FILL 1
#define DC_GENERIC_PIXEL_SHADER_1_1 3

struct ID3DXBuffer
{
	virtual long __stdcall QueryInterface(const void *, void **) = 0;
	virtual unsigned long __stdcall AddRef(void) = 0;
	virtual unsigned long __stdcall Release(void) = 0;
	virtual void * __stdcall GetBufferPointer(void) = 0;
	virtual unsigned long __stdcall GetBufferSize(void) = 0;
};
typedef HRESULT (__stdcall *BfmeCreatePixelShader)(IDirect3DDevice8 *, const DWORD *, DWORD *);
extern "C" long __stdcall D3DXAssembleShader(const char *, unsigned int, const void *, void *, void *, ID3DXBuffer **, unsigned int);

void W3DRadarResetLock(void);
char bfmeUnlock1179(void);
void * operator new(unsigned int);

extern IDirect3DDevice8 *g_retailShaderDevice;

class TextureClass
{
public:
	void Release_Ref(void);
};

// The four-byte owning texture handle.  Retail binds it with a cross-TU
// copy-assignment (AddRef the source, Release_Ref the destination) and
// releases the temporary in place.
class Gen_005D2040
{
public:
	TextureClass *m_texture;
	Gen_005D2040 &operator=(const Gen_005D2040 &other);
	~Gen_005D2040(void)
	{
		if (m_texture != 0)
			m_texture->Release_Ref();
	}
};

enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };

class DX8Wrapper
{
public:
	static Gen_005D2040 Create_Render_Target(int width, int height, WW3DFormat format);
};

class RefCountedResource
{
public:
	virtual void Delete_This(void);
	int m_refCount;
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
		IndexBufferClass *m_indexBuffer;
		UnsignedShort *m_indices;

	public:
		WriteLockClass(IndexBufferClass *indexBuffer, int flags);
		~WriteLockClass(void);

		UnsignedShort *Get_Index_Array(void) { return m_indices; }
	};
};

class DX8IndexBufferClass : public RefCountedResource
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };
	typedef IndexBufferClass::WriteLockClass WriteLockClass;

	DX8IndexBufferClass(unsigned indexCount, UsageType usage);
	unsigned char m_bfmeTail[0x10];
};

class BfmeShaderLoader
{
public:
	static long LoadAndCreateD3DShader(const char *filename, DWORD *shader);
};

class BfmeVertexShaderLoader
{
public:
	static long LoadAndCreateD3DShader(const char *filename, DWORD *shader);
};

enum ChipsetType { CHIPSET_0, CHIPSET_1, CHIPSET_2, CHIPSET_3 };

class W3DShaderManager
{
public:
	static ChipsetType getChipset(void);
};

class WaterTracksRenderSystem
{
public:
	void ReAcquireResources(void);
};

// Retail writes this declaration as four eight-byte descriptors of two
// sixteen-bit then four eight-bit fields.
// Retail holds the radar lock across the whole body and releases it on every
// exit path, including each early failure return.
class WaterDeviceScope
{
public:
	WaterDeviceScope(void) { W3DRadarResetLock(); }
	~WaterDeviceScope(void) { bfmeUnlock1179(); }
};

struct WaterShaderDeclarationElement
{
	unsigned short m_word0;
	unsigned short m_word1;
	unsigned char m_byte0;
	unsigned char m_byte1;
	unsigned char m_byte2;
	unsigned char m_byte3;
};

typedef HRESULT (__stdcall *BfmeCreateVertexShader)(IDirect3DDevice8 *, const DWORD *, DWORD *);

class WaterRenderObjClass
{
public:
	enum WaterType
	{
		WATER_TYPE_0_TRANSLUCENT = 0,
		WATER_TYPE_1_FB_REFLECTION,
		WATER_TYPE_2_PVSHADER,
		WATER_TYPE_3_GRIDMESH
	};

	WaterRenderObjClass(void);
	~WaterRenderObjClass(void);

	void ReAcquireResources(void);

protected:
	HRESULT generateIndexBuffer(int sizeX, int sizeY);
	HRESULT generateVertexBuffer(int sizeX, int sizeY, int vertexSize, bool doFill);

private:
	unsigned char m_beforeIndexBuffer[0xcc];
	DX8IndexBufferClass *m_indexBuffer;
	unsigned char m_beforeWaterType[0x11c - 0xd0];
	int m_waterType;
	unsigned char m_beforePixelShader[0x130 - 0x120];
	DWORD m_wavePixelShader;
	DWORD m_waveVertexShader;
	DWORD m_d3dVertexShader;
	unsigned char m_beforeReflection[0x24c - 0x13c];
	Gen_005D2040 m_pReflectionTexture;
	unsigned char m_beforeTrackSystem[0x254 - 0x250];
	WaterTracksRenderSystem *m_waterTrackSystem;
	int m_meshData;
	unsigned char m_beforeGridCellsX[0x2a0 - 0x25c];
	int m_gridCellsX;
	int m_gridCellsY;
	unsigned char m_beforeShaders[0x2b0 - 0x2a8];
	DWORD m_riverWaterPixelShader;
	DWORD m_waterPixelShader;
	DWORD m_trapezoidWaterPixelShader;
};

void WaterRenderObjClass::ReAcquireResources(void)
{
	HRESULT hr;
	WaterDeviceScope deviceScope;

	if (m_indexBuffer)
		this->~WaterRenderObjClass();

	m_indexBuffer = NEW_REF(DX8IndexBufferClass, (6, DX8IndexBufferClass::USAGE_DEFAULT));
	{
		DX8IndexBufferClass::WriteLockClass lockIdxBuffer((IndexBufferClass *)m_indexBuffer, 0);
		UnsignedShort *ib = lockIdxBuffer.Get_Index_Array();
		// quad of 2 triangles
		ib[0] = 3;
		ib[1] = 0;
		ib[2] = 2;
		ib[3] = 2;
		ib[4] = 0;
		ib[5] = 1;
	}

	// The same grid serves either the 3D water mesh or the shader water, so
	// only the size differs.
	if (m_meshData)
	{
		if (FAILED(generateIndexBuffer(m_gridCellsX + 1, m_gridCellsY + 1)))
			return;
		if (FAILED(generateVertexBuffer(m_gridCellsX + 1, m_gridCellsY + 1, MATER_MESH_VERTEX_SIZE, false)))
			return;
	}
	else
	if (m_waterType == WATER_TYPE_2_PVSHADER)
	{
		if (FAILED(hr = generateIndexBuffer(PATCH_SIZE, PATCH_SIZE)))
			return;
		if (FAILED(hr = generateVertexBuffer(PATCH_SIZE, PATCH_SIZE, SEA_PATCH_VERTEX_SIZE, true)))
			return;

		WaterShaderDeclarationElement declaration[4] =
		{
			{ 0, 0, 2, 0, 0, 0 },
			{ 0, 0x0c, 4, 0, 0x0a, 0 },
			{ 0, 0x10, 1, 0, 5, 0 },
			{ 0xff, 0, 0x11, 0, 0, 0 }
		};
		DWORD *decl = (DWORD *)declaration;
		if (m_d3dVertexShader == 0)
		{
			IDirect3DDevice8 *device = g_retailShaderDevice;
			hr = (*(BfmeCreateVertexShader **)device)[86](device, decl, &m_d3dVertexShader);
			if (FAILED(hr))
				return;
		}

		hr = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\wave.pso", &m_wavePixelShader);
		if (FAILED(hr))
			return;
		hr = BfmeVertexShaderLoader::LoadAndCreateD3DShader("shaders\\wave.vso", &m_waveVertexShader);
		if (FAILED(hr))
			return;

		m_pReflectionTexture = DX8Wrapper::Create_Render_Target(SEA_REFLECTION_SIZE, SEA_REFLECTION_SIZE, WW3D_FORMAT_UNKNOWN);
	}

	if (m_waterTrackSystem)
		m_waterTrackSystem->ReAcquireResources();

	if (W3DShaderManager::getChipset() >= DC_GENERIC_PIXEL_SHADER_1_1)
	{
		ID3DXBuffer *compiledShader;
		const char *shader =
			"ps.1.1\n \
			tex t0 \n\
			tex t1	\n\
			tex t2	\n\
			tex t3\n\
			mul r0,v0,t0 ; blend vertex color into t0. \n\
			mul r1, t1, t2 ; mul\n\
			add r0.rgb, r0, t3\n\
			+mul r0.a, r0, t3\n\
			add r0.rgb, r0, r1\n\
			+mul r0.a, r0, c1\n";
		hr = D3DXAssembleShader(shader, strlen(shader), 0, 0, 0, &compiledShader, 0);
		if (hr == 0)
		{
			IDirect3DDevice8 *device = g_retailShaderDevice;
			hr = (*(BfmeCreatePixelShader **)device)[106](device, (DWORD *)compiledShader->GetBufferPointer(), &m_waterPixelShader);
			compiledShader->Release();
		}
		shader =
			"ps.1.1\n \
			tex t0 \n\
			tex t1	\n\
			texbem t2, t1 ; use t1 as env map adjustment on t2.\n\
			mul r0,v0,t0 ; blend vertex color into t0. \n\
			mul r1.rgb,t2,c0 ; reduce t2 (environment mapped reflection) by constant\n\
			add r0.rgb, r0, r1";
		hr = D3DXAssembleShader(shader, strlen(shader), 0, 0, 0, &compiledShader, 0);
		if (hr == 0)
		{
			IDirect3DDevice8 *device = g_retailShaderDevice;
			hr = (*(BfmeCreatePixelShader **)device)[106](device, (DWORD *)compiledShader->GetBufferPointer(), &m_riverWaterPixelShader);
			compiledShader->Release();
		}
		shader =
			"ps.1.1\n \
			tex t0 ;get water texture\n\
			tex t1 ;get white highlights on black background\n\
			tex t2 ;get white highlights with more tiling\n\
			tex t3	; get black shroud \n\
			mul r0,v0,t0 ; blend vertex color and alpha into base texture. \n\
			mad r0.rgb, t1, t2, r0	; blend sparkles and noise \n\
			mul r0.rgb, r0, t3 ; blend in black shroud \n\
			;\n";
		hr = D3DXAssembleShader(shader, strlen(shader), 0, 0, 0, &compiledShader, 0);
		if (hr != 0)
			return;
		{
			IDirect3DDevice8 *device = g_retailShaderDevice;
			hr = (*(BfmeCreatePixelShader **)device)[106](device, (DWORD *)compiledShader->GetBufferPointer(), &m_trapezoidWaterPixelShader);
			compiledShader->Release();
		}
	}
}
