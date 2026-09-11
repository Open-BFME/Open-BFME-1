// cl: /DNDEBUG /MD /EHsc
//
// Retail's SpecialEnemySenseUpdateModuleData vtable at 0x0108CD38 names this
// scalar deleting destructor in slot zero. Its call target is the separately
// matched destructor body at 0x00125890.

class Buffer
{
public:
	~Buffer();
};

class SpecialEnemySenseUpdateModuleDataBase
{
public:
	virtual ~SpecialEnemySenseUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class SpecialEnemySenseUpdateModuleData
	: public SpecialEnemySenseUpdateModuleDataBase
{
public:
	virtual ~SpecialEnemySenseUpdateModuleData();

private:
	Buffer m_buffer;
};

SpecialEnemySenseUpdateModuleData::~SpecialEnemySenseUpdateModuleData()
{
}
