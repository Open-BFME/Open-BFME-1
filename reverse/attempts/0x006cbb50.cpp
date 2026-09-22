// ?getHeightMapHeight@BaseHeightMapRenderObjClass@@QBEMMMPAUCoord3D@@@Z
// partial score=0.43 date=2026-09-22
// cl: /O2 /Ob1 /Oy /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef float Real;
typedef int Int;
typedef unsigned short UnsignedShort;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

extern const Real BfmeZeroRange;
extern const Real g_bfmeScaleBK;
extern const Real g_bfmeDefaultBU;

#define Rva010F653CHeightScale (*(const Real *)0x010F653C)
#define Rva010977E0NormalAxis (*(const Real *)0x010977E0)
#define Rva01096418NormalAxisSquared (*(const Real *)0x01096418)
#define Rva0111D88CNormalLengthBias (*(const Real *)0x0111D88C)

extern "C" __declspec(dllimport) double __cdecl floor(double value);

__forceinline Int bfmeFloatToLong(Real value)
{
	Int result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

class WWMath
{
public:
	static Real __fastcall Inv_Sqrt(Real value);
};

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;

	__forceinline void Set(Real x, Real y, Real z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	__forceinline void Normalize(void)
	{
		Real lengthSquared = Length2();
		if (lengthSquared != BfmeZeroRange)
		{
			Real inverseLength = WWMath::Inv_Sqrt(lengthSquared);
			X *= inverseLength;
			Y *= inverseLength;
			Z *= inverseLength;
		}
	}

	__forceinline Real Length2(void) const
	{
		return X * X + Y * Y + Z * Z;
	}

	static __forceinline void Normalized_Cross_Product(const Vector3 &a, const Vector3 &b, Vector3 *result)
	{
		result->X = a.Y * b.Z - a.Z * b.Y;
		result->Y = a.Z * b.X - a.X * b.Z;
		result->Z = a.X * b.Y - a.Y * b.X;
		result->Normalize();
	}
};

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
	Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;
	UnsignedShort getClipHeight(Int x, Int y) const;

private:
	char m_pad[0x2FF4];
	WorldHeightMap *m_map;
};

Real BaseHeightMapRenderObjClass::getHeightMapHeight(Real x, Real y, Coord3D *normal) const
{
	if (!m_map)
	{
		if (normal)
		{
			normal->x = 0.0f;
			normal->y = 0.0f;
			normal->z = 1.0f;
		}
		return BfmeZeroRange;
	}

	Real xdiv = x * g_bfmeScaleBK;
	Real ydiv = y * g_bfmeScaleBK;
	Real ixf = (Real)floor((double)xdiv);
	Real iyf = (Real)floor((double)ydiv);
	Real fx = xdiv - ixf;
	Real fy = ydiv - iyf;
	Int ix = bfmeFloatToLong((Real)floor((double)ixf)) + m_map->m_borderSize;
	Int iy = bfmeFloatToLong((Real)floor((double)iyf)) + m_map->m_borderSize;
	Int xExtent = m_map->m_width;

	if (ix > xExtent - 3 || iy > m_map->m_height - 3 || iy < 1 || ix < 1)
	{
		if (normal)
		{
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
	if (fy > fx)
	{
		Real p3 = data[idx + xExtent];
		height = (p3 + (g_bfmeDefaultBU - fy) * (p0 - p3) + fx * (p2 - p3)) * Rva010F653CHeightScale;
	}
	else
	{
		Real p1 = data[idx + 1];
		height = (p1 + fy * (p2 - p1) + (g_bfmeDefaultBU - fx) * (p0 - p1)) * Rva010F653CHeightScale;
	}

	if (normal)
	{
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

		Real deltaZ_X_Left = deltaZ_X0 * (g_bfmeDefaultBU - fx) + fx * deltaZ_X3;
		Real deltaZ_X_Right = deltaZ_X1 * (g_bfmeDefaultBU - fx) + fx * deltaZ_X2;
		Real deltaZ_X = deltaZ_X_Left * (1.0 - fy) + fy * deltaZ_X_Right;
		Real deltaZ_Y_Left = deltaZ_Y0 * (g_bfmeDefaultBU - fx) + fx * deltaZ_Y3;
		Real deltaZ_Y_Right = deltaZ_Y1 * (g_bfmeDefaultBU - fx) + fx * deltaZ_Y2;
		Real deltaZ_Y = deltaZ_Y_Left * (1.0 - fy) + fy * deltaZ_Y_Right;

		Vector3 l2r, n2f;
		l2r.Set(Rva010977E0NormalAxis, 0.0f, deltaZ_X * Rva010F653CHeightScale);
		n2f.Set(0.0f, Rva010977E0NormalAxis, deltaZ_Y * Rva010F653CHeightScale);
		Real normalX = l2r.Y * n2f.Z - l2r.Z * n2f.Y;
		Real normalY = l2r.Z * n2f.X - l2r.X * n2f.Z;
		Real normalZ = l2r.X * n2f.Y - l2r.Y * n2f.X;
		Real lengthSquared = normalX * normalX + normalY * normalY + normalZ * normalZ;
		if (lengthSquared != BfmeZeroRange)
		{
			Real inverseLength = WWMath::Inv_Sqrt(lengthSquared);
			normalX *= inverseLength;
			normalY *= inverseLength;
			normalZ *= inverseLength;
		}
		normal->x = normalX;
		normal->y = normalY;
		normal->z = normalZ;
	}

	return height;
}
