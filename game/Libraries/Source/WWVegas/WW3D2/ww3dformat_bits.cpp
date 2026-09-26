// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep
//
// Get_Bits_Per_Pixel -- retail 0x0090C400, 180 bytes including its two jump
// tables. The first function of BFME's texture pipeline to land, and it settles
// the question that makes the rest of that pipeline look "drifted":
//
//   BFME's WW3DFormat is D3DFORMAT.
//
// Zero Hour's WW3DFormat is a dense enum numbered from zero, with its own
// UNKNOWN..DXT5 ordering, and every format switch in WW3D2 is written against
// it. Retail's switch here compares against 20 through 30, 40, 41, 50 through
// 52 and the four-character codes 'DXT1' through 'DXT5' -- which are D3DFMT_
// values exactly. So BFME dropped the abstraction and passes Direct3D's own
// enumeration around. That is why locate.py places none of texture.cpp or
// textureloader.cpp: every format switch in them is built on the wrong numbers,
// so no body can byte-match however faithfully it was ported.
//
// Zero Hour's nearest equivalent is Get_Bytes_Per_Pixel, which cannot express
// DXT1 -- half a byte per pixel -- so BFME moved to bits.
//
// The enum is declared here rather than taken from ww3dformat.h because that
// header still carries the Zero Hour numbering, and changing it would rewrite
// every format constant in every file that already matches against it. This
// translation unit needs only the retail values.
//
// The argument arrives in ecx with nothing pushed and no stack adjustment at
// the call site (0x0090C5CC reaches it as mov ecx,[esi+0x3c]; call), so it is
// __fastcall.
enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN		= 0,

	// D3DFMT_R8G8B8 through D3DFMT_X4R4G4B4, contiguous, which is what lets
	// MSVC reach them through one index table.
	WW3D_FORMAT_R8G8B8		= 20,
	WW3D_FORMAT_A8R8G8B8	= 21,
	WW3D_FORMAT_X8R8G8B8	= 22,
	WW3D_FORMAT_R5G6B5		= 23,
	WW3D_FORMAT_X1R5G5B5	= 24,
	WW3D_FORMAT_A1R5G5B5	= 25,
	WW3D_FORMAT_A4R4G4B4	= 26,
	WW3D_FORMAT_R3G3B2		= 27,
	WW3D_FORMAT_A8			= 28,
	WW3D_FORMAT_A8R3G3B2	= 29,
	WW3D_FORMAT_X4R4G4B4	= 30,

	WW3D_FORMAT_A8P8		= 40,
	WW3D_FORMAT_P8			= 41,
	WW3D_FORMAT_L8			= 50,
	WW3D_FORMAT_A8L8		= 51,
	WW3D_FORMAT_A4L4		= 52,

	WW3D_FORMAT_DXT1		= 0x31545844,	// 'DXT1'
	WW3D_FORMAT_DXT2		= 0x32545844,
	WW3D_FORMAT_DXT3		= 0x33545844,
	WW3D_FORMAT_DXT4		= 0x34545844,
	WW3D_FORMAT_DXT5		= 0x35545844,
};

// ?Get_Bits_Per_Pixel@@YIIW4WW3DFormat@@@Z
unsigned __fastcall Get_Bits_Per_Pixel( WW3DFormat format )
{
	// Zeroed up front rather than returned from a default arm: that is what puts
	// retail's xor eax,eax ahead of the range checks and lets the unmatched
	// formats fall straight through to the shared ret.
	unsigned bits = 0;

	switch( format )
	{
		case WW3D_FORMAT_A8R8G8B8:
		case WW3D_FORMAT_X8R8G8B8:
			bits = 32;
			break;

		case WW3D_FORMAT_R8G8B8:
			bits = 24;
			break;

		case WW3D_FORMAT_R5G6B5:
		case WW3D_FORMAT_X1R5G5B5:
		case WW3D_FORMAT_A1R5G5B5:
		case WW3D_FORMAT_A4R4G4B4:
		case WW3D_FORMAT_A8R3G3B2:
		case WW3D_FORMAT_X4R4G4B4:
		case WW3D_FORMAT_A8P8:
		case WW3D_FORMAT_A8L8:
			bits = 16;
			break;

		case WW3D_FORMAT_R3G3B2:
		case WW3D_FORMAT_A8:
		case WW3D_FORMAT_P8:
		case WW3D_FORMAT_L8:
		case WW3D_FORMAT_A4L4:
		case WW3D_FORMAT_DXT2:
		case WW3D_FORMAT_DXT3:
		case WW3D_FORMAT_DXT4:
		case WW3D_FORMAT_DXT5:
			bits = 8;
			break;

		// The one format that is not a whole number of bytes, and the reason
		// this returns bits where Zero Hour returned bytes.
		case WW3D_FORMAT_DXT1:
			bits = 4;
			break;

		default:
			break;
	}

	return bits;
}
