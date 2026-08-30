// ?d_00899f00@@YAXXZ
// partial score=0.9 date=2026-08-30
// cl: /DNDEBUG /MD /EHsc

class Rva899F00Base;

struct Rva899F00Registry
{
	int capacity;
	int count;
	Rva899F00Base **items;

	__forceinline void add(Rva899F00Base *item)
	{
		if (count < capacity)
		{
			items[count] = item;
			++count;
		}
	}
};

extern Rva899F00Registry *TheRva899F00Registry;

class Rva899F00RegistrationBase
{
public:
	__forceinline Rva899F00RegistrationBase(const char *id)
	{
		unsigned value = (((m_flags & 0xc0) | reinterpret_cast<unsigned>(id)) &
			0xf000803f) | 0x8000;
		m_flags = value;

		if (id != reinterpret_cast<const char *>(0x1c) &&
			id != reinterpret_cast<const char *>(0x0a))
		{
			value |= 0x40000000;
			m_flags = value;
			TheRva899F00Registry->add(reinterpret_cast<Rva899F00Base *>(this));
		}
		else
		{
			value &= 0xbfffffff;
			m_flags = value;
		}
	}

	virtual ~Rva899F00RegistrationBase();

protected:
	unsigned m_flags;
};

class Rva899F00Node
{
public:
	Rva899F00Node(int kind);

private:
	int m_kind;
	int m_zero0;
	int m_zero1;
	int m_zero2;
};

class Rva899F00Base : public Rva899F00RegistrationBase
{
public:
	Rva899F00Base(const char *id, int kind);
	virtual ~Rva899F00Base();

private:
	Rva899F00Node m_node;
	unsigned m_state;
	unsigned m_bits;
};

Rva899F00Base::Rva899F00Base(const char *id, int kind) :
	Rva899F00RegistrationBase(id),
	m_node(kind)
{
	reinterpret_cast<unsigned char *>(&m_bits)[0] = 0;
	m_bits &= 0xfffffcff;
	m_state = 0;
}
