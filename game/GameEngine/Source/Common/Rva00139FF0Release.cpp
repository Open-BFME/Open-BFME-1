// cl: /O2 /Ob0
// Retail 0x00139FF0 (14 B): load the pointer at this+0, and when non-null
// release it with operator delete[].  Only its ILT 0x0001A5DC refers to it.
// Earlier ledgers called it ~INIException; retail's INIException ThrowInfo
// names 0x00061BD0 as that destructor, so this body keeps an address-derived
// identity.

void __cdecl operator delete[](void *);

class Rva00139FF0
{
	void *m_ptr;

public:
	void release();
};

void Rva00139FF0::release()
{
	void *ptr = m_ptr;
	if (ptr != 0)
		::operator delete[](ptr);
}
