// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
//
// Retail 0x007D9540: thiscall preRender-shaped body.  skipRender=false, bind
// this+0x1C as a render target, Clear(color only), and return true.

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

class ScreenFilterPreRenderNoPassHost
{
public:
	bool preRender(bool &skipRender, int &scenePassMode);

private:
	char pad[0x1C];
	IDirect3DSurface8 *m_surface;
};

bool ScreenFilterPreRenderNoPassHost::preRender(bool &skipRender, int &scenePassMode)
{
	skipRender = false;
	DX8Wrapper::Set_Render_Target(m_surface, true);
	Vector3 color;
	color.X = 0.0f;
	color.Y = 0.0f;
	color.Z = 0.0f;
	DX8Wrapper::Clear(true, false, false, color, 0.0f, 1.0f, 0);
	return true;
}
