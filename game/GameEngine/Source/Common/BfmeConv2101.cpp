class Rva00785FD0Renderer;

// Retail 0x00783F60 deletes through ILT 0x00039F45 -> 0x0078AFC0, the matched
// ??1Rva0078AFC0Holder@@QAE@XZ (Rva0078AFC0HolderDestructor.cpp).
class Rva0078AFC0Holder
{
public:
	~Rva0078AFC0Holder();
};

extern Rva00785FD0Renderer *g_rva00785FD0Renderer;

void bfmeShutYP()
{
	if (g_rva00785FD0Renderer != 0)
	{
		Rva0078AFC0Holder *r = reinterpret_cast<Rva0078AFC0Holder *>(g_rva00785FD0Renderer);

		delete r;

		g_rva00785FD0Renderer = 0;
	}
}
