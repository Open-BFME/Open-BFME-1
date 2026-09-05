// ?rva0013E280ParseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
// partial score=0.85 date=2026-09-05
// cl: /DNDEBUG /MD /EHs-c-
// 88B twin of ?parseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
// (ThingTemplate_parseAddModule_Thunk.cpp, retail 0x0013E210): byte-identical
// shape, the sole difference is the "new mode" store -- 2 here instead of 1 --
// so this is a sibling parse-mode setter for a different ModuleParseMode enum
// member on the same class, one field-parse table (TheThingTemplateFieldParse)
// and one mode byte at +0x498. Address-derived name pending the real enumerator
// name / caller site that names it.

typedef int Int;

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException(Int code, const char *msg, ...);		///< direct call to 0x00850600
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_msg;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);	///< direct call to 0x008520A0
};

extern const FieldParse TheThingTemplateFieldParse[];	///< retail [0x010910A0]

enum Rva0013E280ParseMode
{
	MODULEPARSE_NORMAL = 0,
	MODULEPARSE_ADD_REMOVE_REPLACE = 1,
	MODULEPARSE_RVA0013E280 = 2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
protected:
	static void rva0013E280ParseAddModule(INI *, void *, void *, const void *);

private:
	unsigned char m_unreconstructed_00[0x498];
	char m_moduleParsingMode;							///< retail this+0x498
};

// address-derived: ?rva0013E280ParseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void ThingTemplate::rva0013E280ParseAddModule(INI *ini, void *instance, void *store, const void *userData)
{
	// don't care about the result.
	ThingTemplate* self = (ThingTemplate*)instance;

	Rva0013E280ParseMode oldMode = (Rva0013E280ParseMode)self->m_moduleParsingMode;
	if (oldMode != MODULEPARSE_NORMAL)
		throw INIException(3, "Expected oldMode to be MODULEPARSE_NORMAL");

	self->m_moduleParsingMode = MODULEPARSE_RVA0013E280;

	ini->initFromINI(self, TheThingTemplateFieldParse);

	self->m_moduleParsingMode = oldMode;
}
// cache-bust 1788628341
