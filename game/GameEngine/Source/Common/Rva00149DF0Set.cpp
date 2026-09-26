// cl: /O2 /Ob0

struct Rva00149DF0Obj
{
	char pad[0x10];
	int m_refs;
};

class Rva00149DF0
{
	Rva00149DF0Obj *m_ptr;

public:
	Rva00149DF0 &set(Rva00149DF0Obj *const *src);
};

Rva00149DF0 &Rva00149DF0::set(Rva00149DF0Obj *const *src)
{
	Rva00149DF0Obj *ptr = *src;
	m_ptr = ptr;
	++ptr->m_refs;
	return *this;
}
