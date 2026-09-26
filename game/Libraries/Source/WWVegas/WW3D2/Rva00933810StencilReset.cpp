// cl: /DNDEBUG /MD /EHsc
// Retail 0x00933810, 62 bytes. The duplicated stores keep the flags from
// Has_Stencil live through the branch; MSVC then merges the common stores
// while leaving the conditional float zero as an immediate.

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
float g_bfmeStencilDepthRef;

void Rva00933810StencilStateA(void)
{
	if (DX8Wrapper::Has_Stencil())
	{
		g_bfmeThirdEB = 7;
		g_bfmeFourthEB = 2;
		g_bfmeFifthEB = 5;
		g_bfmeSecondEB = 0;
		g_bfmeFirstEB = 0;
	}
	else
	{
		g_bfmeThirdEB = 7;
		g_bfmeFourthEB = 2;
		g_bfmeFifthEB = 5;
		g_bfmeStencilDepthRef = 0.0f;
		g_bfmeSecondEB = 0;
		g_bfmeFirstEB = 0;
	}
}
