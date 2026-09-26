// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva002DF100
{
public:
	unsigned char test(void *a, void *b);
};

class Rva002DE220 : public Rva002DF100
{
public:
	unsigned char test(void *a, void *b);
};

unsigned char Rva002DE220::test(void *a, void *b)
{
	return Rva002DF100::test(a, b) != 0;
}
