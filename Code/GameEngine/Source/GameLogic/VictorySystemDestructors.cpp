// cl: /DNDEBUG /MD /EHsc
// Complete destructor (0x001DFF40) and its emitted scalar-deleting wrapper
// (0x001E02F0). The constructor-installed vtable 0x0109FD8C identifies both.

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	unsigned int m_name;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class VictoryParameterVector
{
public:
	~VictoryParameterVector();
};

class VictorySystem : public SubsystemInterface, public Snapshot
{
public:
	virtual ~VictorySystem();

private:
	char m_fields[0xe0];
	VictoryParameterVector m_parameters;
};

VictorySystem::~VictorySystem()
{
}
