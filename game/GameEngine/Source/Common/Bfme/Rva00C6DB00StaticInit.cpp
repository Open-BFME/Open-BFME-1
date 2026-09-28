// cl: /O2 /MD
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
		bfmeInit1030(0x0107301C, (int *)&allocator);
	}
	~Rva00C6DB00Init();
};

Rva00C6DB00Init g_rva0130C0C8;
