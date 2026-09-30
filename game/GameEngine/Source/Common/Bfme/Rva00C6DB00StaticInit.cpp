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

Rva00C6DB00Init g_rva0130C0C8;
