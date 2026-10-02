// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
//
// Retail 0x007D74D0: Rva007D85C0::preRender.

#include "vector3.h"

struct IDirect3DSurface8;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *renderTarget, bool useDefaultDepthBuffer);
	// Retail 0x00904250: BFME's seven-argument Clear (see WW3D2/DX8Wrapper_Clear.cpp).
	static void Clear(bool clear_color, bool clear_z, bool clear_stencil,
		const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};

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
	// The real class Vector3 is not a POD, so the shared 24-byte local stays a
	// union of ints and is viewed as a Vector3 only where the caller needs one.
	union {
		int snap[6];
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
	reinterpret_cast<Vector3 *>(&local)->X = 0.0f;
	reinterpret_cast<Vector3 *>(&local)->Y = 0.0f;
	reinterpret_cast<Vector3 *>(&local)->Z = 0.0f;
	DX8Wrapper::Clear(true, false, false, *reinterpret_cast<const Vector3 *>(&local), 0.0f, 1.0f, 0);
	m_0C = 1;
	return true;
}
