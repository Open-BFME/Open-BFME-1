// cl: /DNDEBUG /MD /EHs-c-

// Look up a meta type by name, then its record, then hand the record to the
// field parser. Each lookup throws on a miss.
//
// Both MetaMap methods mangle IAE -- protected -- so INI has to reach them as a
// friend. Widening them to public would rename the symbols to QAE and the calls
// would no longer resolve.
//
// The throw follows the shape already established for CommandButton::parseCommand:
// a variadic and therefore __cdecl constructor taking this as its first stack
// argument, with a declared copy constructor so MSVC builds the exception in
// place rather than constructing it and copying it into a second slot.
typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException(Int code, const char *msg, ...);
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_msg;
};

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	enum Type
	{
		MSG_INVALID = 0
	};
};

class MetaMapRec;
class INI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h
class MetaMap
{
	friend class INI;

protected:
	GameMessage::Type findGameMessageMetaType(const char *name);

	MetaMapRec *getMetaMapRec(GameMessage::Type type);
};

extern MetaMap *TheMetaMap;
extern const FieldParse TheMetaMapFieldParseTable[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps = 0);

	void initFromINI(void *what, const FieldParse *table);

	static void parseMetaMapDefinition(INI *ini);
};

// ?parseMetaMapDefinition@INI@@SAXPAV1@@Z
void INI::parseMetaMapDefinition(INI *ini)
{
	const char *token = ini->getNextToken();

	GameMessage::Type type = TheMetaMap->findGameMessageMetaType(token);
	if (type == GameMessage::MSG_INVALID)
		throw INIException(3, "Game message meta type for '%s' not found", token);

	MetaMapRec *rec = TheMetaMap->getMetaMapRec(type);
	if (rec == 0)
		throw INIException(3, "Meta map entry for '%s' not found", token);

	ini->initFromINI(rec, TheMetaMapFieldParseTable);
}
