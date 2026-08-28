// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?Set_Coordinate_Range@Render2DClass@@QAEXABVRectClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp
// Open-BFME5: Render2DClass::Set_Coordinate_Range, retail 0x00933A50,
// converted out of a machine byte dump.
//
// The reference body is four assignments and a call to Update_Bias, and retail
// inlines the call. What that inlining shows is a real difference: the reference
// copies CoordinateOffset into a separate BiasedCoordinateOffset and biases the
// copy, where retail adds the bias straight into CoordinateOffset at +0x0C and
// +0x10 -- the same two floats it had just written. So BFME keeps one offset,
// not two.
//
// The class falls out of the same bytes: CoordinateScale at +0x04,
// CoordinateOffset at +0x0C, both Vector2.
//
// The screen resolution is two UNSIGNED ints. Retail reads each with fild and
// then adds 2^32 when the value tests negative, which is the unsigned-to-float
// conversion and not something a signed Int would need.
//
// Two things about the shape rather than the semantics. The bias goes through a
// Vector2 local, not two scalars: the scalar spelling computes the same values
// and byte-matches the first 0x49 bytes, then loads the two resolution words
// into the opposite registers. And Update_Bias needs __forceinline -- this
// toolchain leaves it as a call at /O2 and emits the symbol, where retail has
// no call at all.

typedef float Real;

class Vector2
{
public:
	Vector2( void ) { }
	Vector2( Real x, Real y ) : X(x), Y(y) { }

	Real X;
	Real Y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/rect.h
class RectClass
{
public:
	Real Width( void ) const { return Right - Left; }
	Real Height( void ) const { return Bottom - Top; }

	Real Left;												///< +0x00
	Real Top;												///< +0x04
	Real Right;												///< +0x08
	Real Bottom;											///< +0x0C
};

class ScreenResolution
{
public:
	unsigned int Width( void ) const { return m_width; }
	unsigned int Height( void ) const { return m_height; }

	unsigned int m_width;
	unsigned int m_height;
};

extern ScreenResolution TheScreenResolution;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static bool Is_Screen_UV_Biased( void ) { return IsScreenUVBiased; }

private:
	static bool IsScreenUVBiased;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
class Render2DClass
{
public:
	void Set_Coordinate_Range( const RectClass &range );

protected:
	__forceinline void Update_Bias( void )
	{
		if ( WW3D::Is_Screen_UV_Biased() ) {	// Global bais setting
			Vector2 bais_add( -0.5f, -0.5f );	// offset by -0.5,-0.5 in pixels

			// Convert from pixels to (-1,1)-(1,-1) units
			bais_add.X = bais_add.X / (Get_Screen_Resolution().Width() * 0.5f);
			bais_add.Y = bais_add.Y / (Get_Screen_Resolution().Height() * -0.5f);

			CoordinateOffset.X = CoordinateOffset.X + bais_add.X;
			CoordinateOffset.Y = CoordinateOffset.Y + bais_add.Y;
		}
	}

	static const ScreenResolution &Get_Screen_Resolution( void ) { return TheScreenResolution; }

private:
	void *m_vtable;
	Vector2 CoordinateScale;								///< +0x04
	Vector2 CoordinateOffset;								///< +0x0C
};

// ?Set_Coordinate_Range@Render2DClass@@QAEXABVRectClass@@@Z
void	Render2DClass::Set_Coordinate_Range( const RectClass & range )
{
	// default range is (-1,1)-(1,-1)
	CoordinateScale.X = 2 / range.Width();
	CoordinateScale.Y = -2 / range.Height();
	CoordinateOffset.X = -(CoordinateScale.X * range.Left) - 1;
	CoordinateOffset.Y = -(CoordinateScale.Y * range.Top) + 1;

	Update_Bias();
}
