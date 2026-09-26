// Terrain texture matrix at retail RVA 0x007DCF00, 281 bytes.
// Existing g_bfmeG1059 pin denotes TheTerrainRenderObject at VA 0x012F7FE0.
// +0x2FF4 is its WorldHeightMap: width +8, height +12, border +16.
// Original field volatility is unknown; volatile preserves the retail read order.
// Matrix owner/method identity remains address-derived.
// Keep the final copy inside each branch: MSVC merges the tails while
// preserving retail lea-then-count setup of the final rep movsd.
// cl: /O2 /Ob0

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

class BfmeG1059
{
public:
	unsigned char m_pad00[0x2FF4];
	Rva007DCF00HeightMap *heightMap;
	unsigned char m_pad2FF8[0x74];
	bool useHeightMapMatrix;
};

extern BfmeG1059 *g_bfmeG1059;

extern "C" Rva007DCF00Matrix *__stdcall D3DXMatrixTranslation(
	Rva007DCF00Matrix *, float, float, float);
extern "C" Rva007DCF00Matrix *__stdcall D3DXMatrixScaling(
	Rva007DCF00Matrix *, float, float, float);
extern "C" Rva007DCF00Matrix *__stdcall D3DXMatrixMultiply(
	Rva007DCF00Matrix *, const Rva007DCF00Matrix *, const Rva007DCF00Matrix *);

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

	if (g_bfmeG1059->useHeightMapMatrix)
	{
		Rva007DCF00HeightMap *heightMap = g_bfmeG1059->heightMap;
		int borderPixels = heightMap->border;
		int widthPixels = heightMap->width;
		int heightPixels = heightMap->height;
		Rva007DCF00Matrix offset;
		float border = borderPixels * 10.0f;
		D3DXMatrixTranslation(&offset, border, border, 0.0f);
		D3DXMatrixScaling(&scale,
			1.0f / (widthPixels * 10.0f),
			-1.0f / (heightPixels * 10.0f),
			1.0f);
		D3DXMatrixMultiply(&result, &offset, &scale);
		scale = result;
		D3DXMatrixMultiply(&result, curViewInverse, &scale);
		*destMatrix = result;
	}
	else
	{
		D3DXMatrixScaling(&scale, 0.0015151514671742916f, -0.0015151514671742916f, 1.0f);
		D3DXMatrixMultiply(&result, curViewInverse, &scale);
		*destMatrix = result;
	}

}
