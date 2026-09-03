// ?bfmeStep1211C@BfmeG1211@@QAEXXZ
// partial score=0.88 date=2026-09-02
// Open-BFME: BfmeG1211::bfmeStep1211C, retail 0x008A30C0.
// Drain the Apt value stack: pop each entry, and either clear the high-ref
// flag or invoke vslot +8.

class BfmeVal1211
{
public:
	virtual void addRef();
	virtual void release();
	virtual void recycle();

	unsigned m_flags;
};

class BfmeG1211
{
public:
	void bfmeStep1211C();

	int m_unused;
	int m_count;
	BfmeVal1211 **m_stack;
};

void BfmeG1211::bfmeStep1211C()
{
	BfmeG1211 *self = this;
	int n;
	if (self->m_count == 0)
		return;
	n = self->m_count;
	for (;;)
	{
		do
		{
			BfmeVal1211 *v = self->m_stack[--self->m_count];
			unsigned flags = v->m_flags;
			if ((flags & 0x0FFF0000) > 0)
				v->m_flags = flags & 0xBFFFFFFF;
			else
				v->recycle();
		} while (--n);
		if (self->m_count == 0)
			return;
		n = self->m_count;
	}
}
