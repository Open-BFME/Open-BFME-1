// cl: /DNDEBUG /MD /EHs-c-
// RubbleRiseUpdateModuleData::buildFieldParse, retail 0x002A4190, 36 bytes.
//
// The ledger read this address as StructureToppleUpdateModuleData
// ::buildFieldParse until 2026-09-16. The table the body adds is at
// 0x010C2AB0 and holds MinRubbleRiseDelay, MaxRubbleRiseDelay, MinBurstDelay,
// MaxBurstDelay, RubbleRiseDamping, RubbleHeight, MaxShudder,
// BigBurstFrequency, OCL and FXList. Its OCL row points at the landed
// parseRubbleRiseObjectCreationLists at 0x002A40E0 and its FXList row at the
// landed parseRubbleRiseFXLists at 0x002A4030, both of which sit right below
// this body. targets/game/reverse/module_registry.tsv puts the RubbleRiseUpdate constructor
// at 0x002A3640 and the StructureToppleUpdate constructor at 0x002AF1E0, so
// this address belongs to the RubbleRise translation unit.
//
// Retail emits no call for the base class, so UpdateModuleData::buildFieldParse
// is empty here. MultiIniFieldParse::add keeps its out-of-line copy at
// 0x00850920, which is what the two calls reach.
typedef int Int;
typedef unsigned int UnsignedInt;

class INI
{
public:
	static void parseInt( INI *ini, void *instance, void *store, const void *userData );
	static void parseReal( INI *ini, void *instance, void *store, const void *userData );
	static void parseDurationUnsignedInt( INI *ini, void *instance, void *store,
		const void *userData );
};

struct FieldParse
{
	const char *token;
	void (*parse)( INI *ini, void *instance, void *store, const void *userData );
	const void *userData;
	Int offset;
};

class MultiIniFieldParse
{
public:
	void add( const FieldParse *f, UnsignedInt extraOffset = 0 );
};

class DieMuxData
{
public:
	static const FieldParse *getFieldParse( void );
};

void parseRubbleRiseObjectCreationLists( INI *ini, void *instance, void *store,
	const void *userData );
void parseRubbleRiseFXLists( INI *ini, void *instance, void *store,
	const void *userData );

class UpdateModuleData
{
public:
	static void buildFieldParse( MultiIniFieldParse & ) {}
};

class RubbleRiseUpdateModuleData : public UpdateModuleData
{
public:
	static void buildFieldParse( MultiIniFieldParse &p );
};

// ?buildFieldParse@RubbleRiseUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z
void RubbleRiseUpdateModuleData::buildFieldParse( MultiIniFieldParse &p )
{
	UpdateModuleData::buildFieldParse( p );

	static const FieldParse dataFieldParse[] =
	{
		{ "MinRubbleRiseDelay",	INI::parseDurationUnsignedInt,	0, 0x34 },
		{ "MaxRubbleRiseDelay",	INI::parseDurationUnsignedInt,	0, 0x38 },
		{ "MinBurstDelay",	INI::parseDurationUnsignedInt,	0, 0x3c },
		{ "MaxBurstDelay",	INI::parseDurationUnsignedInt,	0, 0x40 },
		{ "RubbleRiseDamping",	INI::parseReal,	0, 0x48 },
		{ "RubbleHeight",	INI::parseReal,	0, 0x4c },
		{ "MaxShudder",	INI::parseReal,	0, 0x50 },
		{ "BigBurstFrequency",	INI::parseInt,	0, 0x44 },
		{ "OCL",	parseRubbleRiseObjectCreationLists,	0, 0 },
		{ "FXList",	parseRubbleRiseFXLists,	0, 0 },
		{ 0, 0, 0, 0 }
	};
	p.add( dataFieldParse );
	p.add( DieMuxData::getFieldParse(), 8 );
}
