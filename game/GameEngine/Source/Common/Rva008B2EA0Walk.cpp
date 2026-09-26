// cl: /O2 /DNDEBUG /MD

extern void *g_rva008B2EA0Fallback;

class Rva008B2EA0Inner
{
public:
	virtual void *s00();
	virtual void *s04();
	virtual void *s08();
	virtual void *s0c();
	virtual void *s10();
	virtual void *s14();
	virtual void *s18();
	virtual void *s1c();
	virtual void *s20();
	virtual void *s24();
	virtual void *s28();
	virtual void *s2c();
	virtual void *s30();
	virtual void *s34();
	virtual void *s38();
	virtual void *s3c();
	virtual void *s40();
	virtual void *s44();
	virtual void *s48();
	virtual void *s4c();
	virtual void *s50();
	virtual void *slot54();
};

class Rva008B2EA0Obj
{
public:
	virtual void unused();
	unsigned m_flags;
	char m_pad08[0x20 - 8];
	Rva008B2EA0Inner *m_20;
};

class Rva008B2EA0Node
{
public:
	void append(void *p);
};

Rva008B2EA0Node *rva008B2EA0Create();
void *g_rva008B2EA0Base;

void *rva008B2EA0Walk(Rva008B2EA0Obj *obj)
{
	Rva008B2EA0Node *node;
	void *extra;

	if ((obj->m_flags & 0x3f) != 0x20)
		return g_rva008B2EA0Fallback;

	node = rva008B2EA0Create();
	node->append((char *)g_rva008B2EA0Base + 8);
	if (obj->m_20)
	{
		extra = obj->m_20->slot54();
		if (extra)
			node->append(extra);
	}
	return node;
}
