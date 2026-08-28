// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?parseAddModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z: Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp
// Lift the ThingTemplate::parseAddModule __emit thunk to clean C++.
//
// Zero Hour's body, with the one BFME difference the bytes make plain: ZH throws
// the bare enum INI_INVALID_DATA, retail constructs an INIException carrying the
// code 3 and the message text. That constructor is variadic, which is why it is
// __cdecl rather than __thiscall and why `this` arrives as the first stack
// argument with the caller cleaning up twelve bytes.
//
// The function needs no unwind state -- retail has no SEH prologue -- so the
// exception object must have no destructor to run between its construction and
// the throw.
//
// ZH restores the saved oldMode on the way out and retail stores a constant 0.
// Those are the same source: the throw above proves oldMode is MODULEPARSE_NORMAL
// on the path that reaches the store, so the compiler propagates the constant.
//
// The mode byte lives at ThingTemplate+0x498 and is read with movsx, so it is a
// signed char widened for the comparison against the enum rather than a Bool.

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
	MODULEPARSE_ADD_REMOVE_REPLACE = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
protected:
	static void parseAddModule(INI *, void *, void *, const void *);

private:
	unsigned char m_unreconstructed_00[0x498];
	char m_moduleParsingMode;							///< retail this+0x498
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
