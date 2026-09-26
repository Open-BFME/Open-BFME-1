
extern void *g_activeObj12F0610;
extern const char bfmeString10CF748[];
void __cdecl bfmeLogMsg574(const char *msg);
void __cdecl bfmeNotify1_574(void *obj, void *param);
void __cdecl bfmeNotify2_574(void *obj, void *param);

void __cdecl bfmeHandleDeactivation574(void *obj, void *param)
{
	if (g_activeObj12F0610 == obj) {
		g_activeObj12F0610 = 0;
		bfmeLogMsg574(bfmeString10CF748);
		bfmeNotify1_574(obj, param);
		bfmeNotify2_574(obj, param);
	}
}

extern const char bfmeEmptyStr107388B[];

struct BfmeStrHolder43D
{
	const char *m_raw;
	const char* str() const
	{
		return m_raw ? (const char*)((char*)m_raw + 8) : bfmeEmptyStr107388B;
	}
};

void __cdecl bfmeHelper996070(void *field, void *arg1, void *arg2, const char *name);
void __cdecl bfmeHelper98FDE0(void *field, int zero);

struct BfmeThing43D
{
	unsigned char pad[8];
	void *m_field8;
	void *m_fieldC;
	void doDispatch8(void *arg1, void *arg2, BfmeStrHolder43D *nameHolder);
	void doDispatchC(void *arg1, void *arg2, BfmeStrHolder43D *nameHolder);
};

void BfmeThing43D::doDispatch8(void *arg1, void *arg2, BfmeStrHolder43D *nameHolder)
{
	const char *str = nameHolder->str();
	bfmeHelper996070(m_field8, arg1, arg2, str);
	bfmeHelper98FDE0(m_field8, 0);
}

void BfmeThing43D::doDispatchC(void *arg1, void *arg2, BfmeStrHolder43D *nameHolder)
{
	const char *str = nameHolder->str();
	bfmeHelper996070(m_fieldC, arg1, arg2, str);
	bfmeHelper98FDE0(m_fieldC, 0);
}

extern "C" const float bfmeConst1075350;

class BfmeBaseA97
{
public:
	virtual void v0();
	virtual bool vfn1(void *a, void *b);
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void vfn6(void *a, void *b_sub38);
	unsigned char pad[0x60 - 4];
	float m_f60;
	void handleMatch(void *a, void *b);
	void checkAndDispatch(void *a, void *b);
};

void BfmeBaseA97::checkAndDispatch(void *a, void *b)
{
	if (vfn1(a, b)) {
		handleMatch(a, b);
	}
	if (m_f60 > bfmeConst1075350) {
		vfn6(a, (char*)b + 0x38);
	}
}
