// cl: /O2 /MD
extern const char g_Rva0107301CEmptyString[];

class BfmeSub1030
{
public:
	void bfmeInit1030(int text, int *allocator);
};

class Rva00C6DAD0Init : public BfmeSub1030
{
public:
	Rva00C6DAD0Init()
	{
		char allocator;
		bfmeInit1030((int)g_Rva0107301CEmptyString, (int *)&allocator);
	}
	~Rva00C6DAD0Init();
};

// 0x0130C074 is recorded (DIR32) as ?TheBfmeObject_00C70E20@@3VGen_00C70E20Target@@A.
// Retire ?g_rva0130C074@@3VRva00C6DAD0Init@@A: define the storage under that symbol.
extern "C" { Rva00C6DAD0Init __identifier("?TheBfmeObject_00C70E20@@3VGen_00C70E20Target@@A"); }
