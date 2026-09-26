void __cdecl operator delete(void *p);

class BfmeLockVHX
{
public:
	~BfmeLockVHX();
};

extern BfmeLockVHX *g_bfmeLockZS;

void bfmeDropLockZS();

void bfmeDropLockZS()
{
	delete g_bfmeLockZS;
}
