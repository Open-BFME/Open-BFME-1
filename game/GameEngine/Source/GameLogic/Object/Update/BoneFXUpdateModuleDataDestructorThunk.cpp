// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BoneFXUpdateModuleData dtor.
// Triple 0x20-element arrays of 0x24-byte elems at +0x0c/+0x490/+0x914.

class BoneFXElement
{
public:
	~BoneFXElement();
private:
	unsigned char m_pad[0x24];
};

class BoneFXUpdateModuleDataBase
{
public:
	virtual ~BoneFXUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x8];
};

class __declspec(novtable) BoneFXUpdateModuleData
	: public BoneFXUpdateModuleDataBase
{
public:
	virtual ~BoneFXUpdateModuleData();
private:
	BoneFXElement m_a[0x20];
	unsigned char m_gap1[4];
	BoneFXElement m_b[0x20];
	unsigned char m_gap2[4];
	BoneFXElement m_c[0x20];
};

// ??1BoneFXUpdateModuleData@@UAE@XZ
BoneFXUpdateModuleData::~BoneFXUpdateModuleData()
{
}
