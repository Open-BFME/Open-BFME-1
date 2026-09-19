// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ConvertToCarBombCrateCollideModuleData dtor. SEH BFMERetailAsciiString member pin body 0x887940.

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

class ConvertToCarBombCrateCollideModuleDataBase
{
public:
	virtual ~ConvertToCarBombCrateCollideModuleDataBase() {}
private:
	unsigned char m_pad[0x40];
};

class __declspec(novtable) ConvertToCarBombCrateCollideModuleData : public ConvertToCarBombCrateCollideModuleDataBase
{
public:
	virtual ~ConvertToCarBombCrateCollideModuleData();
private:
	BFMERetailAsciiString m_buffer;
};

// ??1ConvertToCarBombCrateCollideModuleData@@UAE@XZ
ConvertToCarBombCrateCollideModuleData::~ConvertToCarBombCrateCollideModuleData()
{
}
