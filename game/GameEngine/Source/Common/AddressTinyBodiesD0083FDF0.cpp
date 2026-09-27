// cl: /DNDEBUG /MD /EHsc
// Address-derived owners for small complete bodies formerly carried by the
// gen_asm dump d_0083fdf0.asm. No caller, vtable slot or string names any of
// them, so each keeps its retail address in the name; the members describe
// only what the bytes read and write.

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

// 0x008F8E60: mov eax,ecx / ret
class Rva008F8E60Body
{
public:
	Rva008F8E60Body *body();
};

// ?body@Rva008F8E60Body@@QAEPAV1@XZ
Rva008F8E60Body *Rva008F8E60Body::body()
{
	return this;
}

// 0x008FD4B0: mov al,1 / ret
// ?Rva008FD4B0True@@YA_NXZ
bool Rva008FD4B0True()
{
	return true;
}

// 0x008AB800: return the dword at +0x50
class Rva008AB800Body
{
public:
	int body() const;

private:
	char m_pad[0x50];
	int m_value50;
};

// ?body@Rva008AB800Body@@QBEHXZ
int Rva008AB800Body::body() const
{
	return m_value50;
}

// 0x00891AB0: zero-extend the word at +2 of the object this points to
struct Rva00891AB0Data
{
	unsigned short m_word0;
	unsigned short m_word2;
};

class Rva00891AB0Body
{
public:
	int body() const;

private:
	Rva00891AB0Data *m_data;
};

// ?body@Rva00891AB0Body@@QBEHXZ
int Rva00891AB0Body::body() const
{
	return m_data->m_word2;
}

// 0x008B84A0 / 0x008B84B0: split a tagged dword of the array at +0x20
class Rva008B84A0Body
{
public:
	unsigned int lowBit(int index) const;
	unsigned int upperBits(int index) const;

private:
	char m_pad[0x20];
	unsigned int *m_words;
};

// ?lowBit@Rva008B84A0Body@@QBEIH@Z
unsigned int Rva008B84A0Body::lowBit(int index) const
{
	return m_words[index] & 1;
}

// ?upperBits@Rva008B84A0Body@@QBEIH@Z
unsigned int Rva008B84A0Body::upperBits(int index) const
{
	return m_words[index] & ~1u;
}

// 0x008C4510: test bit n of the signed word at +0xA
class Rva008C4510Body
{
public:
	int body(int bit) const;

private:
	char m_pad[0xA];
	short m_bits;
};

// ?body@Rva008C4510Body@@QBEHH@Z
int Rva008C4510Body::body(int bit) const
{
	return m_bits & (1 << bit);
}

// 0x008AB7E0: set bit 16 of the dword at +0x60 from a flag
class Rva008AB7E0Body
{
public:
	void body(int enable);

private:
	char m_pad[0x60];
	unsigned int m_low16 : 16;
	unsigned int m_flag16 : 1;
};

// ?body@Rva008AB7E0Body@@QAEXH@Z
void Rva008AB7E0Body::body(int enable)
{
	m_flag16 = enable != 0;
}

// 0x008C44F0: set bit 9 of the dword at +0x1C from a flag
class Rva008C44F0Body
{
public:
	void body(int enable);

private:
	char m_pad[0x1C];
	unsigned int m_low9 : 9;
	unsigned int m_flag9 : 1;
};

// ?body@Rva008C44F0Body@@QAEXH@Z
void Rva008C44F0Body::body(int enable)
{
	m_flag9 = enable != 0;
}

// 0x008F8E40: four-dword constructor; the second slot takes the last argument
class Rva008F8E40Quad
{
public:
	Rva008F8E40Quad(int a, int b, int c, int d);

private:
	int m_a;
	int m_d;
	int m_b;
	int m_c;
};

// ??0Rva008F8E40Quad@@QAE@HHHH@Z
Rva008F8E40Quad::Rva008F8E40Quad(int a, int b, int c, int d)
	: m_a(a), m_d(d), m_b(b), m_c(c)
{
}

// 0x008BD010: forward to the allocator pointer at 0x01337828
// ?Rva008BD010Alloc@@YAPAXI@Z
void *Rva008BD010Alloc(unsigned int size)
{
	return Rva008C5D70Alloc(size);
}
