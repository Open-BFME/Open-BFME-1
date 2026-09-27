// ?drawSea@WaterRenderObjClass@@IAEXAAVRenderInfoClass@@@Z
// partial score=0.429 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/water /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// BFME drawSea uses the custom water object layout and direct device ABI.
// The retail body is 2,884 bytes at 0x007A37B0.
#define Matrix4x4 Matrix4

#include "W3DDevice/GameClient/heightmap.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "rinfo.h"
#include "aabox.h"
#include "dx8wrapper.h"
#include "texture.h"
#include "D3dx8math.h"

void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

#define F2DW(f) (*(DWORD *)&(f))

typedef long (__stdcall *BfmeD3D1)(void *, DWORD);
typedef long (__stdcall *BfmeD3D2)(void *, DWORD, DWORD);
typedef long (__stdcall *BfmeD3D3)(void *, DWORD, DWORD, DWORD);
typedef long (__stdcall *BfmeD3DTexture)(void *, DWORD, void *);
typedef long (__stdcall *BfmeD3DConstant)(void *, DWORD, const void *, DWORD);
typedef long (__stdcall *BfmeD3DStream)(void *, DWORD, void *, DWORD, DWORD);
typedef long (__stdcall *BfmeD3DDraw)(void *, DWORD, DWORD, DWORD, DWORD, DWORD);

static inline void *BfmeDevice(void)
{
	return DX8Wrapper::_Get_D3D_Device8();
}

static inline void BfmeDevice1(unsigned slot, DWORD value)
{
	void *device = BfmeDevice();
	((BfmeD3D1)(*(void ***)device)[slot / 4])(device, value);
}

static inline void BfmeDevice2(unsigned slot, DWORD first, DWORD second)
{
	void *device = BfmeDevice();
	((BfmeD3D2)(*(void ***)device)[slot / 4])(device, first, second);
}

static inline void BfmeDevice3(unsigned slot, DWORD first, DWORD second, DWORD third)
{
	void *device = BfmeDevice();
	((BfmeD3D3)(*(void ***)device)[slot / 4])(device, first, second, third);
}

static inline void BfmeDeviceTexture(unsigned stage, void *texture)
{
	void *device = BfmeDevice();
	((BfmeD3DTexture)(*(void ***)device)[0x104 / 4])(device, stage, texture);
}

static inline void BfmeDeviceConstant(unsigned reg, const void *data, unsigned count)
{
	void *device = BfmeDevice();
	((BfmeD3DConstant)(*(void ***)device)[0x178 / 4])(device, reg, data, count);
}

static inline void BfmeDeviceStream(unsigned stream, void *buffer, unsigned offset, unsigned stride)
{
	void *device = BfmeDevice();
	((BfmeD3DStream)(*(void ***)device)[0x190 / 4])(device, stream, buffer, offset, stride);
}

static inline void BfmeDeviceIndices(void *buffer)
{
	void *device = BfmeDevice();
	((BfmeD3D1)(*(void ***)device)[0x1a0 / 4])(device, (DWORD)buffer);
}

static inline void BfmeDeviceDraw(unsigned type, unsigned minVertex, unsigned vertexCount,
	unsigned startIndex, unsigned primitiveCount)
{
	void *device = BfmeDevice();
	((BfmeD3DDraw)(*(void ***)device)[0x148 / 4])(
		device, type, minVertex, vertexCount, startIndex, primitiveCount);
}

class TextureHandle
{
public:
	TextureHandle(void) : m_ptr(0) { }
	TextureHandle(const TextureHandle &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr != 0)
			m_ptr->Add_Ref();
	}
	~TextureHandle(void)
	{
		if (m_ptr != 0)
			m_ptr->Release_Ref();
	}

	TextureBaseClass *get(void) const { return m_ptr; }

	TextureBaseClass *m_ptr;
};

class W3DShroud
{
public:
	TextureHandle getShroudTexture(void);
};

class WaterRenderObjClass
{
public:
	bool getClippedWaterPlane(CameraClass *camera, AABoxClass *box);

	protected:
	void drawSea(RenderInfoClass &rinfo);

	unsigned char m_base[0x1c];
	Matrix3D Transform;
	unsigned char m_gap[0xd8];
	LPDIRECT3DVERTEXBUFFER8 m_vertexBuffer;
	LPDIRECT3DINDEXBUFFER8 m_indexBuffer;
	DWORD m_12c;
	DWORD m_130;
	DWORD m_134;
	DWORD m_138;
	DWORD m_numVertices;
	DWORD m_numIndices;
	void *m_textureSlots[64];
	DWORD m_244;
	DWORD m_248;
	TextureBaseClass *m_reflectionTexture;
};

static inline void BfmeCameraRefresh(CameraClass *camera)
{
	typedef void (__fastcall *CameraMethod)(CameraClass *);
	void **vtable = *(void ***)camera;
	((CameraMethod)vtable[0x50 / 4])(camera);
}

static inline void BfmeSetTextureCache(TextureBaseClass *texture)
{
	TextureBaseClass **current = (TextureBaseClass **)0x012F9D28;
	if (texture != 0)
		texture->Add_Ref();
	if (*current != 0)
		(*current)->Release_Ref();
	*current = texture;
}

void WaterRenderObjClass::drawSea(RenderInfoClass &rinfo)
{
	AABoxClass seaBox;

	if (!getClippedWaterPlane(&rinfo.Camera, &seaBox))
		return;

	D3DXMATRIX matProj, matView, matWW3D, patchMatrix;
	Matrix3D tm(Transform);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, tm);

	{
		TextureBaseClass *texture = 0;
		BoxSetTexture(0, texture);
	}
	{
		TextureBaseClass *texture = 0;
		BoxSetTexture(1, texture);
	}

	DX8Wrapper::Apply_Render_State_Changes();
	BfmeCameraRefresh(&rinfo.Camera);
	DX8Wrapper::_Get_DX8_Transform(D3DTS_VIEW, *(Matrix4x4 *)&matView);
	DX8Wrapper::_Get_DX8_Transform(D3DTS_PROJECTION, *(Matrix4x4 *)&matProj);

	BfmeDevice3(0x10c, 0, 2, 2);
	BfmeDevice3(0x10c, 1, 3, 0);
	BfmeDevice3(0x10c, 1, 4, 0);
	BfmeDevice3(0x10c, 1, 4, 1);
	BfmeDevice3(0x10c, 1, 0xb, 0);
	BfmeDevice3(0x10c, 1, 2, 2);
	BfmeDevice3(0x10c, 1, 3, 1);
	BfmeDevice3(0x10c, 1, 4, 1);
	BfmeDevice3(0x10c, 1, 1, 1);
	BfmeDevice3(0x10c, 1, 4, 2);
	BfmeDevice3(0x10c, 1, 1, 1);
	BfmeDevice3(0x10c, 1, 0xb, 1);
	BfmeDevice3(0x10c, 2, 0x18, 1);
	BfmeDevice3(0x10c, 2, 0xb, 2);
	BfmeDevice3(0x10c, 3, 0x18, 2);
	BfmeDevice3(0x10c, 3, 0xb, 3);
	BfmeDevice3(0x114, 1, 1, 1);
	BfmeDevice3(0x114, 1, 2, 1);
	BfmeDevice3(0x114, 1, 1, 3);
	BfmeDevice3(0x114, 1, 2, 3);
	BfmeDevice2(0x0e4, 3, 0x80);

	BfmeDeviceTexture(0, m_textureSlots[m_244]);
	BfmeDevice3(0x114, 1, 7, 1);
	BfmeDevice3(0x114, 1, 6, 2);
	BfmeDevice3(0x114, 1, 5, 2);
	BfmeDevice3(0x10c, 1, 7, m_248);
	BfmeDevice3(0x10c, 1, 8, 0);
	BfmeDevice3(0x10c, 1, 9, 0);
	BfmeDevice3(0x10c, 1, 10, m_248);
	BfmeDevice3(0x10c, 1, 0x16, 1);
	BfmeDevice3(0x10c, 1, 0x17, 0);
	BfmeDevice3(0x10c, 2, 1, 1);
	BfmeDevice3(0x10c, 2, 4, 1);
	BfmeDevice2(0x0e4, 0x0e, 0);

	memset(&matWW3D, 0, sizeof(matWW3D));
	matWW3D.m[0][0] = 1.0f;
	matWW3D.m[1][2] = 1.0f;
	matWW3D.m[2][1] = 1.0f;
	matWW3D.m[3][3] = 1.0f;

	float texProj[16] = {
		0.5f, -0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	BfmeDeviceConstant(6, texProj, 4);
	float zero[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	BfmeDeviceConstant(0, zero, 1);
	float one[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	BfmeDeviceConstant(1, one, 1);

	BfmeDevice1(0x15c, m_138);
	++*(unsigned *)0x01340594;
	BfmeDevice1(0x170, m_134);
	BfmeDevice1(0x1ac, m_130);
	BfmeDevice2(0x0e4, 0x13, 5);
	BfmeDevice2(0x0e4, 0x14, 6);
	BfmeDevice2(0x0e4, 0x1b, 1);
	BfmeDeviceTexture(1, m_reflectionTexture->Peek_D3D_Base_Texture());

	BfmeDeviceStream(0, m_vertexBuffer, 0, 0x18);
	BfmeDeviceIndices(m_indexBuffer);

	int patchX, patchY;
	int patchWorldX, patchWorldY;
	float worldX, worldY;
	float scale = *(float *)0x01127EC0;
	float cell = *(float *)0x01096C50;
	memset(&patchMatrix, 0, sizeof(patchMatrix));
	patchMatrix.m[0][0] = 40.0f;
	patchMatrix.m[1][1] = 1.0f;
	patchMatrix.m[2][2] = 40.0f;
	patchMatrix.m[3][3] = 1.0f;

	patchY = (int)((seaBox.Center.Y - seaBox.Extent.Y) * scale);
	patchWorldY = patchY * 14;
	for (worldY = (float)patchWorldY * cell;
		worldY < seaBox.Center.Y + seaBox.Extent.Y;
		patchWorldY += 14)
	{
		patchX = (int)((seaBox.Center.X - seaBox.Extent.X) * scale);
		patchWorldX = patchX * 14;
		for (worldX = (float)patchWorldX * cell;
			worldX < seaBox.Center.X + seaBox.Extent.X;
			patchWorldX += 14)
		{
			D3DXMATRIX matWorldViewProj, matTemp, matTempWorld;
			patchMatrix.m[3][0] = worldX;
			patchMatrix.m[3][2] = worldY;
			D3DXMatrixMultiply(&matTempWorld, &patchMatrix, &matWW3D);
			D3DXMatrixMultiply(&matTemp, &matTempWorld, &matView);
			D3DXMatrixMultiply(&matWorldViewProj, &matTemp, &matProj);
			D3DXMatrixTranspose(&matWorldViewProj, &matWorldViewProj);
			BfmeDeviceConstant(2, &matWorldViewProj, 4);
			BfmeDeviceDraw(5, 0, m_numVertices, 0, m_numIndices);
			worldX = (float)patchWorldX * cell;
		}
		worldY = (float)patchWorldY * cell;
	}

	BfmeDevice2(0x0e4, 0x1b, 0);
	BfmeDeviceTexture(0, 0);
	BfmeDeviceTexture(1, 0);
	BfmeDeviceTexture(2, 0);
	BfmeDevice3(0x10c, 0, 0x18, 0);
	BfmeDevice3(0x10c, 0, 0xb, 0);
	BfmeDevice3(0x10c, 1, 0x18, 1);
	BfmeDevice3(0x10c, 1, 0xb, 1);
	BfmeDevice2(0x0e4, 0x0e, 1);
	BfmeDevice3(0x114, 1, 1, 1);
	BfmeDevice3(0x114, 1, 2, 1);
	BfmeDevice2(0x0e4, 3, 0x80);
	BfmeDevice3(0x10c, 0, 1, 1);
	BfmeDevice3(0x10c, 0, 4, 1);
	BfmeDevice3(0x10c, 1, 1, 1);
	BfmeDevice3(0x10c, 1, 4, 1);
	BfmeDevice3(0x10c, 2, 1, 1);
	BfmeDevice3(0x10c, 2, 4, 1);
	DX8Wrapper::_Set_DX8_Transform(D3DTS_VIEW, *(Matrix4x4 *)&matView);
	DX8Wrapper::_Set_DX8_Transform(D3DTS_PROJECTION, *(Matrix4x4 *)&matProj);
	BfmeDevice1(0x1ac, 0);
	BfmeDevice1(0x170, 0x142);
	DX8Wrapper::Invalidate_Cached_Render_States();

	BaseHeightMapRenderObjClass *terrain = TheTerrainRenderObject;
	W3DShroud *shroud = terrain == 0 ? 0 : *(W3DShroud **)((char *)terrain + 0x30b8);
	if (shroud != 0)
	{
		TextureHandle shroudTexture = shroud->getShroudTexture();
		BfmeSetTextureCache(shroudTexture.get());
		W3DShaderManager::setShader(W3DShaderManager::ST_SHROUD_TEXTURE, 0);
		BfmeDeviceStream(0, m_vertexBuffer, 0, 0x18);
		BfmeDeviceIndices(m_indexBuffer);
		patchY = (int)((seaBox.Center.Y - seaBox.Extent.Y) * scale);
		patchWorldY = patchY * 14;
		for (worldY = (float)patchWorldY * cell;
			worldY < seaBox.Center.Y + seaBox.Extent.Y;
			patchWorldY += 14)
		{
			patchX = (int)((seaBox.Center.X - seaBox.Extent.X) * scale);
			patchWorldX = patchX * 14;
			for (worldX = (float)patchWorldX * cell;
				worldX < seaBox.Center.X + seaBox.Extent.X;
				patchWorldX += 14)
			{
				D3DXMATRIX matTemp;
				patchMatrix.m[3][0] = worldX;
				patchMatrix.m[3][2] = worldY;
				D3DXMatrixMultiply(&matTemp, &patchMatrix, &matWW3D);
				DX8Wrapper::_Set_DX8_Transform(D3DTS_WORLD, *(Matrix4x4 *)&matTemp);
				BfmeDeviceDraw(5, 0, m_numVertices, 0, m_numIndices);
				worldX = (float)patchWorldX * cell;
			}
			worldY = (float)patchWorldY * cell;
		}
		W3DShaderManager::resetShader(W3DShaderManager::ST_SHROUD_TEXTURE);
	}
}
