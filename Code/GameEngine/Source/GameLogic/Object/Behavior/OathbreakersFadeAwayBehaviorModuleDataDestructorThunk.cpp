// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: OathbreakersFadeAwayBehaviorModuleData dtor.
// Retail 80B SEH: destroy BFMERetailAsciiString @+0xc then @+0x8, base vtbl store. BFMERetailAsciiString pin 0x887940.

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

private:
	unsigned char m_pad[4];
};

class OathbreakersFadeAwayBehaviorModuleDataBase
{
public:
	virtual ~OathbreakersFadeAwayBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) OathbreakersFadeAwayBehaviorModuleData
	: public OathbreakersFadeAwayBehaviorModuleDataBase
{
public:
	virtual ~OathbreakersFadeAwayBehaviorModuleData();

private:
	BFMERetailAsciiString m_a;
	BFMERetailAsciiString m_b;
};

// ??1OathbreakersFadeAwayBehaviorModuleData@@UAE@XZ
OathbreakersFadeAwayBehaviorModuleData::~OathbreakersFadeAwayBehaviorModuleData()
{
}
