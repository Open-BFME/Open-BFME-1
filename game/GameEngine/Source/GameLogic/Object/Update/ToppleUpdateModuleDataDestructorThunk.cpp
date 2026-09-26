// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ToppleUpdateModuleData dtor. SEH BFMERetailAsciiString member pin body 0x887940.

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
};

class ToppleUpdateModuleDataBase
{
public:
	virtual ~ToppleUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) ToppleUpdateModuleData : public ToppleUpdateModuleDataBase
{
public:
	virtual ~ToppleUpdateModuleData();
private:
	BFMERetailAsciiString m_buffer;
};

// ??1ToppleUpdateModuleData@@UAE@XZ
ToppleUpdateModuleData::~ToppleUpdateModuleData()
{
}
