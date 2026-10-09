// cl: /DNDEBUG /MD /EHsc

// RefundDieModuleData::buildFieldParse, retail 0x00123290, 36 bytes.
//
// RefundDie::friend_newModuleData (0x001232C0) hands
// INI::initFromINIMultiProc the incremental-link thunk 0x0040F4BB, and that
// thunk jumps here; nothing else in the image references the thunk. See
// identity_evidence/00123290-refunddie-buildfieldparse.md.
//
// The body registers DieMuxData::getFieldParse() at offset 8, then the table
// at 0x0108B560: UpgradeRequired (+0x34), BuildingRequired (+0x3C) and
// RefundPercent (+0x38), the three keys RefundDie::onDie reads.

class INI;

struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class MultiIniFieldParse
{
public:
	void add(const FieldParse *fields, unsigned int extraOffset = 0);
};

class INI
{
public:
	static void parseUpgradeTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);

class DieMuxData
{
public:
	static const FieldParse *getFieldParse();
};

class RefundDieModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);
};

// ?buildFieldParse@RefundDieModuleData@@SAXAAVMultiIniFieldParse@@@Z
void RefundDieModuleData::buildFieldParse(MultiIniFieldParse &p)
{
	p.add(DieMuxData::getFieldParse(), 8);

	static const FieldParse dataFieldParse[] =
	{
		{ "UpgradeRequired", INI::parseUpgradeTemplate, 0, 0x34 },
		{ "BuildingRequired", iniParseObjectFilter, 0, 0x3C },
		{ "RefundPercent", INI::parsePercentToReal, 0, 0x38 },
		{ 0, 0, 0, 0 }
	};

	p.add(dataFieldParse);
}
