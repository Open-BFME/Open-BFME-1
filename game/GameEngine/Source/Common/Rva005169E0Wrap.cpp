// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Gen00024B7C
{
public:
	unsigned char handle(int a);
};

extern Gen00024B7C *g_Va012F7730;

class Rva005169E0
{
public:
	unsigned char wrap(int a);
};

unsigned char Rva005169E0::wrap(int a)
{
	if (g_Va012F7730)
		return g_Va012F7730->handle(a);
	return 0;
}
