// ?d_00933810@@YAXXZ
// partial score=0.88 date=2026-09-02
// cl: /DNDEBUG /MD /Os /EHsc
// Render2D-family global reset: Has_Stencil, then the 7/2/5 shader
// constants, a guarded Z store, and the two trailing zeroes.

class DX8Wrapper
{
public:
	static bool Has_Stencil(void);
};

int g_bfmeFirstEB;
int g_bfmeSecondEB;
int g_bfmeThirdEB;
int g_bfmeFourthEB;
int g_bfmeFifthEB;
int g_bfmeResetZ;

// ?d_00933810@@YAXXZ
void d_00933810(void)
{
	bool has_stencil = DX8Wrapper::Has_Stencil();

	g_bfmeFifthEB = 5;
	g_bfmeFourthEB = 2;
	g_bfmeThirdEB = 7;

	if (!has_stencil)
		g_bfmeResetZ = 0;

	int z = 0;
	g_bfmeSecondEB = z;
	g_bfmeFirstEB = z;
}
