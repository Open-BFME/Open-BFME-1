// cl: /DNDEBUG /MD /EHsc
//
// Retail's W3DQuadrupedDrawModuleData vtable at 0x0111D190 names this scalar
// deleting destructor in slot zero. Its call target is the independently
// matched destructor body at 0x006BFF70.

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

class W3DQuadrupedDrawModuleData : public W3DQuadrupedDrawModuleDataBase
{
public:
	virtual ~W3DQuadrupedDrawModuleData();
private:
	W3DQuadrupedElement m_arr[4];
};

W3DQuadrupedDrawModuleData::~W3DQuadrupedDrawModuleData()
{
}
