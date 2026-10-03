// cl: /O2 /Ob0

class Rva002EED00
{
};

extern void j_0003d069();

typedef void (Rva002EED00::*Rva002EED00SetCall)(int);

union Rva002EED00SetTarget
{
	void (*function)();
	Rva002EED00SetCall method;
};

Rva002EED00 *g_rva002eed00;

void rva002eed00()
{
	Rva002EED00SetTarget call;
	call.function = j_0003d069;
	(g_rva002eed00->*call.method)(1);
}
