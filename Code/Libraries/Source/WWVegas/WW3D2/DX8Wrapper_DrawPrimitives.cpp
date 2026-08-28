// cl: /DNDEBUG /MD /EHsc
// readable body of ?Draw_Strip@DX8Wrapper@@: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp

// DX8Wrapper::Draw_Triangles (0x00906DF0) and DX8Wrapper::Draw_Strip
// (0x00906E40). Thirty-three bytes each and the same body but for one
// immediate: both forward their four arguments to the helper at 0x00906B40
// with a leading mode constant - 4 for triangles, 5 for strips - and a trailing
// 1. That helper is unnamed in the image and is pinned here.

typedef unsigned short UnsignedShort;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Draw_Triangles( UnsignedShort a, UnsignedShort b, UnsignedShort c, UnsignedShort d );
	static void Draw_Strip( UnsignedShort a, UnsignedShort b, UnsignedShort c, UnsignedShort d );

private:
	static void Draw( int mode, UnsignedShort a, UnsignedShort b, UnsignedShort c, UnsignedShort d, int one );
};

// ?Draw_Triangles@DX8Wrapper@@SAXGGGG@Z
void DX8Wrapper::Draw_Triangles( UnsignedShort a, UnsignedShort b, UnsignedShort c, UnsignedShort d )
{
	Draw( 4, a, b, c, d, 1 );
}

// ?Draw_Strip@DX8Wrapper@@SAXGGGG@Z
void DX8Wrapper::Draw_Strip( UnsignedShort a, UnsignedShort b, UnsignedShort c, UnsignedShort d )
{
	Draw( 5, a, b, c, d, 1 );
}
