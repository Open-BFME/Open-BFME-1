// cl: /O2
// Open-BFME: 70-byte back-step seeder at retail 0x00202DF0. Zeros three dwords
// on the object at this-0x20, virtual-calls slot 0x28 on the pointer at
// this-0x18, optionally forwards 4 to that result, then a two-arg thiscall on
// this-0x20 with a reloaded this-0x18 pointer and 0x3FFFFFFF.

class Rva00202DF0Face
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void *slot10();
};

class Rva00202DF0Doer
{
public:
	void doit(int value);
};

class Rva00202DF0Head
{
public:
	void apply(Rva00202DF0Face *face, int mask);

	char m_pad[0x24];
	int m_a;
	int m_b;
	int m_c;
};

class Rva00202DF0Part
{
public:
	void seed(int unused);
};

void Rva00202DF0Part::seed(int unused)
{
	Rva00202DF0Head *head = (Rva00202DF0Head *)((char *)this - 0x20);
	Rva00202DF0Face *face = *(Rva00202DF0Face **)((char *)this - 0x18);
	head->m_a = 0;
	head->m_b = 0;
	head->m_c = 0;
	Rva00202DF0Doer *doer = (Rva00202DF0Doer *)face->slot10();
	if (doer)
		doer->doit(4);
	head->apply(*(Rva00202DF0Face **)((char *)this - 0x18), 0x3FFFFFFF);
}
