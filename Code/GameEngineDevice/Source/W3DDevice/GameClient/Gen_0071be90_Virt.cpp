// cl: /DNDEBUG /MD /EHsc

// Retail 0x0071BE90. Sibling of 0x00716500: stdcall vtable slot 0x1AC.

struct Gen_0071be90_Obj;

struct Gen_0071be90_Vtbl
{
	void *m_gap[0x1AC / 4];
	void (__stdcall *call)(Gen_0071be90_Obj *self, void *p);
};

struct Gen_0071be90_Obj
{
	Gen_0071be90_Vtbl *vtbl;
};

Gen_0071be90_Obj *g_0071be90_obj;
int g_0071be90_count;

// ?run_0071be90@@YAXPAX@Z
void run_0071be90(void *p)
{
	g_0071be90_obj->vtbl->call(g_0071be90_obj, p);
	++g_0071be90_count;
}
