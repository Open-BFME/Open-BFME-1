// cl: /O2 /MD
extern void j_000203ce(void);
extern const unsigned short g_Rva01088AF4EmptyWideString[];

class Rva00C6DB30Init
{
public:
	Rva00C6DB30Init()
	{
		char allocator;
		typedef void *(Rva00C6DB30Init::*Member)(const unsigned short *, void *);
		union { void (*function)(void); Member method; } call;
		call.function = (void (*)(void))j_000203ce;
		(this->*call.method)(g_Rva01088AF4EmptyWideString, &allocator);
	}
	~Rva00C6DB30Init();
};

// 0x0130C0BC is recorded (DIR32) as ?TheBfmeObject_00C70E40@@3VGen_00C70E40Target@@A,
// the name its consumers bind; define the storage under that symbol.
// Retire ?g_rva0130C0BC@@3VRva00C6DB30Init@@A
extern "C" { Rva00C6DB30Init __identifier("?TheBfmeObject_00C70E40@@3VGen_00C70E40Target@@A"); }
