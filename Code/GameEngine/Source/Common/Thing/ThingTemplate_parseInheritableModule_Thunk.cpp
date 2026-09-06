// cl: /DNDEBUG /MD /EHs-c-
// Near-twin of ?parseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
// (Code/GameEngine/Source/Common/ThingTemplate_parseAddModule_Thunk.cpp,
// retail 0x0013E210): byte-identical shape, the sole difference is the
// "new mode" store -- MODULEPARSE_INHERITABLE (2) here instead of
// MODULEPARSE_ADD_REMOVE_REPLACE (1). ZH names this
// ThingTemplate::parseInheritableModule (Source/Common/Thing/ThingTemplate.cpp,
// "mark the module(s) as being Inheritable"), confirming the enumerator and
// the real name.

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

enum ModuleParseMode
{
	MODULEPARSE_NORMAL = 0,
	MODULEPARSE_ADD_REMOVE_REPLACE = 1,
	MODULEPARSE_INHERITABLE = 2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
protected:
	static void parseInheritableModule(INI *, void *, void *, const void *);

private:
	unsigned char m_unreconstructed_00[0x498];
	char m_moduleParsingMode;							///< retail this+0x498
};

// ?parseInheritableModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void ThingTemplate::parseInheritableModule(INI *ini, void *instance, void *store, const void *userData)
{
	// don't care about the result.
	ThingTemplate* self = (ThingTemplate*)instance;

	ModuleParseMode oldMode = (ModuleParseMode)self->m_moduleParsingMode;
	if (oldMode != MODULEPARSE_NORMAL)
		throw INIException(3, "Expected oldMode to be MODULEPARSE_NORMAL");

	self->m_moduleParsingMode = MODULEPARSE_INHERITABLE;

	ini->initFromINI(self, TheThingTemplateFieldParse);

	self->m_moduleParsingMode = oldMode;
}
