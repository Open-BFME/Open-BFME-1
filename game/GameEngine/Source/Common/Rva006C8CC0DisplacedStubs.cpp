// cl: /O2 /DNDEBUG /MD
// Address-derived bodies whose bytes are RenderObjClass's trivial virtual stubs,
// but whose addresses retail's RenderObjClass vtable does not reference (the
// vtable slots reach the stubs near 0x006CF2D0). No owner is proven for them.

// 0x006F6CB0: mov eax,[esp+4]; mov [ecx+0x84],eax; ret 4
class Rva006F6CB0Owner
{
public:
	void set(int value);

private:
	char m_padding[0x84];
	int m_value;
};

// ?set@Rva006F6CB0Owner@@QAEXH@Z
void Rva006F6CB0Owner::set(int value)
{
	m_value = value;
}

// 0x0045C0D0: fld dword ptr [ecx+0x98]; ret
class Rva0045C0D0Owner
{
public:
	float get() const;

private:
	char m_padding[0x98];
	float m_value;
};

// ?get@Rva0045C0D0Owner@@QBEMXZ
float Rva0045C0D0Owner::get() const
{
	return m_value;
}

// 0x0060D210: mov eax,[esp+4]; mov [ecx+0x8C],eax; ret 4
class Rva0060D210Owner
{
public:
	void set(float value);

private:
	char m_padding[0x8C];
	float m_value;
};

// ?set@Rva0060D210Owner@@QAEXM@Z
void Rva0060D210Owner::set(float value)
{
	m_value = value;
}

// 0x006C8CC0: ret 8
class Rva006C8CC0Owner
{
public:
	void invoke(int, int);
};

// ?invoke@Rva006C8CC0Owner@@QAEXHH@Z
void Rva006C8CC0Owner::invoke(int, int)
{
}
