// cl: /DNDEBUG /MD
// Retail 0x007B0400: release the retained resource before base destruction.

class Rva007B0400Ref
{
public:
	virtual void deleteThis();
	int m_refCount;
};

class Rva007B0400Base
{
public:
	virtual ~Rva007B0400Base();
private:
	char m_padding[0x64];
};

Rva007B0400Base::~Rva007B0400Base()
{
}

class Rva007B0400Owner : public Rva007B0400Base
{
public:
	virtual ~Rva007B0400Owner();
private:
	Rva007B0400Ref *m_reference;
};

Rva007B0400Owner::~Rva007B0400Owner()
{
	Rva007B0400Ref *reference = m_reference;
	if ( reference != 0 )
	{
		if ( --reference->m_refCount == 0 )
			reference->deleteThis();
		m_reference = 0;
	}
}
