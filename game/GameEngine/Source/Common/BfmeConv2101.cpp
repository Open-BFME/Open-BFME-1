class Rva00785FD0Renderer
{
public:
	~Rva00785FD0Renderer();
};

extern Rva00785FD0Renderer *g_rva00785FD0Renderer;

void bfmeShutYP()
{
	if (g_rva00785FD0Renderer != 0)
	{
		Rva00785FD0Renderer *r = g_rva00785FD0Renderer;

		delete r;

		g_rva00785FD0Renderer = 0;
	}
}
