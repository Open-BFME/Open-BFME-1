// ?d_00933b80@@YAXXZ
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Two Has_Stencil blend-mode setters that write the Render2D global
// shader-constant block.

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

// ?d_00933b80@@YAXXZ
void d_00933b80(void)
{
	bool has_stencil = DX8Wrapper::Has_Stencil();
	g_bfmeThirdEB = 7;
	if (has_stencil)
	{
		int z = 0;
		g_bfmeFirstEB = z;
		g_bfmeFourthEB = z;
		int saved = g_bfmeBlendDst;
		g_bfmeSecondEB = 2;
		g_bfmeFifthEB = 1;
		g_bfmeBlendSrc = saved;
		return;
	}

	int z = 0;
	int one = 1;
	g_bfmeSecondEB = z;
	g_bfmeFirstEB = one;
	g_bfmeFourthEB = z;
	g_bfmeFifthEB = one;
	g_bfmeResetZ = 0x3F800000;
}

// ?d_00933bf0@@YAXXZ
void d_00933bf0(void)
{
	bool has_stencil = DX8Wrapper::Has_Stencil();
	g_bfmeFifthEB = 5;
	g_bfmeFourthEB = 2;
	if (has_stencil)
	{
		int saved = g_bfmeBlendDst;
		g_bfmeSecondEB = 1;
		g_bfmeFirstEB = 0;
		g_bfmeThirdEB = 7;
		g_bfmeBlendSrc = saved;
		return;
	}

	int z = 0;
	g_bfmeResetZ = 0x3F000000;
	g_bfmeSecondEB = z;
	g_bfmeFirstEB = z;
	g_bfmeThirdEB = 3;
}
