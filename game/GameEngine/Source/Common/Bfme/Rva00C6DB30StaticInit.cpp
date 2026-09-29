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

Rva00C6DB30Init g_rva0130C0BC;
