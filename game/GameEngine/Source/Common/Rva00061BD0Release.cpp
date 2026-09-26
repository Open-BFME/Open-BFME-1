// cl: /O2 /Ob0

extern "C" void __cdecl gameTextRelease(void *);

class Rva00061BD0
{
	void *m_ptr;

public:
	void release();
};

void Rva00061BD0::release()
{
	void *ptr = m_ptr;
	gameTextRelease(ptr);
}
