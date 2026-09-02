// ?d_007dcf00@@YAXXZ
// partial score=0.65 date=2026-09-02
// cl: /O2 /Ob0

struct Rva007DCF00Matrix
{
	float m[16];
};

struct Rva007DCF00Viewport
{
	int m_00;
	int m_04;
	int width;
	int height;
	int border;
};

struct Rva007DCF00GlobalData
{
	unsigned char m_pad00[0x2FF4];
	Rva007DCF00Viewport *viewport;
	unsigned char m_pad2FF8[0x74];
	bool useViewportMatrix;
};

extern Rva007DCF00GlobalData *TheGlobalData;
extern float g_bfmeDirectionWeight1285;
extern float g_bfmeInvalidScore1285;
extern float g_bfmeDefaultBU;

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

	if (TheGlobalData->useViewportMatrix)
	{
		Rva007DCF00Viewport *viewport = TheGlobalData->viewport;
		volatile int borderPixels = viewport->border;
		int widthPixels = viewport->width;
		int heightPixels = viewport->height;
		Rva007DCF00Matrix offset;
		float border = borderPixels * g_bfmeDirectionWeight1285;
		D3DXMatrixTranslation(&offset, border, border, 0.0f);
		D3DXMatrixScaling(&scale,
			g_bfmeInvalidScore1285 / (widthPixels * g_bfmeDirectionWeight1285),
			g_bfmeDefaultBU / (heightPixels * g_bfmeDirectionWeight1285),
			1.0f);
		D3DXMatrixMultiply(&result, &offset, &scale);
		scale = result;
		D3DXMatrixMultiply(&result, curViewInverse, &scale);
	}
	else
	{
		D3DXMatrixScaling(&scale, 0.0015151514671742916f, -0.0015151514671742916f, 1.0f);
		D3DXMatrixMultiply(&result, curViewInverse, &scale);
	}

	*destMatrix = result;
}
