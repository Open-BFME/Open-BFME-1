// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RefundDieModuleData dtor.
// Retail 67B SEH: release indexed handle @+0x3c, base vtbl store. Handle destructor route 0x1A401 -> 0x39D550.

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

class __declspec(novtable) RefundDieModuleData
	: public RefundDieModuleDataBase
{
public:
	virtual ~RefundDieModuleData();

private:
	Rva0039D550 m_handle3C;
};

// ??1RefundDieModuleData@@UAE@XZ
RefundDieModuleData::~RefundDieModuleData()
{
}
