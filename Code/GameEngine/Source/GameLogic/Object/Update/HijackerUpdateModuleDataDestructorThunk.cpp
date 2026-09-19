// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.
// Open-BFME5: HijackerUpdateModuleData dtor.
// Derived vtbl, BFMERetailAsciiString @+0xc then @+0x8, call base dtor.

// Retail destroys this member with a direct call to
// StringBase<char>::releaseBuffer (0x00887940) -- the member is a retail
// AsciiString, not the WWLib Buffer whose own destructor is the 40-byte
// body at 0x009E1E30, so name it the way the other lifted ModuleData
// destructors already do.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
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
	BFMERetailAsciiString m_attachToBone;
	BFMERetailAsciiString m_parachuteName;
};

// ??1HijackerUpdateModuleData@@UAE@XZ
HijackerUpdateModuleData::~HijackerUpdateModuleData()
{
}
