// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
// FXListStore's INI block parser; the map insert inlines STLport insert_unique.

#include <hash_map>
#include "StringInline.h"

struct FieldParse;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern const FieldParse TheFXListFieldParse[];

// The store's 44-byte nodes hold a link, a key and this 36-byte value.
class FXList
{
public:
	FXList(const AsciiString &name);
	FXList(const FXList &other);
	virtual ~FXList();
	void clear();

private:
	unsigned char m_bfmeValue[32];
};

class FXListStore
{
public:
	static void parseFXListDefinition(INI *ini);

private:
	unsigned char m_pad[8];
	_STL::hash_map<int, FXList> m_fxmap;
};

extern FXListStore *TheFXListStore;

void FXListStore::parseFXListDefinition(INI *ini)
{
	const char *c = ini->getNextToken(0);
	NameKeyType key = TheNameKeyGenerator->nameToKey(c);
	FXList &fxl = TheFXListStore->m_fxmap.insert(_STL::make_pair(key, FXList(c))).first->second;
	fxl.clear();
	ini->initFromINI(&fxl, TheFXListFieldParse);
}
