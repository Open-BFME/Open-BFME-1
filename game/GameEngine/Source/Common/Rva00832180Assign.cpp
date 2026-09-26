// cl: /O2 /Ob0

struct Rva00832180Unk
{
	virtual void slot0();
	virtual void addRef();
	virtual void release();
};

class Rva00832180
{
	Rva00832180Unk *m_ptr;

public:
	Rva00832180 &set(Rva00832180Unk *const *src);
};

Rva00832180 &Rva00832180::set(Rva00832180Unk *const *src)
{
	if (m_ptr != *src)
	{
		m_ptr->release();
		Rva00832180Unk *p = *src;
		p->addRef();
		m_ptr = p;
	}
	return *this;
}
