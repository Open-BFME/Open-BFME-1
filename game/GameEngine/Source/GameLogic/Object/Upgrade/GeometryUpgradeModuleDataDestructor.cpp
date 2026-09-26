// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ lift of the ModuleData destructor.

class GeometryUpgradeModuleDataMemberA
{
public:
	~GeometryUpgradeModuleDataMemberA();

private:
	unsigned char m_data[0x68];
};

class GeometryUpgradeModuleDataMemberB
{
public:
	~GeometryUpgradeModuleDataMemberB();

private:
	unsigned char m_data[0x0c];
};

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class GeometryUpgradeModuleDataPrimaryBase
{
public:
	virtual ~GeometryUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_04;
};

class __declspec(novtable) GeometryUpgradeModuleDataIntermediateBase
	: public GeometryUpgradeModuleDataPrimaryBase
{
private:
	GeometryUpgradeModuleDataMemberA m_base;
};

// Named factory 0x0011DFA0 passes ILT 0x0002A4C3 -> 0x002D5580.
// Its own table at RVA 0x00CCCBC0 names ShowGeometry/+70 and
// HideGeometry/+7c (parseAsciiStringVectorAppend), then WallBoundsMesh/+88,
// RampMesh1/+8c and RampMesh2/+90 (parseAsciiString). The existing vector
// ABI carriers are retained; these names come from the aligned field table.
class __declspec(novtable) GeometryUpgradeModuleData
	: public GeometryUpgradeModuleDataIntermediateBase
{
public:
	virtual ~GeometryUpgradeModuleData();

private:
	GeometryUpgradeModuleDataMemberB m_showGeometry;
	GeometryUpgradeModuleDataMemberB m_hideGeometry;
	AsciiString m_wallBoundsMesh;
	AsciiString m_rampMesh1;
	AsciiString m_rampMesh2;
};

// ??1GeometryUpgradeModuleData@@UAE@XZ
GeometryUpgradeModuleData::~GeometryUpgradeModuleData()
{
}
