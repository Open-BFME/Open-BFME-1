// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// The carved four-byte body reads a pointer from offset +0x4.  The nearby
// functions do not prove its owner, so the accessor keeps the retail address.

class Rva002D93A0Owner
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

typedef void *(Rva002D93A0Owner::*Rva002D93A0Getter)();
Rva002D93A0Getter g_rva002D93A0Getter = &Rva002D93A0Owner::get;
