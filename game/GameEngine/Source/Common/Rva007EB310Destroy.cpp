// cl: /O2
// 0x007EB310: scalar-deleting wrapper around the 0x007EB270 singleton
// teardown. Stores the object vptr, then optionally operator-delete this.

class T_007ea120
{
public:
	virtual void release(int);
	void m();
};

class Rva007EB310Owner
{
public:
	void *destroy(unsigned int flags);
};

extern T_007ea120 *g_Va0130A588;
extern unsigned char g_Va0130A58D;
extern unsigned char g_Va0130A58C;
extern int vftable_01129CB4;

void Rva007EB830Release(void);
void Rva007F0060();
void __cdecl operator delete(void *block);

void *Rva007EB310Owner::destroy(unsigned int flags)
{
	*(int *)this = (int)&vftable_01129CB4;
	T_007ea120 *p = g_Va0130A588;
	if (p)
	{
		p->m();
		p = g_Va0130A588;
		if (p)
			p->release(1);
		g_Va0130A588 = 0;
	}
	if (g_Va0130A58D)
		Rva007EB830Release();
	if (g_Va0130A58C)
		Rva007F0060();
	if (flags & 1)
		operator delete(this);
	return this;
}
