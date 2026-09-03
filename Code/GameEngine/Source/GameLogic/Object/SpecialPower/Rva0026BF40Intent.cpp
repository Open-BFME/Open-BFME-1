// cl: /DNDEBUG /MD

typedef unsigned int UnsignedInt;

class Coord3D;

class Rva0026A620Owner
{
public:
	void apply(const Coord3D *loc, UnsignedInt commandOptions);
};

struct Rva0026BF40String
{
	unsigned short *m_data;
};

struct Rva0026BF40FlagHost
{
	char m_pad[0x210];
	Rva0026BF40String m_name;
};

class Rva0026BF40Primary
{
public:
	void after(const Coord3D *loc);

	char m_pad00[4];
	Rva0026BF40FlagHost *m_flagHost;
	void **m_gate;
	char m_pad0C[4];
};

class Rva0026BF40Owner
{
public:
	void apply(const Coord3D *loc, UnsignedInt commandOptions);
};

static Rva0026BF40Primary *rva0026BF40Primary(Rva0026BF40Owner *self)
{
	return (Rva0026BF40Primary *)((char *)self - 0x10);
}

// ?apply@Rva0026BF40Owner@@QAEXPBVCoord3D@@I@Z
void Rva0026BF40Owner::apply(const Coord3D *loc, UnsignedInt commandOptions)
{
	if (rva0026BF40Primary(this)->m_gate[0x1a4 / 4] != 0)
		return;
	if (loc == 0)
		return;
	Rva0026BF40String *name = &rva0026BF40Primary(this)->m_flagHost->m_name;
	if (name->m_data == 0)
		return;
	if (name->m_data[2] == 0)
		return;
	((Rva0026A620Owner *)this)->apply(loc, commandOptions);
	rva0026BF40Primary(this)->after(loc);
}
