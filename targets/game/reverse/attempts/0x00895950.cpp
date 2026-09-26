// ?d_00895950@@YAXXZ
// partial score=0.35 date=2026-09-24
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
};

class BfmeStrVKI
{
public:
	void *m_data;
};

class RefHandle008958D0
{
public:
	BfmeDropObjectA *m_object;
};

class Rva00895950RefGuard
{
public:
	Rva00895950RefGuard() : m_object(0) {}
	~Rva00895950RefGuard()
	{
		if (m_object && --m_object->m_refCount == 0)
			delete m_object;
	}
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
	Rva00895950RefGuard guard;
	RefHandle008958D0 found = find008958D0(key);
	guard.m_object = found.m_object;
	RefHandle008958D0 output;
	output.m_object = 0;
	if (guard.m_object &&
		(guard.m_object->m_kind == 4 || guard.m_object->m_kind == 5))
	{
		output.m_object = guard.m_object;
		++guard.m_object->m_refCount;
	}
	return output;
}
