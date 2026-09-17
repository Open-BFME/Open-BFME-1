// ?sweep@Rva008A0E70Owner@@QAEXXZ
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008A0E70 walks a fixed 64-entry pointer table that starts at +4 and
// notifies every occupied entry through virtual slot 1, stopping early once it
// has seen the live count held at +0.  The owner has no named retail caller --
// its only two call sites are inside the same anonymous dump -- so the class
// keeps its address-derived name.
//
// The table entry must be read through the member array on BOTH the null test
// and the call.  Binding it to a local first (or to a slot pointer, a
// reference, a void * or a helper) lets MSVC load the entry straight into ecx
// and drops retail's `mov ecx, eax`, leaving the body two bytes short.

class Rva008A0E70Entry
{
public:
	virtual void slot0();
	virtual void notify();
};

class Rva008A0E70Owner
{
public:
	void sweep();

private:
	int m_liveCount;
	Rva008A0E70Entry *m_entries[0x40];
};

void Rva008A0E70Owner::sweep()
{
	int remaining = m_liveCount;
	int index = 0;

	for (; index < 0x40; ++index)
	{
		if (m_entries[index])
		{
			m_entries[index]->notify();

			if (--remaining == 0)
				break;
		}
	}
}
