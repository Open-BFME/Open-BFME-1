// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// The carved four-byte body reads a pointer from offset +0x4.  No owner is
// proven by the callers or neighboring boundaries, so the name stays opaque.

class Rva003AC440Owner
{
public:
	virtual void ownerAnchor();

	__declspec(noinline) void *get()
	{
		return m_value;
	}

private:
	void *m_value;
};

typedef void *(Rva003AC440Owner::*Rva003AC440Getter)();
Rva003AC440Getter g_rva003AC440Getter = &Rva003AC440Owner::get;
