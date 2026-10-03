// cl: /O2
// 0x007EA9C0: start NetConn if needed, then lazy-init the FESL service pair
// at +0x250 the same way 0x007EAA70 does for +0x268.

class BfmeThingUNB
{
public:
	virtual void v0();
	virtual void attach(void *inner);
};

class Rva007F9B80
{
public:
	Rva007F9B80(void *owner) throw();
	void setPeer(void *peer);
	char m_pad[0x24];
	unsigned m_24;
};

class Rva00803080;

// 0x007F0130 is the class-scoped allocating operator retail calls with the
// 0x6B8 byte size here; its defining name is the operator of this class.
class Gen007F0130
{
public:
	static void *operator new(unsigned int size);
};

// 0x007F9590 is a matched body under this class name; the object it is called
// on is the Rva007F9B80 allocated just above.
class Gen_007f9590
{
public:
	void m(int a);
};

class Rva007EAServiceList
{
public:
	void add(Rva00803080 *owner);
};

class BfmeThingDGG;

BfmeThingUNB *bfmeNewUNB(void);
// 0x007F8FB0 is retail's free cdecl body (it never reads ECX, and the call
// site reloads this+0x254 only after it), so it stays spelled as a free
// function here; the gen-shim that defines that address as a member is the
// side that is wrong.
unsigned Rva007F8FB0(void);
BfmeThingDGG *bfmeGoDGG(void *a);
int Rva007EB380Startup(char *params);

inline void *operator new(unsigned int, void *p)
{
	return p;
}

class Rva007EA9C0Owner
{
public:
	void init();

private:
	char m_pad00[4];
	void *m_04;
	unsigned char m_08;
	char m_pad09[3];
	void *m_0C;
	char m_pad10[0x240];
	BfmeThingUNB *m_250;
	Rva007F9B80 *m_254;
};

void Rva007EA9C0Owner::init()
{
	if ((m_08 & 1) == 0)
		Rva007EB380Startup(0);
	m_0C = bfmeGoDGG(this);
	m_250 = bfmeNewUNB();
	Rva007F9B80 *p = (Rva007F9B80 *)Gen007F0130::operator new(0x6B8);
	if (p)
		p = new (p) Rva007F9B80(this);
	else
		p = 0;
	m_254 = p;
	void *adj = p;
	if (adj)
		adj = (char *)adj + 4;
	else
		adj = 0;
	m_250->attach(adj);
	((Gen_007f9590 *)m_254)->m((int)m_250);
	m_254->m_24 = Rva007F8FB0();
	void *svc = m_254;
	if (svc)
		svc = (char *)svc + 8;
	else
		svc = 0;
	((Rva007EAServiceList *)this)->add((Rva00803080 *)svc);
}
