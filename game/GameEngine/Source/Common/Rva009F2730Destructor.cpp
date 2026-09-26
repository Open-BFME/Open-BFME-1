// cl: /DNDEBUG /MD /EHsc
// Address-derived owner and state names do not assert the original C++ spelling.

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	void *m_name;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class Rva009F5970State
{
public:
	~Rva009F5970State();
private:
	unsigned char m_storage[0xF4];
};

class Rva009F2730Owner : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Rva009F2730Owner();
private:
	Rva009F5970State *m_ownedState;
};

Rva009F2730Owner::~Rva009F2730Owner()
{
	delete m_ownedState;
}
