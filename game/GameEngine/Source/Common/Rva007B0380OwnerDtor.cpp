// cl: /DNDEBUG /MD
// Retail 0x007B0380: delete two owned polymorphic objects before base destruction.

class Rva007B0380Owned
{
public:
	virtual ~Rva007B0380Owned();
};

class Rva007B0380Base
{
public:
	virtual ~Rva007B0380Base();
private:
	char m_padding[0x54];
};

Rva007B0380Base::~Rva007B0380Base()
{
}

class Rva007B0380Owner : public Rva007B0380Base
{
public:
	virtual ~Rva007B0380Owner();
private:
	Rva007B0380Owned *m_first;
	Rva007B0380Owned *m_second;
};

Rva007B0380Owner::~Rva007B0380Owner()
{
	delete m_first;
	delete m_second;
}
