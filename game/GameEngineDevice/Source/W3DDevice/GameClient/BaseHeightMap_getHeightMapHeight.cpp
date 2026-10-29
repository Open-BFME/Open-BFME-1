// ?getHeightMapHeight@BaseHeightMapRenderObjClass@@UBEMMMPAVCoord3D@@@Z
// Height and smoothed normal from the BFME unsigned-word heightmap.
// cl: /O2 /Ob1 /Oy /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/shims/sweep

typedef float Real;
typedef int Int;
typedef unsigned short UnsignedShort;

#include "coord3d.h"
#include "vector3.h"

extern const Real g_bfmeScaleBK;
extern Real g_bfmeDefaultBU;

#define Rva010F653CHeightScale 0.0390625f
#define Rva010977E0NormalAxis 20.0f
#define Rva01096418NormalAxisSquared 400.0f
#define Rva0111D88CNormalLengthBias 160000.0f

extern "C" __declspec(dllimport) double __cdecl floor(double value);

// ?bfmeFloatToLong@@YAHM@Z absent-from-retail
__forceinline Int bfmeFloatToLong(Real value)
{
	Int result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

class WorldHeightMap
{
public:
	char m_header[8];
	Int m_width;
	Int m_height;
	Int m_borderSize;
	char m_layout[0x10];
	UnsignedShort *m_data;
};

class BaseHeightMapRenderObjClass
{
public:
	virtual Real getHeightMapHeight(Real x, Real y, class Coord3D *normal) const;
	UnsignedShort getClipHeight(Int x, Int y) const;

private:
	char m_pad[0x2FF0];
	WorldHeightMap *m_map;
};

// ?getHeightMapHeight@BaseHeightMapRenderObjClass@@UBEMMMPAVCoord3D@@@Z
/** return the height and normal of the triangle plane containing given location within heightmap. */
Real BaseHeightMapRenderObjClass::getHeightMapHeight(Real x, Real y, class Coord3D *normal) const
{
	if (!m_map)
	{
		if (normal)
		{
			// return a default normal pointing up
			normal->x = 0.0f;
			normal->y = 0.0f;
			normal->z = 1.0f;
		}
		return 0.0f;
	}

	//	3-----2
	//  |    /|
	//  |  /  |
	//	|/    |
	//  0-----1
	//Find surrounding grid points
	Real xdiv = x * 0.1f;
	Real ydiv = y * 0.1f;
	Real ixf = (Real)floor((double)xdiv);
	Real iyf = (Real)floor((double)ydiv);
	Real fx = xdiv - ixf; //get fraction
	Real fy = ydiv - iyf; //get fraction
	// since ixf & iyf are already floor'ed, we can use the fastest f->i conversion we have...
	Int ix = bfmeFloatToLong((Real)floor((double)ixf)) + m_map->m_borderSize;
	Int iy = bfmeFloatToLong((Real)floor((double)iyf)) + m_map->m_borderSize;
	Int xExtent = m_map->m_width;

	// Check for extent-3, not extent-1: we go into the next row/column of data for smoothed triangle points, so extent-1
	// goes off the end...
	if (ix > xExtent - 3 || iy > m_map->m_height - 3 || iy < 1 || ix < 1)
	{
		// sample point is not on the heightmap
		if (normal)
		{
			// return a default normal pointing up
			normal->x = 0.0f;
			normal->y = 0.0f;
			normal->z = 1.0f;
		}
		return getClipHeight(ix, iy) * Rva010F653CHeightScale;
	}

	const UnsignedShort *data = m_map->m_data;
	Int idx = ix + iy * xExtent;
	Real p0 = data[idx];
	Real p2 = data[idx + xExtent + 1];
	Real height;
	if (fy > fx) // test if we are in the upper triangle
	{
		Real p3 = data[idx + xExtent];
		height = ((1.0f - fy) * (p0 - p3) + fx * (p2 - p3) + p3) * Rva010F653CHeightScale;
	}
	else
	{
		// we are in the lower triangle
		Real p1 = data[idx + 1];
		height = ((1.0f - fx) * (p0 - p1) + fy * (p2 - p1) + p1) * Rva010F653CHeightScale;
	}

	if (normal)
	{
		//		9		  8
		//
		//10	3-----2		7
		//	  |    /|
		//	  |  /  |
		//		|/    |
		//11	0-----1		6
		//
		//		4			5
		//Find surrounding grid points for smoothed normals.
		Int idx4 = ix + (iy - 1) * xExtent;
		Int idx0 = ix + iy * xExtent;
		Int idx3 = ix + iy * xExtent + xExtent;
		Int idx9 = ix + (iy + 2) * xExtent;
		UnsignedShort d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11;
		d0 = data[idx0];
		d1 = data[idx0 + 1];
		d2 = data[idx3 + 1];
		d3 = data[idx3];
		d4 = data[idx4];
		d5 = data[idx4 + 1];
		d6 = data[idx0 + 2];
		d7 = data[idx3 + 2];
		d8 = data[idx9 + 1];
		d9 = data[idx9];
		d10 = data[idx3 - 1];
		d11 = data[idx0 - 1];

		Real deltaZ_X0 = d1 - d11;
		Real deltaZ_X1 = d6 - d0;
		Real deltaZ_X2 = d7 - d3;
		Real deltaZ_X3 = d6 - d0;
		Real deltaZ_Y0 = d3 - d4;
		Real deltaZ_Y1 = d2 - d5;
		Real deltaZ_Y2 = d8 - d1;
		Real deltaZ_Y3 = d9 - d0;

		// Interpolate to get the smoothed valued.
		Real deltaZ_X_Left = deltaZ_X0 * (1.0f - fx) + fx * deltaZ_X3;
		Real deltaZ_X_Right = deltaZ_X1 * (1.0f - fx) + fx * deltaZ_X2;
		Real deltaZ_X = deltaZ_X_Left * (1.0 - fy) + fy * deltaZ_X_Right;
		Real deltaZ_Y_Left = deltaZ_Y0 * (1.0f - fx) + fx * deltaZ_Y3;
		Real deltaZ_Y_Right = deltaZ_Y1 * (1.0f - fx) + fx * deltaZ_Y2;
		Real deltaZ_Y = deltaZ_Y_Left * (1.0 - fy) + fy * deltaZ_Y_Right;

		Vector3 l2r, n2f;
		l2r.Set(Rva010977E0NormalAxis, 0.0f, deltaZ_X * Rva010F653CHeightScale);
		n2f.Set(0.0f, Rva010977E0NormalAxis, deltaZ_Y * Rva010F653CHeightScale);
		Vector3 normalAtTexel;
		Vector3::Normalized_Cross_Product(l2r, n2f, &normalAtTexel);
		Real normalX = normalAtTexel.X;
		Real normalY = normalAtTexel.Y;
		Real normalZ = normalAtTexel.Z;
		normal->x = normalX;
		normal->y = normalY;
		normal->z = normalZ;
	}

	return height;
}
