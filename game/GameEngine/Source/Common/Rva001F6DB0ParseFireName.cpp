// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x001F6DB0, 165 bytes. The FieldParse table at RVA 0x00CA2D28
// names this callback FireName at offset 0 for Rva001F6EA0::buildFieldParse.
// The class name stays address-derived because the table does not name it.

#include "StringInline.h"
#include <vector>

class Open2Elem063700 : public AsciiString
{
public:
	Open2Elem063700(const char *text) : AsciiString(text) {}
	Open2Elem063700(const Open2Elem063700 &other) : AsciiString(other) {}
};

class INI
{
public:
	const char *getNextToken(const char *separators);
};

class Rva001F6EA0
{
public:
	static void parseFireName(INI *ini, void *instance, void *store, const void *userData);

private:
	unsigned char m_pad[0x18];
	_STL::vector<Open2Elem063700> m_fireNames;
};

// ?parseFireName@Rva001F6EA0@@SAXPAVINI@@PAX1PBX@Z
void Rva001F6EA0::parseFireName(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	Rva001F6EA0 *self = (Rva001F6EA0 *)instance;
	const char *token = ini->getNextToken(0);
	if (token)
		self->m_fireNames.push_back(token);
}
