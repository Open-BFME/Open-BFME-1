// Open-BFME5 conversions.

class BfmeE1037;

// Matched callee rows (callees.py, via ILT): operator new,
// T1Derived_005E9540 ctor, rva002323B0FindBannerCarrierUpdate,
// BannerCarrierUpdate::rva00284810, Rva000AF960Object::addFlags/removeFlags.
class Object;
class Module;
class BannerCarrierObjectName;
class BannerCarrierUpdate
{
public:
	void rva00284810(BannerCarrierObjectName *name, bool flag);
};

class T1Derived_005E9540
{
public:
	T1Derived_005E9540(void *o);
	char m_bfmeBody[0x90];
};
class BfmeD1037;
inline void *operator new(unsigned int, void *where) { return where; }

class BfmeE1037
{
public:
	BfmeD1037 *bfmeGo1037E(void);
};

BfmeD1037 *BfmeE1037::bfmeGo1037E(void)
{
	void *p = operator new(0x90);

	if (p != 0)
		return (BfmeD1037 *)new (p) T1Derived_005E9540(this);

	return 0;
}

Module * __stdcall rva002323B0FindBannerCarrierUpdate(const Object *obj);
#define bfmeDo1037(b, c) rva00284810(b, c)
#define bfmeFind1037F(a) rva002323B0FindBannerCarrierUpdate(a)

void __stdcall bfmeGo1037F(int a, int b, int c)
{
	BannerCarrierUpdate *g = (BannerCarrierUpdate *)bfmeFind1037F((const Object *)a);

	if (g != 0)
		g->bfmeDo1037((BannerCarrierObjectName *)b, *(bool *)&c);
}

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void report(const char *message);
};

extern "C" __declspec(dllimport) int __stdcall WaitForSingleObject(void *h, int t);
Rva007EB810Diag *Rva007EB810Get(void);

class BfmeH1037
{
public:
	void bfmeGo1037H(void);

	char m_bfmePad[4];
	void *m_bfmeHandle;
};

void BfmeH1037::bfmeGo1037H(void)
{
	if (WaitForSingleObject(m_bfmeHandle, -1) != 0)
		Rva007EB810Get()->report("Error entering critical section\n");
}

class Rva000AF960Object
{
public:
	void addFlags(unsigned int n);
	void removeFlags(unsigned int n);
};

class BfmeI1037
{
public:
	void bfmeGo1037I(char f);

	char m_bfmePad[0x98];
	int m_bfmeFlags;
};

void BfmeI1037::bfmeGo1037I(char f)
{
	m_bfmeFlags |= 2;

	if (f != 0)
		((Rva000AF960Object *)this)->addFlags(1);
	else
		((Rva000AF960Object *)this)->removeFlags(1);
}
