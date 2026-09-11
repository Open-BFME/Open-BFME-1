// cl: /DNDEBUG /MD /EHsc
//
// Retail's RefundDieModuleData vtable at 0x0108B4E0 names this scalar
// deleting destructor in slot zero. Its call target is the independently
// matched RefundDieModuleData::~RefundDieModuleData body at 0x00125530.

class Buffer
{
public:
	~Buffer();
};

class RefundDieModuleDataBase
{
public:
	virtual ~RefundDieModuleDataBase() {}

private:
	unsigned char m_pad[0x38];
};

class RefundDieModuleData : public RefundDieModuleDataBase
{
public:
	virtual ~RefundDieModuleData();

private:
	Buffer m_buffer;
};

RefundDieModuleData::~RefundDieModuleData()
{
}
