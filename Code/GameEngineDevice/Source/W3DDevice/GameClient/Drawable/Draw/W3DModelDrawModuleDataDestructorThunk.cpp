// cl: /DNDEBUG /MD /EHsc
// readable body of ??1W3DModelDrawModuleData@@UAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp
// Open-BFME5: W3DModelDrawModuleData dtor. SEH W3DModelDrawModuleDataMember @+0x5c then base.

class W3DModelDrawModuleDataMember
{
public:
	~W3DModelDrawModuleDataMember();
private:
	unsigned char m_pad[4];
};

class W3DModelDrawModuleDataBase
{
public:
	virtual ~W3DModelDrawModuleDataBase();
private:
	unsigned char m_pad[0x58];
};

class __declspec(novtable) W3DModelDrawModuleData : public W3DModelDrawModuleDataBase
{
public:
	virtual ~W3DModelDrawModuleData();
private:
	W3DModelDrawModuleDataMember m_member;
};

// ??1W3DModelDrawModuleData@@UAE@XZ
W3DModelDrawModuleData::~W3DModelDrawModuleData()
{
}
