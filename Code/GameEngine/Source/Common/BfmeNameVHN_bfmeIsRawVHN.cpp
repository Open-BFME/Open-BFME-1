// cl: /DNDEBUG /MD /EHsc
// BfmeNameVHN::bfmeIsRawVHN -- retail 0x0090C950, 142 bytes.
// Caller: BfmeThingVHN::bfmeGoVHN (0x0090E1A0, texture.cpp) names this method.
// The EH-unwound local is a scope lock: unwind funclet 0x00C5B8B0 does
// lea ecx,[ebp-0x34] and jumps via 0x0000BFAF -> 0x0007BCE0 -> 0x00905B10,
// the same unlock the normal path calls after the state=-1 store. The
// interface from vtable slot 0x48 is a raw local released on the success
// path only.
void W3DRadarResetLock(void);
char bfmeUnlock1179(void);

class Rva0090C950Lock
{
public:
	Rva0090C950Lock(void) { W3DRadarResetLock(); }
	~Rva0090C950Lock(void) { bfmeUnlock1179(); }
};

struct Rva0090C950Desc
{
	int m_dword0;
	int m_dword4[7];
};

class Rva0090C950Iface
{
public:
	virtual long __stdcall slot00();
	virtual long __stdcall slot01();
	virtual long __stdcall slot02();
	virtual long __stdcall slot03();
	virtual long __stdcall slot04();
	virtual long __stdcall slot05();
	virtual long __stdcall slot06();
	virtual long __stdcall slot07();
	virtual long __stdcall slot08();
	virtual long __stdcall slot09();
	virtual long __stdcall slot10();
	virtual long __stdcall slot11();
	virtual long __stdcall slot12(Rva0090C950Desc *desc);
	virtual long __stdcall slot13();
	virtual long __stdcall slot14();
	virtual long __stdcall slot15();
	virtual long __stdcall slot16();
	virtual long __stdcall slot17();
	virtual long __stdcall slot18(unsigned int index, Rva0090C950Iface **out);
};

class BfmeNameVHN
{
public:
	char bfmeIsRawVHN();

	int m_dword0;
	int m_dword4;
	Rva0090C950Iface *m_dword8;
};

char BfmeNameVHN::bfmeIsRawVHN()
{
	char ok = 0;

	if (m_dword8 != 0)
	{
		Rva0090C950Lock lock;
		Rva0090C950Iface *iface;
		if (m_dword8->slot18(0, &iface) == 0)
		{
			Rva0090C950Desc desc;
			if (iface->slot12(&desc) == 0 && desc.m_dword0 >= 0x3c && desc.m_dword0 <= 0x40)
				ok = 1;
			iface->slot02();
		}
	}

	return ok;
}
