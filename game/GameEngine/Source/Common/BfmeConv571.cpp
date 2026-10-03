class BfmeThingCBF
{
public:
	void *bfmeGoCBF(unsigned int flags);
	void *m_bfmePtr;
};

void __cdecl operator delete[](void *what);
void __cdecl operator delete(void *what);

void *BfmeThingCBF::bfmeGoCBF(unsigned int flags)
{
	operator delete[](m_bfmePtr);
	if (flags & 1)
		operator delete(this);
	return this;
}
