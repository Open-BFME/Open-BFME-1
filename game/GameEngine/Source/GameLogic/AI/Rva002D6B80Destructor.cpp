// Address-derived ABI slice for the multi-vtable destructor at 0x002D6B80.
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHs-

class Rva2D6B80TrivialHead
{
public:
	virtual void headAnchor();

private:
	unsigned int m_04;
};

class Rva00047C53MultiBase
{
public:
	virtual ~Rva00047C53MultiBase();

private:
	unsigned int m_04;
	unsigned int m_08;
};

class Rva2D6B80IfaceA
{
public:
	virtual void ifaceAAnchor();
};

class Rva2D6B80IfaceB
{
public:
	virtual void ifaceBAnchor();
};

class Rva2D6B80DeepBase : public Rva00047C53MultiBase, public Rva2D6B80IfaceA
{
public:
	virtual ~Rva2D6B80DeepBase() {}
};

class Rva2D6B80Middle : public Rva2D6B80DeepBase, public Rva2D6B80IfaceB
{
public:
	virtual ~Rva2D6B80Middle() {}
};

class Rva002D6B80MultiTailDtor : public Rva2D6B80TrivialHead, public Rva2D6B80Middle
{
public:
	virtual ~Rva002D6B80MultiTailDtor();
};

Rva002D6B80MultiTailDtor::~Rva002D6B80MultiTailDtor()
{
}
