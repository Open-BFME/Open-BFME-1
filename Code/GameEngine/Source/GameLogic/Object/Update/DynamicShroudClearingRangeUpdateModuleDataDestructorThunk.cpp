// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DynamicShroudClearingRangeUpdateModuleData dtor.
// Nested dual-BFMERetailAsciiString @+0x28.

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

class NestedBuffers
{
public:
	// Defined in-class: retail has no out-of-line body for it, and an
	// out-of-line definition here is a function the ledger does not declare.
	~NestedBuffers() {}

private:
	BFMERetailAsciiString m_a;
	BFMERetailAsciiString m_b;
};

class DynamicShroudClearingRangeUpdateModuleDataBase
{
public:
	virtual ~DynamicShroudClearingRangeUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x24];
};

class __declspec(novtable) DynamicShroudClearingRangeUpdateModuleData
	: public DynamicShroudClearingRangeUpdateModuleDataBase
{
public:
	virtual ~DynamicShroudClearingRangeUpdateModuleData();
private:
	NestedBuffers m_nested;
};

// ??1DynamicShroudClearingRangeUpdateModuleData@@UAE@XZ
DynamicShroudClearingRangeUpdateModuleData::~DynamicShroudClearingRangeUpdateModuleData()
{
}
