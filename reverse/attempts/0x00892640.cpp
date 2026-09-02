// ?Rva00892640CopyItems@@YAPAURva00892640Item@@PAU1@00@Z
// partial score=0.8 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: copy a run of 8-byte refcounted handles. Increments the source
// refcount word, drops the dest (calling the global vtable+4 deleter when
// the count hits zero), then copies both dwords.

struct Rva00892640Handle
{
	unsigned short refs;
};

struct Rva00892640Item
{
	Rva00892640Handle *handle;
	void *extra;
};

struct Rva00892640Deleter
{
	virtual void pad();
	virtual void destroy(Rva00892640Handle *handle);
};

extern Rva00892640Deleter *g_rva00892640Deleter;

// ?Rva00892640CopyItems@@YAPAURva00892640Item@@PAU1@00@Z
Rva00892640Item *Rva00892640CopyItems(Rva00892640Item *first, Rva00892640Item *last, Rva00892640Item *dest)
{
	if (first == last)
		return dest;

	do
	{
		++first->handle->refs;
		Rva00892640Handle *old = dest->handle;
		--old->refs;
		if (old->refs == 0)
			g_rva00892640Deleter->destroy(old);
		dest->handle = first->handle;
		dest->extra = first->extra;
		++first;
		++dest;
	} while (first != last);

	return dest;
}
