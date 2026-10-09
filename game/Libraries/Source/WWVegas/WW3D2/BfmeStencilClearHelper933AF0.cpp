// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
#include "vector3.h"
class DX8Wrapper
{
public:
	static bool Has_Stencil();
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};
extern char g_bfme911Flag;
extern int g_bfmeBlendDst;
// ?bfmeStencilClearHelper933AF0@@YAXXZ
// Open BFME 2 donor Code/Libraries/Source/WWVegas/WW3D2/Rva00118AC0Finish.cpp.
void __cdecl bfmeStencilClearHelper933AF0()
{
	g_bfme911Flag = 1;
	if (DX8Wrapper::Has_Stencil())
	{
		int v = --g_bfmeBlendDst;
		if (v < 1)
			g_bfmeBlendDst = 0xff;
		else if (v != 0xff)
			return;
		Vector3 black(0.0f, 0.0f, 0.0f);
		DX8Wrapper::Clear(false, false, true, black, 0.0f, 0.0f, 0);
	}
	else
	{
		Vector3 black(0.0f, 0.0f, 0.0f);
		DX8Wrapper::Clear(false, true, true, black, 0.0f, 0.0f, 0);
	}
}
