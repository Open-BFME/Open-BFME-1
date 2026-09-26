// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// The carved four-byte body reads one pointer at offset +0x30.  The owner
// remains unknown, so the accessor keeps the retail address in its name.

class Rva006915A0Owner
{
public:
	__declspec(noinline) void *get()
	{
		return m_value;
	}

private:
	unsigned char m_beforeValue[ 0x30 ];
	void *m_value;
};

typedef void *(Rva006915A0Owner::*Rva006915A0Getter)();
Rva006915A0Getter g_rva006915A0Getter = &Rva006915A0Owner::get;

class Rva006915C0Owner
{
public:
	void *get()
	{
		return m_value;
	}

private:
	unsigned char m_beforeValue[ 0x3C ];
	void *m_value;
};

typedef void *(Rva006915C0Owner::*Rva006915C0Getter)();
Rva006915C0Getter g_rva006915C0Getter = &Rva006915C0Owner::get;
