// cl: /Iinputs/reference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// readable body of ?Set_Coordinate_Range@Render2DClass@@QAEXABVRectClass@@@Z: game/Libraries/Source/WWVegas/WW3D2/render2d.cpp
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
// Retail treats the canonical signed DX8Wrapper resolution words as unsigned.
// It reads each with fild and adds 2^32 when the value tests negative. Explicit
// unsigned casts below preserve that conversion without inventing a second owner.
//
// Two things about the shape rather than the semantics. The bias goes through a
// Vector2 local, not two scalars: the scalar spelling computes the same values
// and byte-matches the first 0x49 bytes, then loads the two resolution words
// into the opposite registers. And Update_Bias needs __forceinline -- this
// toolchain leaves it as a call at /O2 and emits the symbol, where retail has
// no call at all.

// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "dx8wrapper.h"
#include "ww3d.h"
#include "rect.h"

namespace {
// Static-only implementation access view, following the wrapper's existing
// access adapters. This is not a recovered retail class or inheritance claim;
// no instances, casts, layout, or additional storage are involved.
class Rva00933A50ResolutionAccess : public DX8Wrapper
{
public:
    using DX8Wrapper::ResolutionWidth;
    using DX8Wrapper::ResolutionHeight;
};
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
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
			bais_add.X = bais_add.X / (static_cast<unsigned int>(Rva00933A50ResolutionAccess::ResolutionWidth) * 0.5f);
			bais_add.Y = bais_add.Y / (static_cast<unsigned int>(Rva00933A50ResolutionAccess::ResolutionHeight) * -0.5f);

			CoordinateOffset.X = CoordinateOffset.X + bais_add.X;
			CoordinateOffset.Y = CoordinateOffset.Y + bais_add.Y;
		}
	}

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
