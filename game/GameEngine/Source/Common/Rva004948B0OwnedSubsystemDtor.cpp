// cl: /DNDEBUG /DWIN32 /MD /EHsc

class Rva004948B0Resource
{
public:
	virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
	virtual void f4(); virtual void f5(); virtual void f6();
	virtual void release(void);
};

class Rva004948B0Base
{
public:
	virtual ~Rva004948B0Base();
private:
	void *m_name;
};

class Rva004948B0OwnedSubsystem : public Rva004948B0Base
{
public:
	virtual ~Rva004948B0OwnedSubsystem();
private:
	Rva004948B0Resource *m_resource;
	unsigned char m_padding[0x14];
	unsigned char m_flags;
};

Rva004948B0OwnedSubsystem::~Rva004948B0OwnedSubsystem()
{
	if (m_resource)
		m_resource->release();
	m_resource = 0;
	m_flags &= 0xfc;
}
