// cl: /DNDEBUG /MD /EHsc
//
// Retail's RubbleRiseUpdateModuleData vtable at 0x0108EAF8 names this scalar
// deleting destructor in slot zero. Its call target is the independently
// matched destructor body at 0x00128BD0.

class RubbleRiseElement
{
public:
	~RubbleRiseElement();

private:
	unsigned char m_pad[0x0c];
};

class RubbleRiseUpdateModuleDataBase
{
public:
	virtual ~RubbleRiseUpdateModuleDataBase() {}

private:
	unsigned char m_pad[0x50];
};

class RubbleRiseUpdateModuleData : public RubbleRiseUpdateModuleDataBase
{
public:
	virtual ~RubbleRiseUpdateModuleData();

private:
	RubbleRiseElement m_a[4];
	RubbleRiseElement m_b[4];
};

RubbleRiseUpdateModuleData::~RubbleRiseUpdateModuleData()
{
}
