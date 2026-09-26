// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: lift ModuleData dtor MASM dump to clean C++.
// Retail @0x0027E4E0: SEH dtor whose body frees two POD pointers at
// this+0x14/+0x18 (plain operator delete, 2-iteration loop), then destroys
// members in reverse declaration order: a vector<AsciiString> at +0x58
// (state 3), AsciiStrings at +0x44 (state 2) and +0x30 (state 1), and a
// red-black-tree container at +0x08 (state 0), then the base vftable store.

#include "ascii_string.h"

// Stand-in for the out-of-line STLport red-black-tree dtor @0x001468A0
// (header-node teardown); pinned in symbols.csv.
class ModuleDataTreeStandIn
{
	void *m_header;
	unsigned int m_count;
	unsigned int m_reserved;
public:
	~ModuleDataTreeStandIn();
};

#include <vector>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual ~ModuleData() {}
	unsigned int m_moduleTagNameKey;
};

class AnimalAIUpdateModuleData : public ModuleData
{
public:
	virtual ~AnimalAIUpdateModuleData();

private:
	ModuleDataTreeStandIn m_tree;	// +0x08
	int *m_p14;	// +0x14, freed in the dtor body
	int *m_p18;	// +0x18, freed in the dtor body
	int m_f1c, m_f20, m_f24, m_f28, m_f2c;
	AsciiString m_s30;	// +0x30
	int m_f34, m_f38, m_f3c, m_f40;
	AsciiString m_s44;	// +0x44
	int m_f48, m_f4c, m_f50, m_f54;
	std::vector<AsciiString> m_vec;	// +0x58
};

// ??1AnimalAIUpdateModuleData@@UAE@XZ
AnimalAIUpdateModuleData::~AnimalAIUpdateModuleData()
{
	for (int i = 0; i < 2; i++)
	{
		if ((&m_p14)[i])
			delete (&m_p14)[i];
	}
}
