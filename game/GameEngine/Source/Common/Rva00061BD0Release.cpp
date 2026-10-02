// cl: /O2 /Ob0

void __cdecl operator delete[](void *);

class Rva00061BD0
{
	void *m_ptr;

public:
	void release();
};

void Rva00061BD0::release()
{
	void *ptr = m_ptr;
	::operator delete[](ptr);
}
