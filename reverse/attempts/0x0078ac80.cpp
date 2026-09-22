// ?rva0078ac80@@YGXPAUCoord2D@@000@Z
// partial score=0.46 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
//
// Retail RVA 0x0078AC80 (207 bytes). A free __stdcall helper (ret 0x10, no
// `this`) that clips a screen-space rect against the current render target's
// width: it floors the two input axes at BfmeZeroRange, then for each axis
// caps the remaining span at (renderTargetWidth - flooredAxis) once the
// floored-axis-plus-offset would overflow it.  Only the render target WIDTH
// is used for both axes -- retail fetches the height too (WW3D::
// Get_Render_Target_Resolution's second out-param) but never reads it back,
// so this reuses one scratch float for both compares exactly as retail's
// stack slot does.  callers_of finds no named caller and find_emitter finds
// no source owner, so this lands under an opaque address-derived name.

typedef bool Bool;

struct Coord2D
{
	float x;
	float y;
};

// matched callee: ?BfmeZeroRange@@3MB
extern const float BfmeZeroRange;

// pinned callee: ?forward@Rva008FD1F0RenderTargetResolutionThunk@@SAXAAH00AA_N@Z
class Rva008FD1F0RenderTargetResolutionThunk
{
public:
	static void forward( int &setW, int &setH, int &setBits, Bool &setWindowed );
};

// ?rva0078ac80@@YGXPAUCoord2D@@000@Z
void __stdcall rva0078ac80( Coord2D *in, Coord2D *offset, Coord2D *outMin, Coord2D *outMax )
{
	int rtW = 0;
	int rtH = 0;
	int rtBits = 0;
	Bool rtWindowed = false;
	Rva008FD1F0RenderTargetResolutionThunk::forward( rtW, rtH, rtBits, rtWindowed );

	float x = outMin->x = ( in->x <= BfmeZeroRange ) ? BfmeZeroRange : in->x;
	outMin->y = ( in->y <= BfmeZeroRange ) ? BfmeZeroRange : in->y;

	float fW = (float)rtW;

	if ( x + offset->x > fW )
		outMax->x = fW - x;
	else
		outMax->x = offset->x;

	if ( offset->y + outMin->y > fW )
		outMax->y = fW - outMin->y;
	else
		outMax->y = offset->y;
}
