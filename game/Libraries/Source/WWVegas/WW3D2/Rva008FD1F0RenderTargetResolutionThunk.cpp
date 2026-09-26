// cl: /O2 /DNDEBUG /MD /EHsc
// Retail RVA 0x008FD1F0 tail-jumps to WW3D::Get_Render_Target_Resolution.

class WW3D
{
public:
	static void Get_Render_Target_Resolution(int &width, int &height,
		int &bit_depth, bool &windowed);
};

class Rva008FD1F0RenderTargetResolutionThunk
{
public:
	static void forward(int &width, int &height, int &bit_depth, bool &windowed);
};

void Rva008FD1F0RenderTargetResolutionThunk::forward(
	int &width, int &height, int &bit_depth, bool &windowed)
{
	WW3D::Get_Render_Target_Resolution(width, height, bit_depth, windowed);
}
