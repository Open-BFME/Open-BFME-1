// cl: /EHs-c-
//
// APT queued-primitive flush at 0x00785FD0.  Dirty byte 0x01306950, renderer
// 0x01306954 with a __fastcall mode setter (edx = mode) reached via ILT
// 0x0003DDED, stencil helper ILT 0x00041EC0 -> 0x0078B280, queue sentinel
// 0x01306978, element cleanup ILT 0x00049062 -> 0x00785300.

class Rva00785FD0Renderer
{
public:
	void stencil();
	void __fastcall setMode(int mode);
};

class Rva00785FD0Item
{
public:
	void cleanup();
};

struct Rva00785FD0Node
{
	Rva00785FD0Node *next;
	char pad[4];
	Rva00785FD0Item *item;
};

extern char g_rva00785FD0Dirty;
extern Rva00785FD0Renderer *g_rva00785FD0Renderer;
extern Rva00785FD0Node *g_rva00785FD0Queue;

void rva00785FD0Flush()
{
	if (g_rva00785FD0Dirty == 0)
		return;

	if (g_rva00785FD0Queue->next == g_rva00785FD0Queue)
	{
		g_rva00785FD0Renderer->setMode(0);
		return;
	}

	g_rva00785FD0Dirty = 0;
	g_rva00785FD0Renderer->stencil();
	g_rva00785FD0Renderer->setMode(2);
	for (Rva00785FD0Node *n = g_rva00785FD0Queue->next; n != g_rva00785FD0Queue; n = n->next)
		n->item->cleanup();
	g_rva00785FD0Renderer->setMode(1);
}
