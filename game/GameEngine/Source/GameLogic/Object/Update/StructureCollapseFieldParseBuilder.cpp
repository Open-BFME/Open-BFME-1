// cl: /DNDEBUG /MD /EHsc
class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse { const char *token; INIFieldParseProc parse; const void *userData; int offset; };

extern "C" void __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
void parseStructureCollapseObjectCreationLists(INI *ini, void *instance, void *store, const void *userData);
void parseStructureCollapseEffects(INI *ini, void *instance, void *store, const void *userData);

class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int offset = 0);
};

class DieMuxData
{
public:
	static const FieldParse *getFieldParse();
};

// Registration and field keys establish the StructureCollapse role; the original class spelling is unknown.
class Rva002AEDF0ModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

extern const FieldParse g_structureCollapseFieldParse[];

void Rva002AEDF0ModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_structureCollapseFieldParse);
	parse.add(DieMuxData::getFieldParse(), 8);
}

// Retail .rdata VA 0x010C47B8: the table the builder above adds; eleven
// entries and the null terminator, tokens and offsets read from the image.
extern const FieldParse g_structureCollapseFieldParse[] =
{
	{ "MinCollapseDelay", __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x34 },
	{ "MaxCollapseDelay", __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x38 },
	{ "MinBurstDelay", __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3C },
	{ "MaxBurstDelay", __identifier("?parseDurationUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x40 },
	{ "CollapseDamping", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x48 },
	{ "MaxShudder", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4C },
	{ "BigBurstFrequency", __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x44 },
	{ "OCL", parseStructureCollapseObjectCreationLists, 0, 0x0 },
	{ "FXList", parseStructureCollapseEffects, 0, 0x0 },
	{ "DestroyObjectWhenDone", __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF0 },
	{ "CollapseHeight", __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF4 },
	{ 0, 0, 0, 0 }
};
