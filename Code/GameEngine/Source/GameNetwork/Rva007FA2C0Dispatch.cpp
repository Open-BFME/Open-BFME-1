// cl: /O2
// 0x007FA2C0: if the +0x24 object's vslot 9 accepts the first argument,
// dispatch one helper; else if +0x6AC is live, another; else a cdecl triple.

class Rva007FA2C0Hub
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual bool v9(void *a);
};

void Rva007F93E0(void *a, void *b, void *svc);

class Rva007FA2C0
{
public:
	void dispatch(void *a, void *b);
	void onAccept(void *a);
	void onBusy(void *a);

private:
	char m_pad[0x1C];
	void *m_1C;
	char m_pad20[4];
	Rva007FA2C0Hub *m_24;
	char m_pad28[0x684];
	void *m_6AC;
};

void Rva007FA2C0::dispatch(void *a, void *b)
{
	if (m_24->v9(a))
		onAccept(a);
	else if (m_6AC)
		onBusy(a);
	else
		Rva007F93E0(a, b, m_1C);
}
