// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F8340. Four-argument thiscall: pointer at +0x28, kind word at
// +0x48 from that pointer (or 0), AsciiString constructed at +0x88, then three
// bytes at +0x7C/+0x7D/+0x7E.

class Rva006F8340KindSrc
{
public:
	int getKind(void);
};

class Rva006F8340String
{
public:
	Rva006F8340String(const Rva006F8340String &other);
	~Rva006F8340String();
	void copyFrom(const Rva006F8340String &other);

private:
	void *m_data;
};

class Rva006F8340Obj
{
public:
	void apply(Rva006F8340KindSrc *p, Rva006F8340String name,
		unsigned char a, unsigned char b);

private:
	unsigned char m_pad[0x28];
	Rva006F8340KindSrc *m_28;
	unsigned char m_pad2[0x48 - 0x2C];
	int m_48;
	unsigned char m_pad3[0x7C - 0x4C];
	unsigned char m_7c;
	unsigned char m_7d;
	unsigned char m_7e;
	unsigned char m_pad4[0x88 - 0x7F];
	Rva006F8340String m_88;
};

// ?apply@Rva006F8340Obj@@QAEXPAVRva006F8340KindSrc@@VRva006F8340String@@EE@Z
void Rva006F8340Obj::apply(Rva006F8340KindSrc *p, Rva006F8340String name,
	unsigned char a, unsigned char b)
{
	m_28 = p;
	m_48 = p ? p->getKind() : 0;
	Rva006F8340String *slot = &m_88;
	slot->copyFrom(name);
	m_7c = p != 0;
	m_7d = b;
	m_7e = a;
}
