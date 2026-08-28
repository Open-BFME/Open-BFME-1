// cl: /DNDEBUG /MD /EHsc
// readable body of ??1W3DTreeDrawModuleData@@UAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTreeDraw.cpp
// Open-BFME5: W3DTreeDrawModuleData dtor.
// Early derived vtbl; Buffers @+0x08/+0x0c/+0x28/+0x48; base vtbl.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class W3DTreeDrawModuleDataBase
{
public:
	virtual ~W3DTreeDrawModuleDataBase() {}
private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTreeDraw.h
class W3DTreeDrawModuleData : public W3DTreeDrawModuleDataBase
{
public:
	virtual ~W3DTreeDrawModuleData();
private:
	Buffer m_a;
	Buffer m_b;
	unsigned char m_gap1[0x18];
	Buffer m_c;
	unsigned char m_gap2[0x1c];
	Buffer m_d;
};

// ??1W3DTreeDrawModuleData@@UAE@XZ
W3DTreeDrawModuleData::~W3DTreeDrawModuleData()
{
}
