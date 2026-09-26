// cl: /O2

struct Rva0078B280Color
{
	Rva0078B280Color() : m_red(0.0f), m_green(0.0f), m_blue(0.0f) {}
	float m_red;
	float m_green;
	float m_blue;
};

void __cdecl bfmeClear0078B280(
	int clearColor,
	int clearDepth,
	int clearStencil,
	const Rva0078B280Color &color,
	int depth,
	int stencil,
	int rectangleCount);

class Rva0078B280Renderer
{
public:
	void bfmeAdvanceStencil(void);
	bool bfmeHasStencil(void);

	char m_pad00[0xc];
	int m_stencilGeneration;
};

// @?bfmeAdvanceStencil@Rva0078B280Renderer@@QAEXXZ 0x0078B280
void Rva0078B280Renderer::bfmeAdvanceStencil(void)
{
	if (bfmeHasStencil()) {
		++m_stencilGeneration;
		if (m_stencilGeneration > 255)
			m_stencilGeneration = 1;
		if (m_stencilGeneration != 1)
			return;

		bfmeClear0078B280(0, 0, 1, Rva0078B280Color(), 0, 0, 0);
	} else {
		bfmeClear0078B280(0, 1, 1, Rva0078B280Color(), 0, 0, 0);
	}
}
