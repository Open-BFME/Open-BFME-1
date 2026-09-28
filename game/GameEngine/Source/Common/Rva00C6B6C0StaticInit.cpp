// cl: /O2 /MD
extern void j_00046add(void);

class Rva00C6B6C0Init
{
public:
	Rva00C6B6C0Init()
	{
		char allocator;
		typedef void *(Rva00C6B6C0Init::*Member)(int);
		union { void (*function)(void); Member method; } call;
		call.function = (void (*)(void))j_00046add;
		(this->*call.method)((int)&allocator);
	}
	~Rva00C6B6C0Init();
};

Rva00C6B6C0Init g_rva012F146C;
