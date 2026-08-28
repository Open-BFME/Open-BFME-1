// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HijackerUpdateModuleData dtor.
// Derived vtbl, Buffer @+0xc then @+0x8, call base dtor.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class HijackerUpdateModuleDataBase
{
public:
	virtual ~HijackerUpdateModuleDataBase();
private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HijackerUpdate.h
class HijackerUpdateModuleData : public HijackerUpdateModuleDataBase
{
public:
	virtual ~HijackerUpdateModuleData();
private:
	Buffer m_a;
	Buffer m_b;
};

// ??1HijackerUpdateModuleData@@UAE@XZ
HijackerUpdateModuleData::~HijackerUpdateModuleData()
{
}
