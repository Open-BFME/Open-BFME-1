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

extern const FieldParse RailedTransportDockUpdateModuleDataFieldParse[];

class RailedTransportDockUpdateModuleData : public DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void RailedTransportDockUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	DockUpdateModuleData::buildFieldParse(parse);
	parse.add(RailedTransportDockUpdateModuleDataFieldParse, 0);
}
