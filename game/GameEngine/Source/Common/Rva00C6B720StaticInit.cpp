// cl: /O2 /MD
extern void j_0001f5d2(void);
extern void bfmeForward_00C70000(void);

class Rva00C6B720Init
{
public:
	Rva00C6B720Init()
	{
		char allocator;
		typedef void *(Rva00C6B720Init::*Member)(int);
		union { void (*function)(void); Member method; } call;
		call.function = (void (*)(void))j_0001f5d2;
		(this->*call.method)((int)&allocator);
		atexit(bfmeForward_00C70000);
	}
};

Rva00C6B720Init g_rva012F1598;
