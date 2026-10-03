// ?rva00895950@Rva00893030Manager@@QAE?AVRefHandle008958D0@@PAVBfmeStrVKI@@@Z
// partial score=0.4049 date=2026-10-03
// Parent of cleanup C570B8; return and local lifetimes proved by E46550 unwind map.
// Scratch only: destructor binding and pointer reload shape remain unresolved.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern void (__cdecl *TheBfmeFree)(void *storage, unsigned int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA();
	void operator delete(void *storage, unsigned int bytes)
	{
		TheBfmeFree(storage, bytes);
	}
	int m_refCount;
	void *m_string;
	int m_kind;
	int m_rva00895950_tail[3];
};

class BfmeStrVKI
{
public:
	void *m_data;
};

class RefHandle008958D0
{
public:
    RefHandle008958D0(BfmeDropObjectA *p) : m_object(p) { if(p) ++p->m_refCount; }
    RefHandle008958D0(const RefHandle008958D0& o) : m_object(o.m_object) { if(m_object) ++m_object->m_refCount; }
    ~RefHandle008958D0() { BfmeDropObjectA *p = m_object; if (p && --p->m_refCount == 0) delete p; }
    BfmeDropObjectA *m_object;
};
class Rva00893030Node
{
public:
	BfmeDropObjectA *m_object;
	Rva00893030Node *m_next;
};

class Rva00893030Manager
{
public:
	RefHandle008958D0 find008958D0(BfmeStrVKI *key);
	RefHandle008958D0 rva00895950(BfmeStrVKI *key);
private:
	Rva00893030Node *m_head;
};

RefHandle008958D0 Rva00893030Manager::rva00895950(BfmeStrVKI *key)
{
    RefHandle008958D0 found = find008958D0(key);
    BfmeDropObjectA *value = found.m_object;
    if (value && (value->m_kind == 4 || value->m_kind == 5))
        return found;
    return RefHandle008958D0(0);
}
