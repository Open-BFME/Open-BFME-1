
class BfmeTargetF5F
{
public:
	void call(void *obj);
};

class BfmeTargetF63
{
public:
	void call2(void *obj);
};

class BfmeMgrF5F
{
public:
	unsigned char pad[0x3c];
	unsigned int m_frame3C;
	void* find(int id, void *b, int zero);
	void* find2(int id, void *b1, void *b2, int zero);
};

extern BfmeMgrF5F *g_bfmeMgr12F0898;

struct BfmeArgF5F
{
	unsigned char pad[8];
	int m_id;
};

struct BfmeThingF5F
{
	unsigned char pad[0x58];
	BfmeTargetF5F *m_sub58;
	void doDispatch(BfmeArgF5F *a, void *b);
};

void BfmeThingF5F::doDispatch(BfmeArgF5F *a, void *b)
{
	BfmeTargetF5F *target = m_sub58;
	if (target) {
		void *obj = g_bfmeMgr12F0898->find(a->m_id, b, 0);
		target->call(obj);
	}
}

struct BfmeThingF63
{
	unsigned char pad[0x58];
	BfmeTargetF63 *m_sub58;
	void doDispatch2(BfmeArgF5F *a, void *b);
};

void BfmeThingF63::doDispatch2(BfmeArgF5F *a, void *b)
{
	BfmeTargetF63 *target = m_sub58;
	if (target) {
		void *obj = g_bfmeMgr12F0898->find2(a->m_id, b, b, 0);
		target->call2(obj);
	}
}

void __cdecl bfmeHelper990410(void *arg, double val);

int __cdecl bfmeAction2A4(void *arg)
{
	bfmeHelper990410(arg, (double)g_bfmeMgr12F0898->m_frame3C);
	return 1;
}

extern "C" const float bfmeConst1075350;

struct BfmeSub78_2B1
{
	unsigned char pad[0x10];
	float f10;
};

struct BfmeObj2B1
{
	unsigned char pad[0x78];
	BfmeSub78_2B1 *m_sub78;
};

extern BfmeObj2B1 *g_obj12F060C;

int __cdecl bfmeAction2B1(void *arg)
{
	float val = bfmeConst1075350;
	if (g_obj12F060C->m_sub78)
		val = g_obj12F060C->m_sub78->f10;
	bfmeHelper990410(arg, (double)val);
	return 1;
}

double __cdecl bfmeRandom2B7(int a, float b, const char *file, int line);
extern const char bfmeString10CF498[];

int __cdecl bfmeAction2B7(void *arg)
{
	double val = bfmeRandom2B7(0, 1.0f, bfmeString10CF498, 0x973);
	bfmeHelper990410(arg, val);
	return 1;
}
