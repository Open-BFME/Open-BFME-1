// ?invoke@Rva0020DF90Part@@QAEXPAX@Z
// partial score=0.89 date=2026-09-02
// cl: /O2
// Open-BFME: 38-byte back-step virtual then subobject call at retail 0x0020DF90.
// Virtual slot 0x38 on the object at this-0x10, then a three-arg thiscall on
// the subobject at this+0xC8 with (arg, [this-8], 1). Size matches; residue is
// register permutation on the two stack-arg loads (eax/ecx vs ecx/edx).

class Rva0020DF90Head
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
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
};

class Rva0020DF90Sub
{
public:
	void apply(void *arg, void *member, int flag);
};

class Rva0020DF90Part
{
public:
	void invoke(void *arg);

	char m_pad[0xC8];
	Rva0020DF90Sub m_sub;
};

void Rva0020DF90Part::invoke(void *arg)
{
	Rva0020DF90Head *head = (Rva0020DF90Head *)((char *)this - 0x10);
	head->v14();
	void *member = *(void **)((char *)this - 8);
	void *a = arg;
	m_sub.apply(a, member, 1);
}
