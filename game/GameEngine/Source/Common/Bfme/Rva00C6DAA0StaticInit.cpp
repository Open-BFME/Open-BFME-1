// cl: /O2 /MD
extern void j_000203ce(void);

class Rva00C6DAA0Init
{
public:
	Rva00C6DAA0Init()
	{
		char allocator;
		typedef void *(Rva00C6DAA0Init::*Member)(const unsigned short *, void *);
		union { void (*function)(void); Member method; } call;
		call.function = (void (*)(void))j_000203ce;
		(this->*call.method)(L"false", &allocator);
	}
	~Rva00C6DAA0Init();
};

Rva00C6DAA0Init g_rva0130C0B0;
