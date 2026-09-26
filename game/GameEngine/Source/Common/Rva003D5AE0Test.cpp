// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva003D5AE0Obj
{
	char m_pad[0xC];
	unsigned m_bits;
};

int __stdcall rva003D5AE0(int, const Rva003D5AE0Obj *obj, int, int)
{
	return (obj->m_bits & 0xFC0u) != 0x40u;
}
