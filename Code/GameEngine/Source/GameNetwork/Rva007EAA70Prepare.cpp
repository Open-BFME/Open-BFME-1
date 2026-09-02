// cl: /O2
// 0x007EAA70 / 0x007EAB40: lazy-init the FESL service pair at +0x268/+0x284.

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

class Rva007EAServiceList
{
public:
	void add(Rva00803080 *owner);
};

class Rva007FBB20Object;
class Rva007FCF80Object;

BfmeThingUNB *bfmeNewUNB(void);
void *Gen007F0130(unsigned int size);
unsigned Rva007FBC00(void);
unsigned Rva007FD060(void);
Rva007FBB20Object *Rva007FBB20(void *payload);
Rva007FCF80Object *Rva007FCF80(void *payload);

inline void *operator new(unsigned int, void *p)
{
	return p;
}

class Rva007EAA70Owner
{
public:
	void prepare();

private:
	char m_pad00[4];
	void *m_04;
	char m_pad08[0x260];
	BfmeThingUNB *m_268;
	Rva007F9B80 *m_26C;
	char m_pad270[0x10];
	void *m_280;
};

class Rva007EAB40Owner
{
public:
	void prepare();

private:
	char m_pad00[4];
	void *m_04;
	char m_pad08[0x27C];
	BfmeThingUNB *m_284;
	Rva007F9B80 *m_288;
	char m_pad28C[0x10];
	void *m_29C;
};

void Rva007EAA70Owner::prepare()
{
	if (m_280)
		return;
	m_268 = bfmeNewUNB();
	Rva007F9B80 *p = (Rva007F9B80 *)Gen007F0130(0x6B8);
	if (p)
		p = new (p) Rva007F9B80(this);
	else
		p = 0;
	m_26C = p;
	void *adj = p;
	if (adj)
		adj = (char *)adj + 4;
	else
		adj = 0;
	m_268->attach(adj);
	m_26C->setPeer(m_268);
	m_26C->m_24 = Rva007FBC00();
	void *svc = m_26C;
	if (svc)
		svc = (char *)svc + 8;
	else
		svc = 0;
	((Rva007EAServiceList *)this)->add((Rva00803080 *)svc);
	m_280 = Rva007FBB20(m_04);
}

void Rva007EAB40Owner::prepare()
{
	if (m_29C)
		return;
	m_284 = bfmeNewUNB();
	Rva007F9B80 *p = (Rva007F9B80 *)Gen007F0130(0x6B8);
	if (p)
		p = new (p) Rva007F9B80(this);
	else
		p = 0;
	m_288 = p;
	void *adj = p;
	if (adj)
		adj = (char *)adj + 4;
	else
		adj = 0;
	m_284->attach(adj);
	m_288->setPeer(m_284);
	m_288->m_24 = Rva007FD060();
	void *svc = m_288;
	if (svc)
		svc = (char *)svc + 8;
	else
		svc = 0;
	((Rva007EAServiceList *)this)->add((Rva00803080 *)svc);
	m_29C = Rva007FCF80(m_04);
}
