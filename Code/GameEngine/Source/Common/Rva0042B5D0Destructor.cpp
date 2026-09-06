// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??1ArrowStormUpdate (0x00257940, ArrowStormUpdateDestructorThunk.cpp);
// single-vtable destructor that calls a helper first, then destructs three
// members in reverse declaration order: a pinned-dtor object at +0x18, an
// AsciiString at +0xc, and a pinned-dtor object at +4.

void j_00048efa();

class Rva0042B5D0MemberA
{
public:
	~Rva0042B5D0MemberA();
private:
	unsigned char m_pad[8];
};

class Rva0042B5D0Str
{
public:
	~Rva0042B5D0Str();
private:
	void *m_data;
};

class Rva0042B5D0MemberC
{
public:
	~Rva0042B5D0MemberC();
private:
	unsigned char m_pad[4];
};

class Rva0042B5D0
{
public:
	virtual ~Rva0042B5D0();

private:
	Rva0042B5D0MemberA m_a;    // +0x4
	Rva0042B5D0Str m_str;      // +0xc
	unsigned char m_pad2[0x18 - 0x10];
	Rva0042B5D0MemberC m_c;    // +0x18
};

// ?d_0042b5d0@@YAXXZ
Rva0042B5D0::~Rva0042B5D0()
{
	j_00048efa();
}
