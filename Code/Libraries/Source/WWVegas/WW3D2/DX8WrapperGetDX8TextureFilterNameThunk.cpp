// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to semantic C++.

class DX8Wrapper
{
public:
	static const char *Get_DX8_Texture_Filter_Name(unsigned value);
};

const char *DX8Wrapper::Get_DX8_Texture_Filter_Name(unsigned value)
{
	switch (value) {
		case 1: return "D3DSTENCILOP_KEEP";
		case 2: return "D3DSTENCILOP_ZERO";
		case 3: return "D3DSTENCILOP_REPLACE";
		case 4: return "D3DSTENCILOP_INCRSAT";
		case 5: return "D3DSTENCILOP_DECRSAT";
		case 6: return "D3DSTENCILOP_INVERT";
		case 7: return "D3DSTENCILOP_INCR";
		case 8: return "D3DSTENCILOP_DECR";
		default: return "UNKNOWN";
	}
}
