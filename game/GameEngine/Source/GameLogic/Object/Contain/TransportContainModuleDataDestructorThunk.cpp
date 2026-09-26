// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TransportContainModuleData dtor. SEH BFMERetailAsciiString @+0x174 then base.

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

class TransportContainModuleDataBase
{
public:
	virtual ~TransportContainModuleDataBase();
private:
	unsigned char m_pad[0x170];
};

class __declspec(novtable) TransportContainModuleData : public TransportContainModuleDataBase
{
public:
	virtual ~TransportContainModuleData();
private:
	BFMERetailAsciiString m_buffer;
};

// ??1TransportContainModuleData@@UAE@XZ
TransportContainModuleData::~TransportContainModuleData()
{
}
