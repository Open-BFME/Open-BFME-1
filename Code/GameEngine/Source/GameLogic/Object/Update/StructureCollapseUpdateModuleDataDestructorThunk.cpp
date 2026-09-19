// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: StructureCollapseUpdateModuleData dtor.
// Dual 5-element arrays of 0x0c elems at +0x50 and +0x8c.

class StructureCollapseElement
{
public:
	~StructureCollapseElement();
private:
	unsigned char m_pad[0x0c];
};

class StructureCollapseUpdateModuleDataBase
{
public:
	virtual ~StructureCollapseUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x4c];
};

class __declspec(novtable) StructureCollapseUpdateModuleData
	: public StructureCollapseUpdateModuleDataBase
{
public:
	virtual ~StructureCollapseUpdateModuleData();
private:
	StructureCollapseElement m_a[5];
	StructureCollapseElement m_b[5];
};

// ??1StructureCollapseUpdateModuleData@@UAE@XZ
StructureCollapseUpdateModuleData::~StructureCollapseUpdateModuleData()
{
}
