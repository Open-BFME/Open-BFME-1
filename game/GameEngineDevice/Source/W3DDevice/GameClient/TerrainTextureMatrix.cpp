// Terrain texture matrix at retail RVA 0x007DCF00, 281 bytes.
// Canonical TheTerrainRenderObject is owned by BaseHeightMap.cpp at VA 0x012F7FE0.
// +0x2FF4 is its WorldHeightMap: width +8, height +12, border +16.
// Original field volatility is unknown; volatile preserves the retail read order.
// Matrix owner/method identity remains address-derived.
// Keep the final copy inside each branch: MSVC merges the tails while
// preserving retail lea-then-count setup of the final rep movsd.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmeheightmap /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "W3DDevice/GameClient/BaseHeightMap.h"

struct Rva007DCF00Matrix
{
	float m[16];
};

struct Rva007DCF00HeightMap
{
	int m_00;
	int m_04;
	int width;
	int height;
	volatile int border;
};

class Rva007DCF00TextureMatrix
{
public:
	void build(Rva007DCF00Matrix *destMatrix,
		Rva007DCF00Matrix *curViewInverse, bool doUpdate);
};

void Rva007DCF00TextureMatrix::build(Rva007DCF00Matrix *destMatrix,
	Rva007DCF00Matrix *curViewInverse, bool doUpdate)
{
	Rva007DCF00Matrix result;
	Rva007DCF00Matrix scale;

	// The meaning of the native byte at +0x306C is unproven.
	if (*((unsigned char *)TheTerrainRenderObject + 0x306C))
	{
		Rva007DCF00HeightMap *heightMap =
			*(Rva007DCF00HeightMap **)((char *)TheTerrainRenderObject + 0x2FF4);
		int borderPixels = heightMap->border;
		int widthPixels = heightMap->width;
		int heightPixels = heightMap->height;
		Rva007DCF00Matrix offset;
		float border = borderPixels * 10.0f;
		D3DXMatrixTranslation((D3DXMATRIX *)&offset, border, border, 0.0f);
		D3DXMatrixScaling((D3DXMATRIX *)&scale,
			1.0f / (widthPixels * 10.0f),
			-1.0f / (heightPixels * 10.0f),
			1.0f);
		D3DXMatrixMultiply((D3DXMATRIX *)&result, (D3DXMATRIX *)&offset, (D3DXMATRIX *)&scale);
		scale = result;
		D3DXMatrixMultiply((D3DXMATRIX *)&result, (const D3DXMATRIX *)curViewInverse, (D3DXMATRIX *)&scale);
		*destMatrix = result;
	}
	else
	{
		D3DXMatrixScaling((D3DXMATRIX *)&scale, 0.0015151514671742916f, -0.0015151514671742916f, 1.0f);
		D3DXMatrixMultiply((D3DXMATRIX *)&result, (const D3DXMATRIX *)curViewInverse, (D3DXMATRIX *)&scale);
		*destMatrix = result;
	}

}
