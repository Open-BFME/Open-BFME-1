// cl: /DNDEBUG /MD /EHsc

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
