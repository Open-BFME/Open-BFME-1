// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: StealthDetectorUpdateModuleData dtor.
// BFMERetailAsciiString @+0x104, members @+0x84/+0x14.

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

class StealthDetectorUpdateModuleDataMemberA
{
public:
	~StealthDetectorUpdateModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class StealthDetectorUpdateModuleDataBase
{
public:
	virtual ~StealthDetectorUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x10];
};

class __declspec(novtable) StealthDetectorUpdateModuleData
	: public StealthDetectorUpdateModuleDataBase
{
public:
	virtual ~StealthDetectorUpdateModuleData();
private:
	StealthDetectorUpdateModuleDataMemberA m_a;
	unsigned char m_gap1[0x6c];
	StealthDetectorUpdateModuleDataMemberA m_b;
	unsigned char m_gap2[0x7c];
	BFMERetailAsciiString m_c;
};

// ??1StealthDetectorUpdateModuleData@@UAE@XZ
StealthDetectorUpdateModuleData::~StealthDetectorUpdateModuleData()
{
}
