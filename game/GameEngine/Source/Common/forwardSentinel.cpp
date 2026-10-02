// Clean reconstruction of the generated wrapper at retail RVA 0x007EA300.

class Rva007EA0A0Inner
{
public:
	virtual void v0();
	virtual void v1();
	virtual void slot2(int a, void *arg);
};

class Rva007EA0A0Nested
{
public:
	char m_pad[0x6A8];
	Rva007EA0A0Inner *m_inner;
};

class Rva007EA0A0Slot
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void slot5();
};

class Rva007EA0A0Owner
{
public:
	void notify(void *arg);

private:
	char m_pad[0x250];
	Rva007EA0A0Slot *m_250;
	Rva007EA0A0Nested *m_254;
	char m_pad258[0x10];
	Rva007EA0A0Slot *m_268;
	Rva007EA0A0Nested *m_26C;
	char m_pad270[0x14];
	Rva007EA0A0Slot *m_284;
	Rva007EA0A0Nested *m_288;
};

void forwardSentinel()
{
	int value = -204;
	union CallRoute
	{
		void (Rva007EA0A0Owner::*member)(void *);
		void (__stdcall *helper)(int *);
	};
	CallRoute route = { &Rva007EA0A0Owner::notify };
	route.helper(&value);
}
