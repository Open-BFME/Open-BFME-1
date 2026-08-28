// ?d_005c3140@@YAXXZ
// partial score=0.8 date=2026-08-27
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB
// Open-BFME5: retail 0x005C3140 (21 bytes), optional callback then success.

class Rva005C3140Callback
{
public:
	virtual void spare000(void) = 0;
	virtual void spare001(void) = 0;
	virtual void spare002(void) = 0;
	virtual void spare003(void) = 0;
	virtual void spare004(void) = 0;
	virtual void spare005(void) = 0;
	virtual void spare006(void) = 0;
	virtual void spare007(void) = 0;
	virtual void spare008(void) = 0;
	virtual void spare009(void) = 0;
	virtual int notify(void) = 0;
};

class Rva005C3140Base
{
protected:
	unsigned char m_beforeCallback[0x94];
	Rva005C3140Callback *m_callback;
};

class Rva005C3140 : public Rva005C3140Base
{
public:
	int call(void);
};

int Rva005C3140::call(void)
{
	if (m_callback != 0)
		return m_callback->notify();

	return 1;
}
