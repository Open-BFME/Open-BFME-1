// cl: /EHs-c-
// Opaque one-pointer cleanup body at retail 0x00784A70.  The caller sets ECX
// to this object, and the retail body rereads the pointer for the drop after
// the refcount decrement call.

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

__declspec(noinline) void bfmeDropA(void *value);

class Rva00784A70Cleanup
{
public:
	void bfmeCleanup(void);

private:
	void *m_bfmeItem;
};

// ?bfmeCleanup@Rva00784A70Cleanup@@QAEXXZ
void Rva00784A70Cleanup::bfmeCleanup(void)
{
	if (m_bfmeItem)
	{
		if (Rva00894D90Accessor::decrement((unsigned int *)m_bfmeItem) == 0)
			bfmeDropA(m_bfmeItem);
	}
}
