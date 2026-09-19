// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Two vectors and an out-of-line base destructor, and the two vectors take
// different routes for the reason the element type dictates. The one at +0x224
// holds strings, so its teardown is a loop and MSVC calls the COMDAT copy; the
// one at +0x210 holds an eight-byte POD, so the whole STLport deallocate
// dispatch inlines -- capacity from +0x218 minus +0x210, operator delete above
// 128 bytes and _M_deallocate at or below.
//
// No vptr store appears here, so the class is novtable and the base destructor
// is a real call rather than an inlined empty one.
#include <vector>

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_data;
};

struct SpecialPowerEntry
{
	int m_a;
	int m_b;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_head[0x20C];
};

class __declspec(novtable) OCLSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~OCLSpecialPowerModuleData();

private:
	std::vector<SpecialPowerEntry> m_entries;
	unsigned char m_gap0[0x08];
	std::vector<BFMERetailAsciiString> m_names;
};

// ??1OCLSpecialPowerModuleData@@UAE@XZ
OCLSpecialPowerModuleData::~OCLSpecialPowerModuleData()
{
}
