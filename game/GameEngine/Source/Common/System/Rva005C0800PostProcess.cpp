// The 36-byte body at 0x005C0800 is a one-pointer forward walk whose
// interface dispatch is the second vtable slot.  Its owning class is not
// proven by the carved boundary, so the source keeps the address-derived
// identity instead of borrowing SubsystemInterfaceList's name.
// cl: /DNDEBUG /MD /EHsc

class Rva005C0800Interface
{
public:
	virtual void slot00() = 0;
	virtual void process() = 0;
};

class Rva005C0800
{
public:
	void method();

private:
	Rva005C0800Interface **m_begin;
	Rva005C0800Interface **m_end;
};

void Rva005C0800::method()
{
	for (Rva005C0800Interface **it = m_begin; it != m_end; ++it)
	{
		(*it)->process();
	}
}
