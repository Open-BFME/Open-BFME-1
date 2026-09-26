// cl: /O2 /Ob0

struct Rva00832150Unk
{
	virtual void slot0();
	virtual void addRef();
};

class Rva00832150
{
	Rva00832150Unk *m_ptr;

public:
	Rva00832150(Rva00832150Unk *const *src);
	~Rva00832150();
};

Rva00832150::Rva00832150(Rva00832150Unk *const *src)
{
	m_ptr = 0;
	Rva00832150Unk *p = *src;
	p->addRef();
	m_ptr = p;
}

class Rva0083FE90Owner
{
	char m_pad[0x1c];
	Rva00832150Unk *m_ptr;

public:
	Rva00832150 make();
};

Rva00832150 Rva0083FE90Owner::make()
{
	return Rva00832150(&m_ptr);
}
