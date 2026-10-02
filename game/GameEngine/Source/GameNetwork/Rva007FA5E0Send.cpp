// cl: /O2
// 0x007FA5E0: FESL send path. Rejects a live valid() on the argument (-103)
// or an id mismatch at +0x6A8 (-105), then drives vslot 0/5 on +0x24 and
// dispatch(arg, "->R").

class Rva007FA5E0Arg
{
public:
	char m_pad[0x20];
	void *m_20;
	char m_gap24[4];
	void *m_28;
	void *m_2C;
};

// 0x007E88A0 is W3DVideoBuffer::valid (m_texture != NULL, the word at +0x24).
// The FESL arg valid() predicate is the linker's ICF fold of that exact body,
// so the call has to carry the defining name to resolve.
class W3DVideoBuffer
{
public:
	virtual bool valid();
};

class Rva007FA5E0Id
{
public:
	virtual void v0();
	virtual void *id();
};

class Rva007FA5E0Hub
{
public:
	virtual void v0(void *a, void *p);
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void *v5(void *a, int z0, int z1);
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual bool v9(void *a);
};

class Rva007FA2C0
{
public:
	void dispatch(void *a, void *b);
	int send(Rva007FA5E0Arg *arg);

private:
	char m_pad[0x1C];
	void *m_1C;
	char m_pad20[4];
	Rva007FA5E0Hub *m_24;
	char m_pad28[0x680];
	Rva007FA5E0Id *m_6A8;
	void *m_6AC;
};

int Rva007FA2C0::send(Rva007FA5E0Arg *arg)
{
	if (((W3DVideoBuffer *)arg)->W3DVideoBuffer::valid())
		return -103;
	void *want = arg->m_2C;
	if (want != m_6A8->id())
		return -105;
	m_24->v0(arg, arg->m_28);
	arg->m_20 = m_24->v5(arg, 0, 0);
	dispatch(arg, "->R");
}
