// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SlaughterHordeContainModuleData dtor.
// 8-element array of 0x18 elems at +0x24c, then base dtor.

class SlaughterHordeElement
{
public:
	~SlaughterHordeElement();
private:
	unsigned char m_pad[0x18];
};

class SlaughterHordeContainModuleDataBase
{
public:
	virtual ~SlaughterHordeContainModuleDataBase();
private:
	unsigned char m_pad[0x248];
};

class __declspec(novtable) SlaughterHordeContainModuleData
	: public SlaughterHordeContainModuleDataBase
{
public:
	virtual ~SlaughterHordeContainModuleData();
private:
	SlaughterHordeElement m_arr[8]; // +0x24c
};

// ??1SlaughterHordeContainModuleData@@UAE@XZ
SlaughterHordeContainModuleData::~SlaughterHordeContainModuleData()
{
}
