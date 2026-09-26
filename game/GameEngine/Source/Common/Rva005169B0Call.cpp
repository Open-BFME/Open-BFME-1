// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Gen00024B7C
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3C();
	virtual void v40();
	virtual void v44();
	virtual void v48();
};

extern Gen00024B7C *g_Va012F7730;

class Rva005169B0
{
	char m_pad[0x150];
	unsigned int m_val;

public:
	void wrap(int a, int b);
};

void Rva005169B0::wrap(int, int)
{
	if (g_Va012F7730)
	{
		m_val = 11;
		g_Va012F7730->v48();
	}
}
