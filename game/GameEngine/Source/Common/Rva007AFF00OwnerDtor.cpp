// cl: /DNDEBUG /MD
// Retail 0x007AFF00: release two retained resources before base destruction.

class Rva007AFF00Ref
{
public:
	virtual void deleteThis();
	int m_refCount;
};

class Rva007AFF00Base
{
public:
	virtual ~Rva007AFF00Base();
private:
	char m_padding[0x64];
};

Rva007AFF00Base::~Rva007AFF00Base()
{
}

class Rva007AFF00Owner : public Rva007AFF00Base
{
public:
	virtual ~Rva007AFF00Owner();
private:
	Rva007AFF00Ref *m_first;
	int m_padding;
	Rva007AFF00Ref *m_second;
};

Rva007AFF00Owner::~Rva007AFF00Owner()
{
	Rva007AFF00Ref *reference = m_first;
	if ( reference != 0 )
	{
		if ( --reference->m_refCount == 0 )
			reference->deleteThis();
		m_first = 0;
	}

	reference = m_second;
	if ( reference != 0 )
	{
		if ( --reference->m_refCount == 0 )
			reference->deleteThis();
		m_second = 0;
	}
}
