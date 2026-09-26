// cl: /DNDEBUG /MD /EHsc
// Rva0090C950Texture::rva0090C950 -- retail 0x0090C950, 142 bytes.
// A bump-map format check: level-0 surface via texture vslot 0x48
// (GetSurfaceLevel), its desc via surface vslot 0x30 (GetDesc), then
// Format in 0x3c..0x40 (D3DFMT_V8U8..D3DFMT_V16U16). The only caller,
// BfmeThingVHN::bfmeGoVHN (0x0090E1A0, texture.cpp), logs "is not a bump
// map format" when it returns 0. Class and method stay address-derived.
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

class Rva0090C950Texture
{
public:
	char rva0090C950();

	int m_dword0;
	int m_dword4;
	Rva0090C950Iface *m_dword8;
};

char Rva0090C950Texture::rva0090C950()
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
