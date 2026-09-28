// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// RVA 0072B1C0 (759 B, thiscall, ret 2Ch): terrain quad split by edge state.
// Clears four caller flags, asks the matched checkEdges (0x00729D30, same
// object) which edge midpoints of the square (x, y, w) fail the bit-plane test,
// then recurses into the 0x0072A3D0 body (ILT 0x0000FB00) on half-width
// strips and sets the flags. EA file per the wb1 run: W3DTerrainBackground.cpp;
// no Zero Hour twin, so class and method names stay address-derived.
typedef unsigned char Byte;
struct Rva00729300BitPlane;

class Rva00729D30Terrain
{
public:
	void checkEdges( int xOffset, int yOffset, int width,
		bool *top, bool *right, bool *bottom, bool *left );
	void rva0072A3D0( int arg0, int arg1, int xOffset, int yOffset,
		int width, int height, int arg6, int arg7 );
	void rva0072B1C0( int arg0, int arg1, int xOffset, int yOffset, int width,
		bool *flag0, bool *flag1, bool *flag2, bool *flag3, int arg9, int arg10 );

private:
	Byte m_opaque00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva00729300BitPlane *m_map;
};

void Rva00729D30Terrain::rva0072B1C0( int arg0, int arg1, int xOffset, int yOffset, int width,
	bool *flag0, bool *flag1, bool *flag2, bool *flag3, int arg9, int arg10 )
{
	*flag0 = *flag1 = *flag2 = *flag3 = false;
	bool top, right, bottom, left;
	checkEdges( xOffset, yOffset, width, &top, &right, &bottom, &left );
	int half = width / 2;
	if( right )
	{
		if( top )
		{
			rva0072A3D0( arg0, arg1, xOffset, yOffset, half, width, arg9, arg10 );
			rva0072A3D0( arg0, arg1, xOffset, yOffset + half, width, half, arg9, arg10 );
			*flag3 = true;
		}
		else if( bottom )
		{
			rva0072A3D0( arg0, arg1, xOffset, yOffset + half, width, half, arg9, arg10 );
			rva0072A3D0( arg0, arg1, xOffset + half, yOffset, half, width, arg9, arg10 );
			*flag2 = true;
		}
		else
		{
			rva0072A3D0( arg0, arg1, xOffset, yOffset + half, width, half, arg9, arg10 );
			*flag3 = true;
			*flag2 = true;
		}
	}
	else if( left )
	{
		if( top )
		{
			rva0072A3D0( arg0, arg1, xOffset, yOffset, half, width, arg9, arg10 );
			rva0072A3D0( arg0, arg1, xOffset, yOffset, width, half, arg9, arg10 );
			*flag1 = true;
		}
		else if( bottom )
		{
			rva0072A3D0( arg0, arg1, xOffset, yOffset, width, half, arg9, arg10 );
			rva0072A3D0( arg0, arg1, xOffset + half, yOffset, half, width, arg9, arg10 );
			*flag0 = true;
		}
		else
		{
			rva0072A3D0( arg0, arg1, xOffset, yOffset, width, half, arg9, arg10 );
			*flag1 = true;
			*flag0 = true;
		}
	}
	else if( top )
	{
		*flag3 = true;
		*flag1 = true;
		rva0072A3D0( arg0, arg1, xOffset, yOffset, half, width, arg9, arg10 );
	}
	else if( bottom )
	{
		*flag2 = true;
		*flag0 = true;
		rva0072A3D0( arg0, arg1, xOffset + half, yOffset, half, width, arg9, arg10 );
	}
	else
	{
		*flag3 = true;
		*flag2 = true;
		*flag1 = true;
		*flag0 = true;
	}
}
