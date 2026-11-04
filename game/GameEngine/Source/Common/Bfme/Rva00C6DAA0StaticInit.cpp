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

// 0x0130C0B0 is recorded (DIR32) as ?TheBfmeObject_00C70E10@@3VGen_00C70E10Target@@A,
// the name its consumers bind; define the storage under that symbol.
// Retire ?g_rva0130C0B0@@3VRva00C6DAA0Init@@A
extern "C" { Rva00C6DAA0Init __identifier("?TheBfmeObject_00C70E10@@3VGen_00C70E10Target@@A"); }
