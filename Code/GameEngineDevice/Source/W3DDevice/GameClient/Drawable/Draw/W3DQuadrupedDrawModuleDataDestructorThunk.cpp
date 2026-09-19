// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DQuadrupedDrawModuleData dtor.
// 4-element array of 4-byte elems at +0x15c, base dtor.

class W3DQuadrupedElement
{
public:
	~W3DQuadrupedElement();
private:
	unsigned char m_pad[4];
};

class W3DQuadrupedDrawModuleDataBase
{
public:
	virtual ~W3DQuadrupedDrawModuleDataBase();
private:
	unsigned char m_pad[0x158];
};

class __declspec(novtable) W3DQuadrupedDrawModuleData
	: public W3DQuadrupedDrawModuleDataBase
{
public:
	virtual ~W3DQuadrupedDrawModuleData();
private:
	W3DQuadrupedElement m_arr[4];
};

// ??1W3DQuadrupedDrawModuleData@@UAE@XZ
W3DQuadrupedDrawModuleData::~W3DQuadrupedDrawModuleData()
{
}
