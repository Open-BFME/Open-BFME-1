// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.
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
	Buffer m_attachToBone;
	Buffer m_parachuteName;
};

// ??1HijackerUpdateModuleData@@UAE@XZ
HijackerUpdateModuleData::~HijackerUpdateModuleData()
{
}
