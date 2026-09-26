// cl: /DNDEBUG /MD /EHsc

// The two INI callbacks that re-enter the ThingTemplate field-parse table with a
// changed module-parsing mode:
//
//   parseAddModule         0x0013E210  mode 1, MODULEPARSE_ADD_REMOVE_REPLACE
//   parseInheritableModule 0x0013E280  mode 2, MODULEPARSE_INHERITABLE
//
// They are 0x70 apart in the image and byte-identical in shape: read the mode
// byte, refuse to nest, store the new mode, re-enter initFromINI with the whole
// field table, restore. The only difference is which enumerator is stored. They
// sat in two files, in two different directories, each with its own copy of
// INIException, INI, the field-table extern, the enum and ThingTemplate.
//
// The enum is where they disagreed, and the disagreement is settled from
// upstream rather than from either file. parseAddModule declared two enumerators
// and parseInheritableModule three; a third file in this family
// (ThingTemplate_parseReplaceModule.cpp) declares a different third enumerator
// again, MODULEPARSE_MODIFY_ON_COPY, which does not exist upstream. ZH's
// ThingTemplate.h has all four in order -- MODULEPARSE_NORMAL,
// MODULEPARSE_ADD_REMOVE_REPLACE, MODULEPARSE_INHERITABLE,
// MODULEPARSE_OVERRIDEABLE_BY_LIKE_KIND -- so value 2 is INHERITABLE, which is
// also the name the body that stores it already used. All four are written out
// below; the two this TU does not store cost nothing and stop the next reader
// inventing a fifth name.
//
// The mode byte lives at ThingTemplate+0x498 and is read with movsx, so it is a
// signed char widened for the comparison rather than a Bool.
//
// Retail throws INIException carrying the code 3 and the message text where ZH
// throws the bare enum INI_INVALID_DATA. That constructor is variadic, which is
// why it is __cdecl rather than __thiscall and why `this` arrives as the first
// stack argument with the caller cleaning up twelve bytes. Neither function has
// an SEH prologue, so the exception object must have no destructor to run between
// its construction and the throw.
//
// Both bodies restore the saved oldMode on the way out and retail stores a
// constant 0. Those are the same source: the throw above proves oldMode is
// MODULEPARSE_NORMAL on any path that reaches the store, so the compiler
// propagates the constant.

typedef int Int;

struct FieldParse;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException(Int code, const char *msg, ...);		///< direct call to 0x00850600
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_msg;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);	///< direct call to 0x008520A0
};

extern const FieldParse TheThingTemplateFieldParse[];	///< retail [0x010910A0]

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
enum ModuleParseMode
{
	MODULEPARSE_NORMAL,
	MODULEPARSE_ADD_REMOVE_REPLACE,
	MODULEPARSE_INHERITABLE,
	MODULEPARSE_OVERRIDEABLE_BY_LIKE_KIND
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
protected:
	static void parseAddModule(INI *, void *, void *, const void *);
	static void parseInheritableModule(INI *, void *, void *, const void *);

private:
	unsigned char m_unreconstructed_00[0x498];
	char m_moduleParsingMode;				///< retail this+0x498
};

// ?parseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void ThingTemplate::parseAddModule(INI *ini, void *instance, void *store, const void *userData)
{
	// don't care about the result.
	ThingTemplate* self = (ThingTemplate*)instance;

	ModuleParseMode oldMode = (ModuleParseMode)self->m_moduleParsingMode;
	if (oldMode != MODULEPARSE_NORMAL)
		throw INIException(3, "Expected oldMode to be MODULEPARSE_NORMAL");

	self->m_moduleParsingMode = MODULEPARSE_ADD_REMOVE_REPLACE;

	ini->initFromINI(self, TheThingTemplateFieldParse);

	self->m_moduleParsingMode = oldMode;
}

// ?parseInheritableModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
//
// ZH marks the module(s) as being Inheritable here, which is what confirms both
// the enumerator and this function's name.
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
