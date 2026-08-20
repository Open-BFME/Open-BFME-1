// cl: /DNDEBUG /MD /EHsc

// Retail 0x00716500. stdcall vtable slot 0x15C(self, arg), then increment a counter.

struct Gen_00716500_Obj;

struct Gen_00716500_Vtbl
{
	void *m_gap[0x15C / 4];
	void (__stdcall *call)(Gen_00716500_Obj *self, void *p);
};

struct Gen_00716500_Obj
{
	Gen_00716500_Vtbl *vtbl;
};

Gen_00716500_Obj *g_00716500_obj;
int g_00716500_count;

// ?run_00716500@@YAXPAX@Z
void run_00716500(void *p)
{
	g_00716500_obj->vtbl->call(g_00716500_obj, p);
	++g_00716500_count;
}
