// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DynamicShroudClearingRangeUpdateModuleData dtor.
// Nested dual-BFMERetailAsciiString @+0x28.

// The TU-local string view uses the canonical StringBase release method.
#include "../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

namespace
{
class BFMERetailAsciiString
{
public:
	__forceinline ~BFMERetailAsciiString()
	{
		reinterpret_cast<StringBase<char> *>(this)->clear();
	}

private:
	unsigned char m_pad[4];
};
}

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
