// cl: /O2 /MD
extern const char g_Rva0107301CEmptyString[];

class BfmeSub1030
{
public:
	void bfmeInit1030(int text, int *allocator);
};

class Rva00C6DB00Init : public BfmeSub1030
{
public:
	Rva00C6DB00Init()
	{
		char allocator;
		bfmeInit1030((int)g_Rva0107301CEmptyString, (int *)&allocator);
	}
	~Rva00C6DB00Init();
};

// 0x0130C0C8 is recorded (DIR32) as ?TheBfmeObject_00C70E30@@3VGen_00C70E30Target@@A,
// the name its consumers bind; define the storage under that symbol.
// Retire ?g_rva0130C0C8@@3VRva00C6DB00Init@@A
extern "C" { Rva00C6DB00Init __identifier("?TheBfmeObject_00C70E30@@3VGen_00C70E30Target@@A"); }
