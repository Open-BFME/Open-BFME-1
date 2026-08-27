// Open-BFME5: copy the current value into a source object, advance by the
// source's virtual result, reconstructed from retail RVA 0x0048E390.

class Rva0048E390Inner
{
public:
	virtual unsigned int v0();
	virtual unsigned int v1();
	virtual unsigned int v2();
	virtual unsigned int v3();
	virtual unsigned int value();
};

class Rva0048E390Source
{
public:
	Rva0048E390Inner *m_inner;
	char m_padding[4];
	void *m_value;
};

class Rva0048E390Object
{
public:
	void advance( Rva0048E390Source *source );

	char *m_current;
};

void Rva0048E390Object::advance( Rva0048E390Source *source )
{
	source->m_value = m_current;
	m_current += source->m_inner->value();
}
