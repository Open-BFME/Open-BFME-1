// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// LibraryMap constructor parsed by PlayerAITypeSet::parseBlock at 0x000DEEC0.

#include <string.h>
#include <vector>

#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *instance, const FieldParse *parseTable);
};

class LibraryMap
{
public:
	LibraryMap(INI *ini);

private:
	AsciiString m_name;
	std::vector<AsciiString> m_libraryMaps;
};

LibraryMap::LibraryMap(INI *ini)
{
	INI *source = ini;
	const char *name = source->getNextToken();
	int length = name != 0 ? (int)strlen(name) : 0;
	((StringBase<char> *)this)->set(name, length);
	source->initFromINI(this, (const FieldParse *)0x01084130);
}
