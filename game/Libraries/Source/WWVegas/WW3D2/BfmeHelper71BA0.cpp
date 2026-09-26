// cl: /DNDEBUG /MD /O2 /EHs-c-

class RenderObjClass;
RenderObjClass * __cdecl Create_Render_Obj(const char *name);

class BfmeCreatedObj
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void applyAt58(void *what);
	virtual void slot20();
	virtual void applyName(const char *name);

	char m_pad[0x0C];
	int m_bits;
};

class BfmeHelper71BA0
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void attach(BfmeCreatedObj *obj);

	int bfmeCall71BA0();

private:
	char m_pad04[0x20 - 4];
	char m_name[0x28];
	unsigned char m_flags;
	char m_pad49[0x58 - 0x49];
	void *m_at58;
};

int BfmeHelper71BA0::bfmeCall71BA0()
{
	BfmeCreatedObj *obj = (BfmeCreatedObj *)Create_Render_Obj(m_name);
	if (obj)
	{
		attach(obj);
		void *at58 = m_at58;
		obj->applyAt58(at58);
		obj->applyName(m_name);
		if (m_flags & 1)
			obj->m_bits |= 0x100000;
		else
			obj->m_bits &= ~0x100000;
	}
	return (int)obj;
}
