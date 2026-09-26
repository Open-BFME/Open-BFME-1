// cl: /O2 /Ob0

extern "C" void __cdecl gameTextRelease(void *);

class Rva00065C70
{
	void *m_ptr;

public:
	void release();
};

void Rva00065C70::release()
{
	void *ptr = m_ptr;
	gameTextRelease(ptr);
}
