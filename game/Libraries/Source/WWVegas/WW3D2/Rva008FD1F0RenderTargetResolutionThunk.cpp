// cl: /O2 /DNDEBUG /MD /EHsc
// Retail RVA 0x008FD1F0 tail-jumps to DX8Wrapper::Get_Render_Target_Resolution.

class DX8Wrapper
{
	friend class WW3D;
protected:
	static void Get_Render_Target_Resolution(int &width, int &height,
		int &bit_depth, bool &windowed);
};

class WW3D
{
public:
	static void Get_Render_Target_Resolution(int &width, int &height, int &bit_depth, bool &windowed);
};

void WW3D::Get_Render_Target_Resolution(
	int &width, int &height, int &bit_depth, bool &windowed)
{
	DX8Wrapper::Get_Render_Target_Resolution(width, height, bit_depth, windowed);
}
