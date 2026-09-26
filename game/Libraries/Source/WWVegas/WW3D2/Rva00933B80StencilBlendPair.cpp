// cl: /DNDEBUG /MD /EHsc
// Two stencil-gated presets for the same five-word shader-constant block
// (0x012D718C-0x012D7194, 0x01346DDC-0x01346DE0) that d_00930e00.asm's third
// sibling at 0x00933810 resets. Each branches on DX8Wrapper::Has_Stencil()
// and writes a different constant set per side; identity beyond that is not
// recovered, so both are address-derived.

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
int g_bfmeBlendSrc;
int g_bfmeBlendDst;

// ?Rva00933B80StencilBlendA@@YAXXZ
void Rva00933B80StencilBlendA(void)
{
	if (DX8Wrapper::Has_Stencil())
	{
		g_bfmeThirdEB = 7;
		int z = 0;
		g_bfmeFirstEB = z;
		g_bfmeFourthEB = z;
		int saved = g_bfmeBlendDst;
		g_bfmeSecondEB = 2;
		g_bfmeFifthEB = 1;
		g_bfmeBlendSrc = saved;
		return;
	}

	g_bfmeThirdEB = 7;
	int z = 0;
	int one = 1;
	g_bfmeSecondEB = z;
	g_bfmeFirstEB = one;
	g_bfmeFourthEB = z;
	g_bfmeFifthEB = one;
	g_bfmeResetZ = 0x3F800000;
}

// ?Rva00933BF0StencilBlendB@@YAXXZ
void Rva00933BF0StencilBlendB(void)
{
	if (DX8Wrapper::Has_Stencil())
	{
		g_bfmeFourthEB = 2;
		g_bfmeFifthEB = 5;
		int saved = g_bfmeBlendDst;
		g_bfmeSecondEB = 1;
		g_bfmeFirstEB = 0;
		g_bfmeThirdEB = 7;
		g_bfmeBlendSrc = saved;
		return;
	}

	g_bfmeFifthEB = 5;
	g_bfmeFourthEB = 2;
	int z = 0;
	g_bfmeResetZ = 0x3F000000;
	g_bfmeSecondEB = z;
	g_bfmeFirstEB = z;
	g_bfmeThirdEB = 3;
}
