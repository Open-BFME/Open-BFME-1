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

class __declspec(novtable) W3DQuadrupedDrawModuleDataBase
{
public:
	virtual ~W3DQuadrupedDrawModuleDataBase();
private:
	unsigned char m_pad[0x158];
};

class W3DQuadrupedDrawModuleData : public W3DQuadrupedDrawModuleDataBase
{
	friend void forceW3DQuadrupedDrawModuleDataDeletingDestructorCopy(const W3DQuadrupedDrawModuleData &that);
public:
	virtual ~W3DQuadrupedDrawModuleData();
private:
	W3DQuadrupedElement m_arr[4];
};

// ~W3DQuadrupedDrawModuleData is matched out of line (W3DQuadrupedDrawModuleDataDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceW3DQuadrupedDrawModuleDataDeletingDestructorCopy(const W3DQuadrupedDrawModuleData &that)
{
	W3DQuadrupedDrawModuleData value(that);
}
