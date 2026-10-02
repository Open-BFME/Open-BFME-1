// cl: /O2 /Ob0

void __cdecl operator delete[](void *);

class Rva00065C70
{
	void *m_ptr;

public:
	void release();
};

void Rva00065C70::release()
{
	void *ptr = m_ptr;
	::operator delete[](ptr);
}
