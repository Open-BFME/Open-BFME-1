#include "../../../../../Include/Common/FieldParse.h"

class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int extraOffset);
};

class DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

extern const FieldParse SupplyWarehouseDockUpdateModuleDataFieldParse[];

class SupplyWarehouseDockUpdateModuleData : public DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void SupplyWarehouseDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(SupplyWarehouseDockUpdateModuleDataFieldParse, 0);
}
