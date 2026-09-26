// ??1Rva008A0DC0Owner@@QAE@XZ
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008A0DC0 releases a fixed 512-entry pointer table that starts at +4
// through virtual slot 1, stopping early once it has released the live count
// held at +0.  targets/game/reverse/symbols.csv records the address as a destructor target
// read out of the retail unwind funclet bytes, which is what fixes the shape;
// the owning class itself has no named retail caller, so it keeps its
// address-derived name.
//
// The table entry must be read through the member array on BOTH the null test
// and the virtual call.  Binding it to a local, a slot pointer, a reference or
// a helper lets MSVC load the entry straight into ecx and drops retail's
// `mov ecx, eax`, leaving the body two bytes short.  Same lever as the 64-slot
// sweep at 0x008A0E70.

class Rva008A0DC0Entry
{
public:
	virtual void addRef();
	virtual void release();
};

class Rva008A0DC0Owner
{
public:
	~Rva008A0DC0Owner();

private:
	int m_liveCount;
	Rva008A0DC0Entry *m_entries[512];
};

Rva008A0DC0Owner::~Rva008A0DC0Owner()
{
	int remaining = m_liveCount;
	int index = 0;

	for (; index < 512; ++index)
	{
		if (m_entries[index])
		{
			m_entries[index]->release();

			if (--remaining == 0)
				break;
		}
	}
}
