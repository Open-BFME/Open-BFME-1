// cl: /GX-
// Rva00802380Owner ctor: vtable, field8=0, three-dword member at +0x18, then field4/24/28.

struct V2ZeroInt
{
	__forceinline V2ZeroInt() : m_value(0) {}
	int m_value;
};

class Rva00800630Owner
{
public:
	Rva00800630Owner();

	void *m_block;
	int m_field4;
	int m_field8;
};

class Rva00802380Owner
{
public:
	__declspec(noinline) Rva00802380Owner();
	virtual ~Rva00802380Owner();

	int m_field4;
	V2ZeroInt m_field8;
	char m_pad00C[0x0C];
	Rva00800630Owner m_owner;
	int m_field24;
	int m_field28;
};

Rva00802380Owner::Rva00802380Owner()
{
	m_field4 = 0;
	m_field24 = 0;
	m_field28 = 0;
}
