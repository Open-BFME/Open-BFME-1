// cl: /DNDEBUG /MD /EHsc
//
// Retail's RefundDieModuleData vtable at 0x0108B4E0 names this scalar
// deleting destructor in slot zero. Its call target is the independently
// matched RefundDieModuleData::~RefundDieModuleData body at 0x00125530.

// Retail call 0x00125558 passes owner+0x3c to ILT 0x0001A401
// -> 0x0039D550. That body reads/writes one four-byte pool index and
// releases its entry. The original C++ type and this member's role are unknown.
class Rva0039D550
{
public:
	~Rva0039D550();

private:
	unsigned int m_index;
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
	Rva0039D550 m_handle3C;
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
