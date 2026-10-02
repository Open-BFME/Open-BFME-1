// cl: /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include

#include "vector3.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	// Retail 0x00904250: BFME's seven-argument Clear (see WW3D2/DX8Wrapper_Clear.cpp).
	static void Clear(bool clear_color, bool clear_z, bool clear_stencil,
		const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};

class Rva0078B280Renderer
{
public:
	void bfmeAdvanceStencil(void);
	bool bfmeHasStencil(void);

	char m_pad00[0xc];
	int m_stencilGeneration;
};

// @?bfmeAdvanceStencil@Rva0078B280Renderer@@QAEXXZ 0x0078B280
void Rva0078B280Renderer::bfmeAdvanceStencil(void)
{
	if (bfmeHasStencil()) {
		++m_stencilGeneration;
		if (m_stencilGeneration > 255)
			m_stencilGeneration = 1;
		if (m_stencilGeneration != 1)
			return;

		Vector3 color;
		color.X = 0.0f;
		color.Y = 0.0f;
		color.Z = 0.0f;
		DX8Wrapper::Clear(false, false, true, color, 0.0f, 0.0f, 0);
	} else {
		Vector3 color;
		color.X = 0.0f;
		color.Y = 0.0f;
		color.Z = 0.0f;
		DX8Wrapper::Clear(false, true, true, color, 0.0f, 0.0f, 0);
	}
}
