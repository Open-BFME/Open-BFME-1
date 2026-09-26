// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" void *bfmeVft008B0170[];

struct Rva00891B80Block
{
	unsigned short m_ref;
};

class Rva008AD2C0
{
public:
	Rva008AD2C0(const Rva008AD2C0 &src);
	~Rva008AD2C0();
	void assign(const Rva008AD2C0 &src);

private:
	Rva00891B80Block *m_block;
	int m_f4;
	int m_f8;
	int m_fC;
	int m_f10;
	int m_f14;
	int m_f18;
	int m_f1C;
};

class Rva899F00Base
{
public:
	Rva899F00Base(const char *id, int kind);
	~Rva899F00Base();

private:
	char m_pad[0x20];
};

class Rva008B0170 : public Rva899F00Base
{
public:
	Rva008B0170(const Rva008AD2C0 &src);

private:
	Rva008AD2C0 m_str;
};

Rva008B0170::Rva008B0170(const Rva008AD2C0 &src) :
	Rva899F00Base(reinterpret_cast<const char *>(0x24), 8),
	m_str(src)
{
	*reinterpret_cast<void **>(this) = bfmeVft008B0170;
	m_str.assign(src);
}
