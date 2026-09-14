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

// Open-BFME: protected scalar-deleting destructor for RefundDie.
// Constructor 0x00255A80 installs vtable 0x00CB331C whose slot zero routes
// through ILT 0x0000DB4D to this 30-byte wrapper, whose complete destructor
// route ILT 0x00001B4F reaches cleanup body 0x00255A40.

class RefundDie
{
protected:
	virtual ~RefundDie();
private:
	friend void forceRefundDieDeletingDestructor();
};

void forceRefundDieDeletingDestructor()
{
	RefundDie value;
}
