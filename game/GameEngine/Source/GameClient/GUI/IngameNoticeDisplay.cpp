// cl: /DNDEBUG /DWIN32 /MD /EHsc

template <typename T> class Rva0048EC80StringBase
{
friend class Rva0048EC80UnicodeString;
private:
	Rva0048EC80StringBase(const Rva0048EC80StringBase<T> &other);
	~Rva0048EC80StringBase();
	T *m_data;
};

class Rva0048EC80UnicodeString : private Rva0048EC80StringBase<unsigned short>
{
public:
	Rva0048EC80UnicodeString(const Rva0048EC80UnicodeString &other) :
		Rva0048EC80StringBase<unsigned short>(other) {}
	~Rva0048EC80UnicodeString() {}
};

struct Rva0048EC80Descriptor
{
	unsigned int field0;
	unsigned int field4;
};

class Rva0048EC80Resource
{
public:
	virtual void f0();
	virtual void setText(Rva0048EC80UnicodeString text);
	virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
	virtual void setDescriptor(unsigned int value);
	virtual void f7(); virtual void f8(); virtual void f9();
	virtual void finish(int first, int second);
};

class Rva0048EC80Manager
{
public:
	virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
	virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
	virtual void f8();
	virtual Rva0048EC80Resource *create(void);
};

extern Rva0048EC80Manager *Rva0048EC80TheManager;

class Rva0048EC80ResourceOwner
{
public:
	Rva0048EC80ResourceOwner(const Rva0048EC80UnicodeString &text,
		Rva0048EC80Descriptor *descriptor, int identifier);
private:
	Rva0048EC80Descriptor *m_descriptor;
	Rva0048EC80Resource *m_resource;
	unsigned int m_unused;
	int m_identifier;
};

Rva0048EC80ResourceOwner::Rva0048EC80ResourceOwner(
	const Rva0048EC80UnicodeString &text, Rva0048EC80Descriptor *descriptor,
	int identifier)
{
	Rva0048EC80Descriptor *desc = descriptor;
	m_descriptor = desc;
	m_resource = 0;
	m_unused = 0;
	m_identifier = identifier;
	m_resource = Rva0048EC80TheManager->create();
	if (m_resource)
	{
		m_resource->setDescriptor(desc->field4);
		m_resource->setText(text);
		m_resource->finish(0, 0);
	}
}
