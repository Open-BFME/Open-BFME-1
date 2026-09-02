// cl: /EHsc

class AsciiString
{
public:
	AsciiString(const char *value);
	~AsciiString();

private:
	char *m_data;
};

class Rva00471F80Owned
{
public:
	virtual ~Rva00471F80Owned();
};

class Rva00471F80Base
{
public:
	virtual ~Rva00471F80Base() {}
};

struct Rva00471F80Vec
{
	int x, y, z;
};

class Rva00471F80 : public Rva00471F80Base
{
public:
	Rva00471F80();
	virtual ~Rva00471F80();

private:
	char m_pad[0x18];
	Rva00471F80Owned *m_owned;
	int m_unused;
	AsciiString m_name;
	int m_color;
	int m_count;
	int m_extra;
	Rva00471F80Vec m_first;
	Rva00471F80Vec m_second;
};

// ??0Rva00471F80@@QAE@XZ
Rva00471F80::Rva00471F80() :
	m_owned(0),
	m_unused(0),
	m_name("SachaWynter")
{
	m_color = 0x00DCF0FA;
	m_count = 8;
	m_extra = 0xE;
	m_first.x = 0;
	m_first.y = 0;
	m_first.z = 0;
	m_second.x = 0;
	m_second.y = 0;
	m_second.z = 0;
}

// ??1Rva00471F80@@UAE@XZ
Rva00471F80::~Rva00471F80()
{
	delete m_owned;
	m_owned = 0;
}
