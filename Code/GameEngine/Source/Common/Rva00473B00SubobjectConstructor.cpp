class Rva00473B00Holder
{
private:
	unsigned char m_padding[0x04];

public:
	int m_refCount;
};

class Rva00473B00State
{
public:
	void *m_vtable;
	Rva00473B00Holder *m_holder;
};

void gen00473B00( void *destination, void *source )
{
	if ( destination != 0 )
	{
		Rva00473B00State *dest = (Rva00473B00State *)destination;
		Rva00473B00State *src = (Rva00473B00State *)source;
		dest->m_vtable = src->m_vtable;
		dest->m_holder = src->m_holder;
		if ( dest->m_holder != 0 )
			++dest->m_holder->m_refCount;
	}
}
