// cl: /O2 /Ob0

class Rva002EECE0
{
};

extern void j_0003d069();

typedef void (Rva002EECE0::*Rva002EECE0SetCall)(int);

union Rva002EECE0SetTarget
{
	void (*function)();
	Rva002EECE0SetCall method;
};

Rva002EECE0 *g_rva002eece0;

void rva002eece0()
{
	Rva002EECE0SetTarget call;
	call.function = j_0003d069;
	(g_rva002eece0->*call.method)(0);
}
