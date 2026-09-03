// cl: /DNDEBUG /MD
//
// Retail 0x007D74D0: Rva007D85C0::preRender.

struct IDirect3DSurface8;

struct Vector3
{
	float X;
	float Y;
	float Z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *renderTarget, bool useDefaultDepthBuffer);
};

void __cdecl bfmeClear7(bool clear_color, bool clear_z, bool clear_stencil,
	const Vector3 &color, float dest_alpha, float z, unsigned int stencil);

unsigned __cdecl bfmeCurrentCU();
void __cdecl bfmeCopyCuSnap(void *vec, void *snap);

extern unsigned char g_bfmeDirtyCU;

class Rva007D85C0
{
public:
	bool preRender(bool &skipRender, int &scenePassMode);

private:
	void *m_vptr;
	int m_04;
	int m_08;
	unsigned char m_0C;
	unsigned char m_pad0D[3];
	char m_vec[12];
	int m_1C;
	int m_20;
	int m_24;
	IDirect3DSurface8 *m_28;
};

bool Rva007D85C0::preRender(bool &skipRender, int &scenePassMode)
{
	union {
		int snap[6];
		Vector3 color;
	} local;
	skipRender = false;
	if (g_bfmeDirtyCU)
	{
		local.snap[0] = 2;
		local.snap[1] = *(int *)(bfmeCurrentCU() + 4);
		local.snap[3] = *(int *)(bfmeCurrentCU() + 0x14);
		local.snap[5] = *(int *)(bfmeCurrentCU() + 0x1C);
		local.snap[2] = *(int *)(bfmeCurrentCU() + 0x10);
		local.snap[4] = *(int *)(bfmeCurrentCU() + 0x18);
		bfmeCopyCuSnap(m_vec, local.snap);
		g_bfmeDirtyCU = 0;
	}
	DX8Wrapper::Set_Render_Target(m_28, true);
	local.color.X = 0.0f;
	local.color.Y = 0.0f;
	local.color.Z = 0.0f;
	bfmeClear7(true, false, false, local.color, 0.0f, 1.0f, 0);
	m_0C = 1;
	return true;
}
