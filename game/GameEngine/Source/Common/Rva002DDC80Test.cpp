// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva002DF120
{
public:
	unsigned char test(void *a, void *b);
};

class Rva002DDC80 : public Rva002DF120
{
public:
	unsigned char test(void *a, void *b);
};

unsigned char Rva002DDC80::test(void *a, void *b)
{
	return Rva002DF120::test(a, b) != 0;
}
