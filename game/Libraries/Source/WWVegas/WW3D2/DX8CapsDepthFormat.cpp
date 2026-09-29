// cl: /DNDEBUG /MD /EHsc
// Retail 0x0091B6A0 (58 B incl. its jump table): true for the Direct3D
// depth/stencil formats D16_LOCKABLE(70), D32(71), D15S1(73), D24S8(75),
// D24X8(77), D24X4S4(79), D16(80), D32F_LOCKABLE(82) and D24FS8(83). It sits
// between the matched DX8Caps::Is_Valid_Display_Format and Init_Caps and has
// no references, so the name keeps the address.

class DX8Caps
{
public:
	bool rva0091B6A0(int d3dFormat);
};

bool DX8Caps::rva0091B6A0(int d3dFormat)
{
	switch (d3dFormat)
	{
	case 70:
	case 71:
	case 73:
	case 75:
	case 77:
	case 79:
	case 80:
	case 82:
	case 83:
		return true;
	}
	return false;
}
