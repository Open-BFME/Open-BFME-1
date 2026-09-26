// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RubbleRiseUpdateModuleData dtor.
// Dual 4-element arrays of 0x0c elems at +0x54 and +0x84.

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

class __declspec(novtable) RubbleRiseUpdateModuleData
	: public RubbleRiseUpdateModuleDataBase
{
public:
	virtual ~RubbleRiseUpdateModuleData();
private:
	RubbleRiseElement m_a[4];
	RubbleRiseElement m_b[4];
};

// ??1RubbleRiseUpdateModuleData@@UAE@XZ
RubbleRiseUpdateModuleData::~RubbleRiseUpdateModuleData()
{
}
