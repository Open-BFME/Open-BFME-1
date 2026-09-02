// ?rva00C6FF70Release@@YAXXZ
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Free function: InterlockedDecrement the global object's refcount at +4 and
// delete it through vtable slot 0 when the count falls to zero or below.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *value);

class Rva00C6FF70Obj
{
public:
	virtual ~Rva00C6FF70Obj(void);

	long m_refCount;
};

extern Rva00C6FF70Obj *g_rva00C6FF70Obj;

void rva00C6FF70Release(void)
{
	Rva00C6FF70Obj *p = g_rva00C6FF70Obj;

	if (p)
	{
		if (InterlockedDecrement(&p->m_refCount) <= 0)
			delete p;
	}
}
