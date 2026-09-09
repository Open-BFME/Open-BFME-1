// Open-BFME5: clean C++ for the four refcounted module pointers at 0x005F3910.
// partial score=0.78 date=2026-09-09
// The function clears each pointer after dropping its count and calls virtual
// slot zero when the count reaches zero. The four concrete module owners remain
// unidentified, so this source uses the retail global addresses directly.
// cl: /DNDEBUG /MD /EHsc

class Rva005F3910Ref
{
public:
	virtual void release(void);
	int m_refCount;
};

__forceinline void *loadRva005F3910First(void)
{
	return *(void **)0x012F6DC8;
}

void rva005F3910Cleanup(void)
{
	void *first = loadRva005F3910First();
	if (first != 0)
	{
		volatile int *slot = (int *)((char *)first + 4);
		int count = *slot;
		--count;
		*slot = count;
		if (count == 0)
			((Rva005F3910Ref *)first)->release();
		*(void **)0x012F6DC8 = 0;
	}

	Rva005F3910Ref *second = *(Rva005F3910Ref **)0x012F6DCC;
	if (second != 0)
	{
		volatile int *slot = &second->m_refCount;
		int count = *slot;
		--count;
		*slot = count;
		if (count == 0)
			second->release();
		*(Rva005F3910Ref **)0x012F6DCC = 0;
	}

	Rva005F3910Ref *third = *(Rva005F3910Ref **)0x012F6DD0;
	if (third != 0)
	{
		volatile int *slot = &third->m_refCount;
		int count = *slot;
		--count;
		*slot = count;
		if (count == 0)
			third->release();
		*(Rva005F3910Ref **)0x012F6DD0 = 0;
	}

	Rva005F3910Ref *fourth = *(Rva005F3910Ref **)0x012F6DD4;
	if (fourth != 0)
	{
		volatile int *slot = &fourth->m_refCount;
		int count = *slot;
		--count;
		*slot = count;
		if (count == 0)
			fourth->release();
		*(Rva005F3910Ref **)0x012F6DD4 = 0;
	}
}
