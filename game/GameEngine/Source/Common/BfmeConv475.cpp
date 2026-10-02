// cl: /Igame /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad
// WW3D::Set_Texture_Reduction is the matched body at 0x008FE0E0 (WW3D2/ww3d.cpp);
// the real header declares it, so include it rather than respelling a stand-in.
#include "WW3D2/ww3d.h"

class BfmeThingBKA
{
public:
	void bfmeGoBKA(void *what);
	unsigned char m_bfmeHead[0x1730];
	void *m_bfmeSaved;
};

void BfmeThingBKA::bfmeGoBKA(void *what)
{
	m_bfmeSaved = what;
	WW3D::Set_Texture_Reduction((int)what, 1);
}
