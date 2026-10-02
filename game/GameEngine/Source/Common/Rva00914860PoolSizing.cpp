// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I game/Libraries/Source/WWVegas/WWLib /I game/Libraries/Source/WWVegas/WWMath /I game/Libraries/Source/WWVegas/WW3D2
// Open-BFME5: clean C++ conversion of the three-pool size update.

#include "vector.h"
#include "vector4.h"

// The third growth call this function makes goes to retail 0x009131E0 --
// ?Resize@?$VectorClass@VVector4@@@@UAE_NHPBVVector4@@@Z -- and does so by a
// direct (non-virtual, qualified) call, so the pool really is a VVector4
// vector and the caller reaches past any override to VectorClass's own
// implementation. Declared, never defined here: that 550-byte body is already
// matched by game/Libraries/Source/WWVegas/WWLib/VectorClassResizeNothrowDelete.cpp,
// and the explicit specialization declaration keeps this TU from emitting a
// second copy of it.
template <> bool VectorClass<Vector4>::Resize(int newsize, Vector4 const *array);

class Rva00914860PoolA
{
public:
	bool allocate(int count, int extra);
};

class Rva00914860PoolB
{
public:
	bool allocate(int count, int extra);
};

class Rva00914860PoolC
{
public:
	bool allocate(int count, int extra);
};

extern Rva00914860PoolA g_rva00914860PoolA;
extern Rva00914860PoolB g_rva00914860PoolB;
extern Rva00914860PoolC g_rva00914860PoolC;
extern int g_rva00914860Limit;

class Rva00914860Sizer
{
public:
	void updatePoolSizes(int width, int height, int *storedWidth);

private:
	char m_pad00[0x2C];
	int m_sizeMode;
};

void Rva00914860Sizer::updatePoolSizes(int width, int height, int *storedWidth)
{
	int scale = m_sizeMode == 1 ? 4 : 3;
	int scaledHeight = scale * height;
	int scaledWidth = scale * width;
	*storedWidth = scaledWidth;

	if (g_rva00914860Limit < scaledHeight)
	{
		int count = scaledHeight * 2;
		g_rva00914860PoolA.allocate(count, 0);
		g_rva00914860PoolB.allocate(count, 0);
		reinterpret_cast<VectorClass<Vector4> &>(g_rva00914860PoolC).VectorClass<Vector4>::Resize(count, 0);
	}
}
