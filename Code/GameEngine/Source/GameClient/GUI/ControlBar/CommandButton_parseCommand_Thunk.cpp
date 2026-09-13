// cl: /DNDEBUG /MD /EHs-c-
// Lift CommandButton::parseCommand to clean C++.
//
// An INI name-to-index lookup: take the next token, walk a null-terminated table
// of names comparing case-insensitively, and store the matching index through the
// store pointer. A miss throws.
//
// The comparison goes through the import table -- MSVC hoists the slot into a
// register before the loop and calls through it -- and the retail binary imports
// _strcmpi, not _stricmp. Declaring the wrong one of that pair still builds and
// still byte-matches, because the slot address is a copied DIR32, so it has to
// be got right by reading the imports rather than by trusting the build.
//
// The throw is the same shape as ThingTemplate::parseAddModule: a variadic and
// therefore __cdecl constructor taking `this` as its first stack argument, and
// the exception type needs a declared copy constructor or MSVC builds the object
// and then copies it into a second slot instead of constructing it in place.

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

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
	const char *getNextToken(const char *seps = 0);		///< ILT thunk at 0x00850970
};

extern const char *TheCommandNames[];					///< retail [0x012B5F80]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	static void parseCommand(INI *, void *, void *, const void *);
};

// ?parseCommand@CommandButton@@SAXPAVINI@@PAX1PBX@Z
void CommandButton::parseCommand(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken();

	Int index = 0;
	while (TheCommandNames[index])
	{
		if (_strcmpi(TheCommandNames[index], token) == 0)
		{
			*(Int *)store = index;
			return;
		}
		++index;
	}

	throw INIException(3, "Command '%s' not found", token);
}
