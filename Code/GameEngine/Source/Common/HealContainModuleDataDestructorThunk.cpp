// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: lift ModuleData dtor MASM dump to clean C++.
// Retail SEH dtor with two POD vector members (+0x14 then +0x08, reverse
// declaration order), each deallocated inline through the STLport node_alloc
// 0x80 threshold (big: operator delete; small: _M_deallocate), then the base
// vftable store. #include <vector> comes first so node_alloc is used.

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual ~ModuleData() {}
	unsigned int m_04;
};

class __declspec(novtable) HealContainModuleData : public ModuleData
{
public:
	virtual ~HealContainModuleData();

private:
	std::vector<int> m_b;	// +0x08
	std::vector<int> m_a;	// +0x14
};

// ??1HealContainModuleData@@UAE@XZ
HealContainModuleData::~HealContainModuleData()
{
}
