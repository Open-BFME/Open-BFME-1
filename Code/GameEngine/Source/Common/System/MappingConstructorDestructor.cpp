// cl: /DNDEBUG /MD /EHsc

class MemoryPoolObject
{
public:
	virtual void memoryPoolAnchor();
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	void *m_data;
};

class Mapping : public MemoryPoolObject
{
public:
	Mapping();

protected:
	virtual ~Mapping();

private:
	Mapping *m_next;
	AsciiString m_name;
};

Mapping::Mapping()
{
}

Mapping::~Mapping()
{
}
