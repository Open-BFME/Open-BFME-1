// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva002DF120
{
public:
	unsigned char test(void *a, void *b);
};

class Rva002DF4C0 : public Rva002DF120
{
public:
	unsigned char test(void *a, void *b);
};

unsigned char Rva002DF4C0::test(void *a, void *b)
{
	return Rva002DF120::test(a, b) != 0;
}
