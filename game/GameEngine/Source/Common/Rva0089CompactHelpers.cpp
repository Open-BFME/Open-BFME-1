// cl: /DNDEBUG /MD /O2

struct Rva008923E0Index
{
    int m_position;
    int m_unused;
    int *m_items;
    int at(int offset) const;
};
int Rva008923E0Index::at(int offset) const { return m_items[m_position - offset - 1]; }

struct Rva00892900Index
{
    int m_position;
    int m_unused;
    int *m_items;
    int at(int offset) const;
};
int Rva00892900Index::at(int offset) const { return m_items[m_position - offset - 1]; }

bool Rva00892620NotEqual(const int *value, int other)
{
    return *value != other;
}

bool Rva00894F60Equal(const int *value, int other)
{
    return *value == other;
}

struct Rva00894CD0Triple
{
    char m_unknown[12];
    int m_first;
    int m_second;
    int m_third;
    void set(int first, int second, int third);
};
void Rva00894CD0Triple::set(int first, int second, int third)
{
    m_first = first;
    m_second = second;
    m_third = third;
}

struct Rva00894E60Ref
{
    int *m_pointer;
    Rva00894E60Ref(int *pointer);
};
Rva00894E60Ref::Rva00894E60Ref(int *pointer) : m_pointer(pointer)
{
    if (pointer) ++*pointer;
}

struct Rva00894E80Ref
{
    int *m_pointer;
    Rva00894E80Ref(const Rva00894E80Ref &other);
};
Rva00894E80Ref::Rva00894E80Ref(const Rva00894E80Ref &other) : m_pointer(other.m_pointer)
{
    if (m_pointer) ++*m_pointer;
}

struct Rva00894F00Pair
{
    int m_pointer;
    int m_extra;
    Rva00894F00Pair(const int *pointer, int extra);
};
Rva00894F00Pair::Rva00894F00Pair(const int *pointer, int extra) : m_pointer(*pointer), m_extra(extra) {}

struct Rva00894F80Handle
{
    int m_unused;
    unsigned short *m_pointer;
    int m_state;
    int m_field0c;
    int m_field10;
    int m_field14;
    Rva00894F80Handle(unsigned short **pointer);
};
Rva00894F80Handle::Rva00894F80Handle(unsigned short **pointer)
{
    m_unused = 0;
    m_pointer = *pointer;
    ++*m_pointer;
    m_state = 1;
    m_field0c = 0;
    m_field10 = 0;
    m_field14 = 0;
}

struct Rva00896360Handle
{
    int *m_pointer;
    int m_extra;
    Rva00896360Handle(const Rva00896360Handle &other, int extra);
};
Rva00896360Handle::Rva00896360Handle(const Rva00896360Handle &other, int extra)
{
    m_pointer = other.m_pointer;
    if (m_pointer) {
        ++*m_pointer;
        m_extra = extra;
        return;
    }
    m_extra = extra;
}

struct Rva00899270Index
{
    int m_position;
    int m_unused;
    int *m_items;
    int at(int offset) const;
};
int Rva00899270Index::at(int offset) const { return m_items[m_position - offset - 1]; }

struct Rva0089C640Item
{
    int m_unused;
    unsigned int m_flags;
};
struct Rva0089C640List
{
    int m_unused;
    Rva0089C640Item *m_items;
    unsigned int flag(int index) const;
};
unsigned int Rva0089C640List::flag(int index) const { return m_items[index].m_flags & 1; }

struct Rva0089C660List
{
    int m_unused;
    Rva0089C640Item *m_items;
    unsigned int withoutFlag(int index) const;
};
unsigned int Rva0089C660List::withoutFlag(int index) const { return m_items[index].m_flags & ~1u; }

struct Rva0089DBF0Fields
{
    unsigned short m_field00;
    unsigned short m_field02;
    unsigned short m_field04;
};
struct Rva0089DBF0View
{
    Rva0089DBF0Fields *m_data;
    void setField02(unsigned short value);
    unsigned int getField04() const;
    void setField04(unsigned short value);
    unsigned int getField00() const;
};
void Rva0089DBF0View::setField02(unsigned short value) { m_data->m_field02 = value; }
unsigned int Rva0089DBF0View::getField04() const { return m_data->m_field04; }
void Rva0089DBF0View::setField04(unsigned short value) { m_data->m_field04 = value; }
unsigned int Rva0089DBF0View::getField00() const { return m_data->m_field00; }

struct Rva0089DC40StringData
{
    unsigned short m_refs;
};
extern Rva0089DC40StringData g_bfmeDefaultString1284;
struct Rva0089DC40String
{
    Rva0089DC40StringData *m_data;
    Rva0089DC40String(int unused);
};
Rva0089DC40String::Rva0089DC40String(int)
{
    m_data = &g_bfmeDefaultString1284;
    ++g_bfmeDefaultString1284.m_refs;
}

struct Rva00892850Handle
{
    unsigned short m_refs;
};
class Rva00892850Owner
{
public:
    Rva00892850Handle *m_handle;
    void *m_extra;
    Rva00892850Owner *attach( Rva00892850Handle **src, void *extra );
};
// ?attach@Rva00892850Owner@@QAEPAV1@PAPAURva00892850Handle@@PAX@Z
Rva00892850Owner *Rva00892850Owner::attach( Rva00892850Handle **src, void *extra )
{
    Rva00892850Handle *incoming = *src;
    m_handle = incoming;
    ++incoming->m_refs;
    m_extra = extra;
    return this;
}

struct Rva0088D960Inner
{
	int m_value;
};
class Rva0088D960Owner
{
public:
	Rva0088D960Owner *set( Rva0088D960Inner *src );

private:
	char m_pad[0x9F44];
	int m_copy;
};
// ?set@Rva0088D960Owner@@QAEPAV1@PAURva0088D960Inner@@@Z
Rva0088D960Owner *Rva0088D960Owner::set( Rva0088D960Inner *src )
{
	m_copy = src->m_value;
	return this;
}

struct Rva0088D990Inner
{
	unsigned char m_value;
};
class Rva0088D990Owner
{
public:
	Rva0088D990Owner *set( Rva0088D990Inner *src );

private:
	char m_pad[0x9F48];
	unsigned char m_copy;
};
// ?set@Rva0088D990Owner@@QAEPAV1@PAURva0088D990Inner@@@Z
Rva0088D990Owner *Rva0088D990Owner::set( Rva0088D990Inner *src )
{
	m_copy = src->m_value;
	return this;
}
