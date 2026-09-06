// ?Rva00933810StencilStateA@@YAXXZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: three shadow-stencil render-state setters from dump
// d_00930e00.asm (0x00933810 62 B, 0x00933B80 102 B, 0x00933BF0 103 B), the
// family whose global reset lives at 0x009336B0. Each asks
// DX8Wrapper::Has_Stencil, then writes the five shader words
// (g_bfmeFirstEB..g_bfmeFifthEB) and the depth reference. The depth
// reference (VA 0x01346DD8) is a FLOAT: retail stores it as an immediate
// (0.0f / 1.0f / 0.5f) while the two integer zeroes share one register
// materialised after the branch. Typing it as an int made MSVC hoist a
// shared zero above the Has_Stencil test (cmp al,cl instead of test al,al),
// which is what the earlier 0.8-0.88 attempts hit.
class DX8Wrapper
{
public:
	static bool Has_Stencil(void);
};

extern int g_bfmeFirstEB;
extern int g_bfmeSecondEB;
extern int g_bfmeThirdEB;
extern int g_bfmeFourthEB;
extern int g_bfmeFifthEB;
extern float g_bfmeStencilDepthRef;
extern int g_bfmeStencilBlendSrcEB;
extern int g_bfmeStencilBlendDstEB;

void Rva00933810StencilStateA(void)
{
	bool has_stencil = DX8Wrapper::Has_Stencil();
	g_bfmeFifthEB = 5;
	g_bfmeFourthEB = 2;
	g_bfmeThirdEB = 7;
	if (!has_stencil)
		g_bfmeStencilDepthRef = 0.0f;
	g_bfmeSecondEB = 0;
	g_bfmeFirstEB = 0;
}

void Rva00933B80StencilStateB(void)
{
	bool has_stencil = DX8Wrapper::Has_Stencil();
	g_bfmeThirdEB = 7;
	if (has_stencil)
	{
		g_bfmeFirstEB = 0;
		g_bfmeFourthEB = 0;
		g_bfmeSecondEB = 2;
		g_bfmeFifthEB = 1;
		g_bfmeStencilBlendSrcEB = g_bfmeStencilBlendDstEB;
	}
	else
	{
		g_bfmeSecondEB = 0;
		g_bfmeFirstEB = 1;
		g_bfmeFourthEB = 0;
		g_bfmeFifthEB = 1;
		g_bfmeStencilDepthRef = 1.0f;
	}
}

void Rva00933BF0StencilStateC(void)
{
	bool has_stencil = DX8Wrapper::Has_Stencil();
	g_bfmeFifthEB = 5;
	g_bfmeFourthEB = 2;
	if (has_stencil)
	{
		g_bfmeSecondEB = 1;
		g_bfmeFirstEB = 0;
		g_bfmeThirdEB = 7;
		g_bfmeStencilBlendSrcEB = g_bfmeStencilBlendDstEB;
	}
	else
	{
		g_bfmeStencilDepthRef = 0.5f;
		g_bfmeSecondEB = 0;
		g_bfmeFirstEB = 0;
		g_bfmeThirdEB = 3;
	}
}
