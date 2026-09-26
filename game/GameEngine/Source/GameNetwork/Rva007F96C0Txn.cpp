// cl: /GS
// 0x007F96C0: transactor.cpp TXN dispatch. Hub vslot 4 yields a handler
// object; a miss logs the TXN string and fail()s. A hit looks the key up
// and fires the record callback with a +0x14 refcount around the call.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void log(int level, const char *format, ...);
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva007E8810Message
{
public:
	bool getString(const char *key, char *buf, int size);
};

struct Rva007F96C0Rec
{
	char m_00;
	char m_pad[3];
	void *m_04;
	void *m_08;
	void *m_0C;
	void (__cdecl *fn)(Rva007E8810Message *msg, void *ctx);
	void *ctx;
};

class Rva007F96C0Obj
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *v2(Rva007E8810Message *msg);
};

class Rva007F96C0Hub
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual Rva007F96C0Obj *v4(void *a, Rva007E8810Message *msg);
};

class Rva007FA2C0
{
public:
	bool onTxn(Rva007E8810Message *msg);
	Rva007F96C0Rec *lookup(void *key);

private:
	char m_pad[0x14];
	int m_14;
	char m_pad18[8];
	void *m_20;
	Rva007F96C0Hub *m_24;
};

bool Rva007FA2C0::onTxn(Rva007E8810Message *msg)
{
	Rva007F96C0Obj *obj = m_24->v4(m_20, msg);
	if (!obj)
	{
		char txn[0x20] = {0};
		msg->getString("TXN", txn, 0x20);
		Rva007EB810Get()->log(0, "Received serviceless TXN: %s\n", txn);
		Rva007EB810Get()->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\transactor.cpp",
			0x109);
		return false;
	}
	Rva007F96C0Rec *rec = lookup(obj->v2(msg));
	if (!rec)
		return false;
	++m_14;
	rec->fn(msg, rec->ctx);
	--m_14;
	return true;
}
