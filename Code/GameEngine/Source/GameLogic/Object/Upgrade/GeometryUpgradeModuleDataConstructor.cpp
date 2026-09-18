// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: GeometryUpgrade module-data constructor.
//
// The named friend_newModuleData factory at retail 0x0011DFA0 allocates 0x94
// bytes and calls this constructor.  Its matched destructor independently
// fixes the +0x08 upgrade subobject, two twelve-byte vector members at
// +0x70/+0x7C, and three trailing AsciiStrings.

#include <vector>

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();
	~UpgradeModuleDataSub();

private:
	unsigned char m_unmodelled[ 0x68 ];
};

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class __declspec(novtable) GeometryUpgradeModuleDataPrimaryBase
{
public:
	virtual ~GeometryUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_unmodelled_04;
};

class __declspec(novtable) GeometryUpgradeModuleDataIntermediateBase
	: public GeometryUpgradeModuleDataPrimaryBase
{
protected:
	UpgradeModuleDataSub m_upgradeData; // +0x08
};

// Named factory 0x0011DFA0 passes ILT 0x0002A4C3 -> 0x002D5580.
// Its own table at RVA 0x00CCCBC0 names ShowGeometry/+70 and
// HideGeometry/+7c (parseAsciiStringVectorAppend), then WallBoundsMesh/+88,
// RampMesh1/+8c and RampMesh2/+90 (parseAsciiString). The existing vector
// ABI carriers are retained; these names come from the aligned field table.
class GeometryUpgradeModuleData : public GeometryUpgradeModuleDataIntermediateBase
{
public:
	GeometryUpgradeModuleData();
	virtual ~GeometryUpgradeModuleData();

private:
	_STL::vector<unsigned int> m_showGeometry; // +0x70
	_STL::vector<unsigned int> m_hideGeometry;    // +0x7C
	AsciiString m_wallBoundsMesh;              // +0x88
	AsciiString m_rampMesh1;              // +0x8C
	AsciiString m_rampMesh2;              // +0x90
};

// ??0GeometryUpgradeModuleData@@QAE@XZ
GeometryUpgradeModuleData::GeometryUpgradeModuleData()
{
	m_wallBoundsMesh.clear();
	m_rampMesh1.clear();
	m_rampMesh2.clear();
}
