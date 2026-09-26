// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// The five-way switch at retail 0x006990E0.
//
// The body takes one pointer in EDX and returns an int in EAX, so it is
// modelled as __fastcall with a dead first register argument.  It reads a
// second object out of +0x8, switches on that object's word at +0x84, and
// returns either 1 or 1000000, except in case 0 where a value at +0x68 of
// one or more is returned as it stands and -1 asks for 1000000.  MSVC lays
// the five labels out through a jump table, as retail does.
//
// Four dump bodies call this address and nothing names it, so the function,
// the request and the kind object all keep the retail address.
struct Rva006990E0Kind
{
	unsigned char m_pad0[0x3c];
	unsigned char m_flag;
	unsigned char m_pad3d[0x84 - 0x3d];
	unsigned int m_kind;
};

struct Rva006990E0Request
{
	unsigned char m_pad0[8];
	Rva006990E0Kind *m_kind;
	unsigned char m_pad0c[0x68 - 0xc];
	int m_value;
};

int __fastcall rva006990E0(int unused, Rva006990E0Request *request)
{
	Rva006990E0Kind *kind = request->m_kind;
	if (kind == 0)
		return 1;

	switch (kind->m_kind)
	{
	case 0:
		{
			int value = request->m_value;
			if (value == -1)
				goto full;
			if (value >= 1)
				return value;
			return 1;
		}
	case 1:
	case 4:
		return (kind->m_flag & 1) ? 1000000 : 1;
	case 3:
full:
		return 1000000;
	default:
		return 1;
	}
}
