// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?Convert_Vert@Render2DClass@@: Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp
// BFME Render2DClass::Convert_Vert, retail 0x006E7190 (42 B) and 0x006E71D0 (41 B).
//
// Zero Hour writes a Vector2 through BiasedCoordinateOffset. BFME keeps one
// offset at +0x0C (see Set_Coordinate_Range) and writes a third coordinate
// from g_BfmeRender2DZ, the same global Add_Quad stores into each vertex.
// Layout: CoordinateScale at +0x04, CoordinateOffset at +0x0C.

class Vector2
{
public:
	float X;
	float Y;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

extern "C" float g_BfmeRender2DZ;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
class Render2DClass
{
public:
	void Convert_Vert(Vector3 &vert_out, const Vector2 &vert_in);
	void Convert_Vert(Vector3 &vert_out, float x_in, float y_in);

private:
	void *m_vtable;
	Vector2 CoordinateScale;
	Vector2 CoordinateOffset;
};

// ?Convert_Vert@Render2DClass@@QAEXAAVVector3@@ABVVector2@@@Z
void Render2DClass::Convert_Vert(Vector3 &vert_out, const Vector2 &vert_in)
{
	vert_out.X = CoordinateScale.X * vert_in.X + CoordinateOffset.X;
	vert_out.Y = vert_in.Y * CoordinateScale.Y + CoordinateOffset.Y;
	vert_out.Z = g_BfmeRender2DZ;
}

// ?Convert_Vert@Render2DClass@@QAEXAAVVector3@@MM@Z
void Render2DClass::Convert_Vert(Vector3 &vert_out, float x_in, float y_in)
{
	vert_out.X = x_in * CoordinateScale.X + CoordinateOffset.X;
	vert_out.Y = y_in * CoordinateScale.Y + CoordinateOffset.Y;
	vert_out.Z = g_BfmeRender2DZ;
}
