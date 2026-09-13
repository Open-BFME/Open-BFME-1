// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva001A2D50Node
{
public:
	virtual ~Rva001A2D50Node();
};

extern Rva001A2D50Node *g_rva012EF4D0;

void rva001A2D50Clear(void)
{
	while (g_rva012EF4D0)
		delete g_rva012EF4D0;
}
