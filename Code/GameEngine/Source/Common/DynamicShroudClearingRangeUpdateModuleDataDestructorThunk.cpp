// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DynamicShroudClearingRangeUpdateModuleData dtor.
// Nested dual-Buffer @+0x28.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class NestedBuffers
{
public:
	~NestedBuffers();
private:
	Buffer m_a;
	Buffer m_b;
};

// force NestedBuffers dtor to be out-of-line? empty body with members generates SEH
NestedBuffers::~NestedBuffers() {}

class DynamicShroudClearingRangeUpdateModuleDataBase
{
public:
	virtual ~DynamicShroudClearingRangeUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x24];
};

class __declspec(novtable) DynamicShroudClearingRangeUpdateModuleData
	: public DynamicShroudClearingRangeUpdateModuleDataBase
{
public:
	virtual ~DynamicShroudClearingRangeUpdateModuleData();
private:
	NestedBuffers m_nested;
};

// ??1DynamicShroudClearingRangeUpdateModuleData@@UAE@XZ
DynamicShroudClearingRangeUpdateModuleData::~DynamicShroudClearingRangeUpdateModuleData()
{
}
